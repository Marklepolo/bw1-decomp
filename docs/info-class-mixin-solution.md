# GBaseInfo Info-class byte-exact — the mixin solution

The reusable clean-C++ fix that makes the `GBaseInfo` data-table Info family (74 classes:
CreatureInitialSourceInfo, AlignmentInfo, ReactionInfo, the Magic*Info, …) compile byte-exact.

## Problem
The compiler-generated **array ctor** for a global `XInfo g_table[N]` kept the intermediate
`??_7GBaseInfo` vtable store (43 B) where retail collapses it to 2 stores (37 B). No
compiler/flag/CRT reproduced it — `objdiff` fuzzy% even reported false 100% (use `exact_gate.py`).

## Root cause
MSVC6 sets each class's vtable at the **start** of its ctor, then runs member inits. Inlined into the
array ctor, `Base→GBaseInfo→CISI` emitted:
`[eax]=??_7Base; [eax+4]=0 (destroyed); [eax]=??_7GBaseInfo; [eax+8]=0 (next); [eax]=??_7CISI`.
The `next=0` store **wedges** between GBaseInfo's (dead) vtable store and CISI's overwrite, blocking
MSVC's dead-store elimination of the intermediate vtable. Retail emits members first, so the
intermediate vtable store is adjacent to CISI's and gets eliminated.

## The fix (clean C++ — no `__asm`, no pointer math)
Move `next` into a **non-polymorphic mixin used as a 2nd base**:
```cpp
class GBaseInfo;
class NextHolder            // non-polymorphic: contributes NO vtable
{
public:
    GBaseInfo* next;        /* 0x8 */
    NextHolder() { next = 0; }
};
class GBaseInfo : public Base, public NextHolder
{
public:
    int index;             /* 0xc */
    // ~GBaseInfo() is IMPLICIT (virtual, inherited) — do NOT declare it explicitly
    ...
};
```
Why it works:
- A non-poly **2nd base** is constructed *after* `Base` but *before* `GBaseInfo`'s own vtable store, so
  `next=0` is emitted before that vtable store → no wedge → MSVC drops the intermediate vtable. **Both
  array ctors byte-exact (37 B, d=0).**
- Making `~GBaseInfo` **implicit** lets the array dtor fold the chain to `??1Base` with no vtable-thrash.
- `NextHolder` adds no vtable slot, so **layout (0x10), sizeof (0x54), and the vtable are unchanged**
  (`vtbl_bin`-verified). `next` stays at offset 0x8 and remains accessible (inherited).

## Result
`CreatureInitialSourceInfo`: **6/10 → 8/10** byte-exact (`exact_gate.py`). Both ctors + both
dtor-bodies exact, no regression to `Base`/`Persistent`. Family-safe: a full ninja build of the
configured TUs is clean. Applies to every `GBaseInfo` data-table class.

## Remaining (the one wall)
The 2 array dtors are byte-identical to retail **minus a 15-byte run-once destruction guard**
(`mov cl,[guard]; mov al,1; test; jne; or cl,al; mov [guard],cl`, bit-packed). MSVC6 in our toolchain
never emits this guard for a global teardown under any compiler/CRT/flag/pragma tested — a toolchain
gap, not a source problem. Details + the exhaustive matrix: `docs/parked-tus/CreatureInitialSourceInfo.md`.

## Verify
```
python tools/exact_gate.py CreatureInitialSourceInfo \
  0x4DD220 0x4DD230 0x4DD280 0x4DD290 0x4DD2E0 0x4DD2F0 0x4DD320 0x4DD330
```

## The guard — characterized as a PROJECT-WIDE gap (not CISI-specific)
The remaining 15B run-once destruction guard is **ubiquitous**: scanning retail `.text` for the prologue
`8A0D <imm32> B0 01 84 C8` finds **695 guarded dtors across 167 guard bytes** — i.e. nearly every
global-object dtor in B&W carries it. Our toolchain emits **zero** of them: tested **7 compilers**
(c2 RTM 8168 / SP3 8447 / SP4 8799 / SP5 8966 / beta 8047 / 6.6 / 6.5pp), every CRT (`/MT`/`/ML`/`/MD`
±debug), `/GX`/`/EH`, `init_seg`, and each compiler's own CRT headers — none emit a guard for a
file-scope global teardown.

**Key:** the guard *mechanism* DOES exist in our compiler — it emits the identical pattern (guard var
`_?$S1@…`, `B0 01 84 C8`) for **function-local-static run-once init**. So this is not a missing feature
but a c1xx/config difference: retail emits the run-once guard for **file-scope global destruction**,
ours only for **local-static init**. CISI is file-scope (`??__E` dynamic init at 0x4DD220 is
unconditional, not a guarded accessor), so the local-static path doesn't apply.

**Implication:** every global-object data-table TU in dtk hits this same wall on its dtor — it is a
maintainer-level global-termination-codegen gap, reproducible only with the exact c1xx build Lionhead
used (not in the OmniBlade `msvcwin9x` set) or by a source construct that routes file-scope teardown
through the local-static guard. Tool: `build/_cisi_guardtest.py` (guard-prologue scan across all
compilers). Win banked regardless: the mixin gets the whole family's **ctors + dtor-bodies** byte-exact.
