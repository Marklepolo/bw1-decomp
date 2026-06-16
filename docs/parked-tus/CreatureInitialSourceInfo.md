# CreatureInitialSourceInfo — WIP Matching TU (BW1E142): 6/10 byte-exact, 4 blocked

**Status:** shelved as `Object(NonMatching, …)` on 2026-06-12. The body
`src/Black/CreatureInitialSourceInfo.cpp` is **kept as WIP** (both static arrays defined). Six of
ten functions are byte-exact (proven by `tools/exact_gate.py`); four are blocked on an MSVC
construction/destruction-vtable codegen mismatch. This is the first *real* data-table lift attempt
(arrays DEFINED, not the false `extern`-method-only port that was reverted) — see
[[baw-matching-tu-completeness-gate]].

## Game meaning
`CreatureInitialSourceInfo` is the data table of a creature's **61 initial "desire sources"** — the
inputs (hunger, cold, being attacked, a tasty villager nearby, …) that feed the creature's desires
in the belief–desire–intention loop ([[baw-bdi-sprint]]). Each 0x54-byte record holds that source's
starting config; the Mac symbols expose `GetInitialThreshold()` and `GetInitialValue()` (2 of the 17
dwords). `GetBaseInfo` hands the whole 61-record table (+ the count) to the creature-info loader.

## Structure (strict-gate truth)
`.text` = `0x004DD220–0x004DD360`, **10 functions**. Two `CreatureInitialSourceInfo[61]` tables in
`.bss` (runtime-loaded, zero-init): `g_creatureInitialSourceInfo` @`0xC89958` (returned by
`GetBaseInfo`) and `g_creatureInitialSourceInfoDefault` @`0xC87E98`. Each table has a dynamic-init
(init-pair → ctor) and an atexit-registered destructor (register → guarded dtor loop).

| addr | function | exact? |
|---|---|---|
| `0x4DD220` | array-A init-pair (call ctor → jmp atexit) | ✅ |
| `0x4DD230` | array-A ctor | ❌ extra `??_7GBaseInfo` + `ecx`/`edx` swap |
| `0x4DD260` | `GetBaseInfo` (count=61, returns array A) | ✅ |
| `0x4DD280` | array-A atexit-register | ✅ |
| `0x4DD290` | array-A dtor | ❌ calls `??1GBaseInfo`, no run-once guard |
| `0x4DD2C0` | `??_GCreatureInitialSourceInfo` (scalar-deleting dtor) | ✅ |
| `0x4DD2E0` | array-B init-pair | ✅ |
| `0x4DD2F0` | array-B ctor | ❌ (same as A) |
| `0x4DD320` | array-B atexit-register | ✅ |
| `0x4DD330` | array-B dtor | ❌ (same as A) |

## The 4 blocked diffs — one root cause
MSVC **keeps `GBaseInfo`'s intermediate vtable handling** where the original **collapses the abstract
middle class**:
- **ctor** target: `set ??_7Base; [+4]=0; [+8]=0; set ??_7CISI` (2 vtables, 37 B). Mine: inserts
  `mov [eax], ??_7GBaseInfo` (3 vtables, 43 B) and allocates `ecx`=zero/`edx`=count where the target
  uses `ecx`=count/`edx`=zero.
- **dtor** target: run-once guard byte + inline loop calling `??1Base` (the folded base dtor). Mine:
  no guard + calls `??1GBaseInfo` (one level too high).

## Ruled out (don't re-try these)
- `/Ob1` vs `/Ob2` — `/Ob1` is correct; `/Ob2` regresses Persistent (100→14%) + zlib.
- inline-fold: `~GBaseInfo() {}` makes the dtor call `??1Base` but ADDS a vtable-set (still wrong).
- pure vs non-pure `GetBaseInfo` — both keep the `GBaseInfo` vtable-set.
- reference repo (`_repos/bw1-decomp`) — only raw reassembled asm, no clean source idiom.

## How to resume
1. Flip `configure.py` back to `Object(Matching, "Black/CreatureInitialSourceInfo.cpp")` and re-add a
   `splits.txt` entry: `.text 0x004DD220–0x004DD360` + vtable + RTTI + `.bss` for the two arrays.
2. Build, then prove with the **strict** gate (not objdiff fuzzy%):
   `python tools/exact_gate.py CreatureInitialSourceInfo 0x4DD220 0x4DD230 0x4DD280 0x4DD290 0x4DD2E0 0x4DD2F0 0x4DD320 0x4DD330`
3. The remaining lever: get MSVC to **collapse `GBaseInfo`'s intermediate vtable-set** in both
   construction and destruction (ctor sets only `??_7Base`+`??_7CISI`; dtor calls `??1Base` with the
   guard). Likely needs the exact original `Base`/`GBaseInfo` ctor/dtor idiom or a codegen/flag
   insight not yet found.

Headers already staged: `Base.h` → `Base() { destroyed = 0; }` inline + proper `operator delete`;
`BaseInfo.h` → `GBaseInfo() { next = 0; }` inline + `GetBaseInfo` pure (vtable slot 9).

## 2026-06-13 update — proof-based, two more levers ruled out
Re-attacked with the now-working bw1-decomp byte-exact build (md5 `174b1a64`) as the target-bytes
oracle + a fast standalone compile→`exact_gate` idiom loop (`build/_cisi_experiment.py`: compile one
TU with the exact Black cflags, byte-compare each fn to the target, seconds per idiom).

**Exact target ctor `0x4DD230` (capstone — dumpbin's MSDIS110.DLL is missing, use capstone):**
```
mov eax,0xC89958 ; array base      mov ecx,0x3D ; count=61      xor edx,edx
loop: mov [eax],??_7Base ; mov [eax+4],edx ; mov [eax+8],edx ; mov [eax],??_7CISI
      add eax,0x54 ; dec ecx ; jne loop ; ret      (37 B, TWO vtables)
```
Two independent deltas vs ours: **(a)** regalloc — target `ecx=count/edx=0`, ours `ecx=0/edx=count`
(a pure `permute`/regalloc finisher target, only worth doing once the structural delta is solved);
**(b)** the extra `mov [eax],??_7GBaseInfo` (+6 B → 43 B). Target *keeps* the dead `??_7Base` store
but *drops* `??_7GBaseInfo` — so it is **not** plain dead-store elimination (DSE would drop both);
MSVC6 simply never emits the intermediate base's vtable in the inlined most-derived array ctor.

- **Per-TU `/Ob2`: REJECTED (data).** Standalone `/Ob2` inlines the per-element ctor *into* the
  dynamic-init (init-pair 10 B→54 B), wrecking the function boundaries, and still does not collapse
  the vtable. (So `/Ob2` is dead globally *and* per-TU — the earlier global-only rejection now holds
  per-object too.)
- **Ctor-idiom search: REJECTED (data).** `GBaseInfo() : next(0) {}` (init-list), `{ this->next=0; }`,
  and Base-also-init-list all still emit `??_7GBaseInfo` (43 B). Ctor *body form* does not reach it.

Net: the regalloc half is mechanically fixable; the vtable-collapse half is a deep MSVC6
construction/destruction-vtable codegen behavior that neither flags nor ctor-body source idioms
reach. Still parked. Untried angles if resumed: vary the **vtable layout / virtual-decl set** of
`GBaseInfo`, or find a sibling `GBaseInfo`-family TU whose array ctor already matches and copy its
class shape.

### ctor MECHANISM CRACKED (2026-06-13, later) — collapse is reproducible, gates the whole family
The collapse is **universal** in the original: across all **74** `GBaseInfo` Info classes every array
ctor stores only `[Base, <Derived>]`; `??_7GBaseInfo` is stored just **3×** in all of `.text` (vs
`??_7Base` 117×). Same toolchain as dtk (`cl 12.00.8804` SP5/6, `/Ob1`). So it is **not** a
compiler/flag wall — it is a reproducible source-structure property, and solving it unlocks the
entire data-table Info family, not just CISI.

**Root mechanism (proven via the standalone compile→`exact_gate` loop, `build/_cisi_*.py`):** MSVC6
dead-store-eliminates the intermediate (`GBaseInfo`) ctor vtable store **iff no member store wedges
between it and the most-derived vtable store**.
- `GBaseInfo() {}` (no `next=0`) → vtable **COLLAPSES** (2 vtables). Proves the wedge is the blocker.
- `GBaseInfo() { next = 0; }` → the `next=0` store (offset +8) wedges between `??_7GBaseInfo` and
  `??_7CISI` → DSE won't look past it → vtable **KEPT** (43 B, 3 vtables). This is our exact bug.
- Setting `next` in `Base::Base` (so it's written *before* `GBaseInfo`'s vtable) → **ctor byte-exact,
  37 B d=0, both arrays** — but it resizes Base 0x8→0xc → breaks `??_GBase` (d=1) + every Base class.
- A non-poly intermediate `GInfoLink : public Base` owning `next` **fails**: deriving from polymorphic
  Base makes it polymorphic too → it gets `??_7GInfoLink` and the wedge just relocates there (43 B).

**The remaining contradiction (the real open question):** the target sets `next` at +8 **without**
wedging **and** keeps Base = 0x8 (`??_GBase` matches only at 0x8). With `next` a `GBaseInfo` member
(set after GBaseInfo's vtable) the wedge is unavoidable in our codegen — yet the original elides it on
the *same* compiler+flags. So our imported `Base`/`GBaseInfo` headers must differ from the true
layout/virtual-set in a way that changes the schedule. **Next step:** Ghidra-decompile the real
`GBaseInfo::GBaseInfo` (`0x42E5E0`) + `Base::Base` to recover true member ownership/order and the
exact vtable shape, then reproduce. The dtor (`0x4DD290`: calls `??1Base` + run-once guard; ours
calls `??1GBaseInfo`, no guard) is the destruction-side of the same collapse and should fall out once
the construction structure is right.

Reusable harnesses left in `build/` (disposable): `_cisi_experiment.py` (ctor-idiom sweep),
`_cisi_ctor_cmp.py` (mine-vs-target instr diff), `_cisi_siblings.py` (family-wide vtable-ref census),
`_cisi_next_in_base.py` / `_cisi_intermediate.py` (structure tests). All write headers back LF-safe.

### THE root cause: members-first vs vtable-first (capstone, Ghidra MCP was down — port 8080 refused)
The **true** `GBaseInfo::GBaseInfo` (`0x42E5E0`) is **members-first**:
`mov [eax+4],0 ; mov [eax+8],0 ; mov [eax],??_7GBaseInfo` — members set, THEN the vtable (Base's
vtable elided). Ours compiles **vtable-first**, so when inlined into CISI's array ctor the member
store wedges between `??_7GBaseInfo` and `??_7CISI` and blocks DSE. The whole bug is this ordering.
- The **target array ctor** is the *mix*: `??_7Base` first (kept), then members, then `??_7CISI` —
  i.e. **Base vtable-first, GBaseInfo members-first**, so only GBaseInfo's vtable is adjacent to
  CISI's and gets DSE'd.
- **`/Oa` (assume-no-alias)** flips ours to members-first → array ctor = **38 B referencing only
  `??_7CISI`** (Base *and* GBaseInfo eliminated). That **over**-collapses (target keeps Base) and is
  global-only — MSVC6 has no per-function `/Oa` (`#pragma optimize` controls only g/s/t/y, not
  aliasing). Flag sweep (O1/Ox/Os/Ot/Oy, O2±Og) all keep GBaseInfo vtable-first.
- **Remaining gap:** make *only* `GBaseInfo`'s ctor members-first under standard aliasing. Not reached
  by ctor body, flags, pragma, or the structure variants tried. **`vtbl_bin` confirms our
  `Base`/`GBaseInfo`/`CISI` vtables + member layout MATCH the binary exactly** (Base 7 slots;
  GBaseInfo `GetDebugText@1c / GetDebugColor@20 / __purecall@24 / UpdateValue@28`; CISI overrides +24)
  — so it is NOT a structure mismatch. It is purely MSVC's per-class store scheduling: the original's
  `GBaseInfo::GBaseInfo` is members-first on the *same* toolchain, ours is vtable-first, and no source
  lever we have flips one class without `/Oa` flipping all of them. Remaining hypotheses: an exact
  per-TU build-env/flag combo Lionhead used, or it is not cleanly reproducible with our invocation.
  The dtor (`0x4DD290`) is the same collapse on the destruction side and should follow once (if) the
  ctor scheduling is matched. **Verdict: stays parked — exhaustively root-caused, clean fix unknown.**

### Compiler-version sweep (2026-06-13) — SP version is NOT the lever
The binary is a multi-compiler patchwork (`compiler_sweep.py` docstring: C++ dominated by c2-8966, C
by the 8047 beta, + 8799/8447/8168). Downloaded RTM(8168)/SP3(8447)/SP4(8799) and swept CISI's ctor
across **all four** available MSVC6 c2 back-ends (now persisted in `compilers-extra/`, auto-discovered
by `compiler_sweep.py`): **every one produces the identical 43 B vtable-first ctor, 6/10 exact.** So
the members-first ordering is not any standard MSVC6 SP — codegen is stable RTM→SP5. The **8047 beta**
(which the docstring says built the *C* objects) is the only untested MSVC6 back-end and is **not in
the OmniBlade `msvcwin9x` release** (only 6.0/6.3/6.4/6.5/6.5pp/6.6/7.0).

**UPDATE — 8047 beta sourced + tested → compiler route DEFINITIVELY REJECTED.** Extracted from the
VS6.0 Beta2 install disks (`dlls/VS6.0 build 8056 (Beta2)/` → `_cltest/ext_8047/Bin`), saved as
`compilers-extra/8047-beta2/Bin` (`compiler_sweep --list` shows `c2-8047(beta)`). Swept CISI's ctor
across **all FIVE** c2 back-ends (RTM 8168 / SP3 8447 / SP4 8799 / SP5 8966 / **beta 8047**):
**byte-identical 43 B vtable-first ctor, 6/10, every one.** No MSVC6 back-end produces CISI's
members-first ctor under our cflags — so it is NOT the compiler. The lever is the per-class store
**scheduling** itself (target = Base vtable-first + GBaseInfo members-first in one inlined ctor),
reachable only by `/Oa` which over-collapses (drops Base too). Ghidra (now up) confirms `0x42E5E0`
members-first, matching capstone. Side win: the 5-compiler `compilers-extra/` set + the
`compiler_sweep.py` root edit make the "which compiler built this TU" sweep a one-click, project-wide
tool for any register-allocation-sensitive TU.

### ★ BREAKTHROUGH 2026-06-13 — clean-C++ solves the ctor + dtor-body (9/10), only a 15B guard left
The intermediate-vtable collapse IS reproducible in clean C++ (no `__asm`, no hacks) via a
**non-polymorphic mixin base** that owns `next`:
```cpp
class NextHolder { public: GBaseInfo* next; NextHolder() { next = 0; } };   // non-poly: NO vtable
class GBaseInfo : public Base, public NextHolder { ...; /* implicit ~GBaseInfo (remove explicit decl) */ };
```
Mechanism: as a non-poly **2nd base**, `NextHolder` is constructed after `Base` but **before**
GBaseInfo's own vtable store, so `next=0` no longer wedges between `??_7GBaseInfo` and `??_7CISI` →
MSVC drops the intermediate vtable, exactly like the original. Layout (0x10), sizeof (0x54) and the
vtable are unchanged (`vtbl_bin`-verified — NextHolder adds no slots). Making `~GBaseInfo` implicit
lets the array dtor fold the chain to `??1Base` with no vtable-thrash.
Result (strict `exact_gate`, standalone compile): **both ctors 37B d=0; both dtors call `??1Base`
clean; `??_GBase`/`??_GCISI`/GetBaseInfo/init-pairs/atexit all exact → 9/10.**
**Only remaining delta:** the 2 array dtors lack the 15-byte run-once guard (`mov cl,[0xC8929C];
mov al,1; test; jne; or cl,al; mov [0xC8929C],cl` — bit-packed A=bit0, B=bit1). Otherwise the dtor is
byte-identical (same backward loop, same `~Base` calls). Guard trigger NOT found in: all 5 c2 back-ends,
`/GX`, `/ML`, `/Oa`/`/Ow`, member type, ctor/dtor form, mixin variants. It is MSVC6's per-TU shared
global-destruction guard; reproducing it is the last step. Harnesses: `build/_cisi_mixin.py`,
`_cisi_dtor_cmp.py`, `_cisi_sweep_mixin.py`. The mixin fix applies to the **whole GBaseInfo family**
(74 classes) — apply to `src/Black/BaseInfo.h` once confirmed in a full ninja build.

**Guard finding (exhaustive):** the 15B run-once guard is NOT emitted by ANY of our 5 compilers
(front-end c1xx + back-end c2: RTM/SP3/SP4/SP5/beta) under ANY CRT (`/MT`/`/ML`/`/MD` ± `d`/`_DEBUG`)
or flag, for a minimal 2-global-dtor TU (`build/_cisi_guardtest.py`: dtors stay 16B, no guard byte).
So it is fully systematic — the original's guarded global-destruction is a source construct or build
config our toolchain doesn't reproduce (NOT a flag/compiler/CRT we can reach). **CISI is at 8/10 in
clean C++** (both ctors + both dtor-bodies correct; the 2 array dtors differ ONLY by this 15B
guard). Remaining ideas if resumed: `#pragma init_seg`, a function-local-static accessor form (but the
target's construction is an unconditional file-scope `??__E`, which contradicts local-static), or the
original used a compiler build we don't have. The clean-C++ structural crack (mixin) is the real win.

**Guard — DEFINITIVE (full matrix, `build/_cisi_dtorstruct.py`):** tested single vs **array** × non-poly
vs poly vs **mixin** — in EVERY case the global-object teardown dtor is **32B with no guard** (an
earlier "guard for arrays" reading was a false positive: the 48–64B funcs were the *ctors*/`??_H`/`??_I`,
not the dtors). CISI's array dtor (`_$E2`, 32B: backward loop calling `??1Base`) is **byte-identical to
the target (48B) minus exactly the 15B run-once guard**. Our MSVC6 toolchain never emits that guard for
any global teardown under any compiler/CRT/flag/pragma. **Final state: CISI 8/10 clean C++**; the 2
dtors need only the guard, which is a genuine toolchain gap (needs the original's exact build). Mixin
LOCKED IN to `src/Black/BaseInfo.h` (family-safe: full ninja build of 25 configured TUs clean; 59/106
`*Info.h` compile, the 47 failures are pre-existing MapCoords-blocked headers, not the mixin).

### 2026-06-14 — genuine state re-confirmed via fresh disasm; an exact_gate PAIRING BUG fixed
Re-verified end to end with the **committed** sources (the `class GBaseInfo : public Base, public
LHListNode<GBaseInfo>` mixin in `src/Black/BaseInfo.h` — `LHListNode` is the non-poly 2nd base that
owns `next`, the clean LH-idiomatic form of the `NextHolder` trick). The mixin works: **11 of 13
emitted functions are byte-exact** (`exact_gate.py`), every one except the 2 array dtors:
- **exact:** `??_GBase`, `??_GCreatureInitialSourceInfo`, `GetBaseInfo`, and BOTH tables'
  init-pair / ctor / atexit — `_$E4`/`_$E1`/`_$E3` for table A (@0xC89958), `_$E9`/`_$E6`/`_$E8` for
  table B (@0xC87E98). Table B's ctor `_$E6` (37 B, d=0) proves the intermediate-`??_7GBaseInfo`
  collapse holds for the **2nd** array too (not just A).
- **blocked:** the 2 array dtors `_$E2` (A) / `_$E7` (B) — 28 B each, byte-identical to retail's 43 B
  dtors **minus the 15-byte run-once guard**.

**exact_gate had a pairing bug (now FIXED).** It paired each `.o` function to its best slot greedily
in symbol-table order; the **unused COMDAT vector iterators `??_H`/`??_I`** (vector ctor/dtor
iterators — they match no slot, d=999, and fold away at link) were processed first and **consumed**
table-B's slots 0x4DD2E0/0x4DD2F0, starving the real `_$E9`/`_$E6` → a false **"6/11"**. The mixin
had looked like it regressed table B; it had not. Fix in `tools/exact_gate.py`: skip `??_H`/`??_I`
(never a per-TU `.text` slot) + assign the `_$E*` helpers to slots by **global lowest-diff** (best
pairs first), not greedy-per-function. Post-fix the gate reports the true **11/13**.

**Guard fully characterized (both dtors disassembled).** Per-object run-once flags — **not**
shared/bit-packed (an earlier guess): dtor A's guard byte @0xC8929C, dtor B's @0xC87E90, each
`8A0D <g>` (mov cl,[g]) · `B0 01` (al=1, **bit0**) · `84 C8` (test) · `75 23` (jne end) ·
`0A C8` (or cl,al) · `88 0D <g>` (mov [g],cl). **Construction is UNGUARDED** (the `??__E` init at
0x4DD220/0x4DD2E0 runs unconditionally at startup); only the **atexit-registered destruction** is
guarded against a double call. That unguarded-construct + guarded-destruct asymmetry is
compiler-emitted global-teardown codegen — it **cannot be written in clean C++** (it is not a source
construct), and no MSVC6 back-end / CRT / flag in our toolchain emits it (exhaustive matrix above).
**Verdict unchanged:** CISI is a genuine **11/13** in clean C++; the last 2 dtors need Lionhead's
exact c1xx global-termination codegen — a toolchain gap, not a source problem. Stays parked; making it
a `Matching` TU would carve the *whole* `.text` block (the 2 dtors break the unit link-match), so the
11 genuine functions would be **gap-filled** at link, not actually linked — hence **no "100%" claim**.
