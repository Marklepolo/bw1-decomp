# 09 — Tooling + State Audit Synthesis ("why 60 tools but no progress")

Four parallel audits, each rule = **verify by running, report only confirmed facts**. This is the
synthesis + the fixes applied. Everything below was confirmed by running, not asserted.

## Root causes of stalled progress (verified)
1. **No trustworthy measurement loop** — byte-exact counts kept disagreeing. → **FIXED:** `tools/bytecount.py`.
2. **Tools run in the wrong repo** — the lift/xref/symbol/vtable/rdata tools need the asm+header corpus that
   lives ONLY in **bw1-decomp** (379 `.asm`, 17 285 symbols). Run from **bw1-dtk** they found 0 files →
   returned `None`/empty → read as "broken." They were never broken; they were data-starved. → **FIXED:**
   `tools/corpus.py` local-first fallback (11 tools now work from either checkout).
3. **Tool/agent output trusted without verifying** — e.g. `vtable_drift.py`'s "no drift" was a data-starved
   artifact; I relayed it. → **DISCIPLINE:** run the self-test; never claim a number without producing it.
4. **Diverged base + experimental detours** — `filter-branch` re-hashed 122 upstream base commits into our WIP
   branches (patch-id-proven); global `/G6` and CRT-reconstruction won't merge as-is.

## The measurement loop (USE THIS — the one truth)
```
# run from bw1-dtk
build/tools/objdiff-cli.exe report generate -p . -o rep.json
python3 tools/bytecount.py            # global + every TU
python3 tools/bytecount.py Abode      # one TU
```
Truth field = report `measures.matched_functions` (== functions with `fuzzy_match_percent >= 100`).
Do NOT count via `objdiff-cli diff -u` — it includes folded/CRT symbols and **undercounts** (gave 394 vs the
real 443 for Abode). **Current: GLOBAL 2952 / 25981; ABODE 443 / 608 (73%).**

## The repo split (REMEMBER — this was the core confusion)
- **bw1-decomp** = the ANALYSIS corpus (lifted asm `src/asm`, headers `black/*.h`, vftables, staging stubs).
  Run lift / xref / vtable / symbols / rdata here (or anywhere now — `corpus.py` falls back to it).
- **bw1-dtk** = the BUILD + objdiff + `bytecount`. Run the matching loop here.

## Tool fixes applied (committed: dtk `54750af0`, decomp `50b71369`, md5-mirrored)
- **`corpus.py` (NEW, both repos):** local-first corpus resolver; falls back to sibling `bw1-decomp`. Patched
  into `symbolize / symbols / rdata / vtable / lift_thunks / taint_xref` → **11 tools FAIL→PASS in dtk**
  (symbols, vtable, symbolize, rdata, autolift, fpu, gpr, sig_arity, propose, lift_thunks, taint_xref),
  **zero regression in decomp** (corpus present locally → no-op).
- **`--help`/no-arg guards:** `_extract / testcompile / measure_match / verify_defs / verify_isolate` now print
  usage instead of `FileNotFoundError`/`StopIteration`; `project.py` relative imports made dual-mode.
- **pyyaml 6.0.3** installed in the venv (unblocks `post_link_patch`).
- **Trustworthy core** = the 53 self-test-passing tools (see `00-TOOLKIT.md`) + `bytecount.py`.
  `vtable_drift.py` is now ratchet-pinned: its `--self-test` asserts ZERO drift for the whole
  Object→Mobile→MobileWallHug→Living chain (slot counts + every binary-commented slot). The COMPILER is the
  only ground truth — verify with `bw1-dtk/tools/probe_vtable.py` (`/FAcs` listing of real vcalls).

## The vtable drift — FIXED (2026-06-09), compiler-verified, zero-regression
**Before:** `v->IsChild()` compiled to `[eax+0xAA8]`; retail wants `[reg+0xAF8]` → a +0x50 (20-slot) drift that
shifted EVERY virtual past it, blocking expressive-C for any virtual-calling function in the Object-derived
hierarchy. **After:** `v->IsChild()` compiles to `[reg+0xAF8]`; `IsDead`→0xAF4, and the whole chain lays out
exactly where the binary's `??_7*@@6B@` arrays say. Global byte-exact floor held at **2952 → 2952 (0
regressions, 0 losses)** — the fix is layout-only; it UNBLOCKS future expressive-C virtual-callers (the gain
is realised as those functions get authored).

### Probe harness (the ground-truth check) — `bw1-dtk/tools/probe_vtable.py`
Compiles a TU of one-vcall functions with the exact Black `/FAcs` flags and reads each emitted
`call/jmp DWORD PTR [reg+0xNN]`. Pinned probes (all PASS): `IsChild→0xAF8`, `IsDead→0xAF4`,
`IsSpellSeedReturnPoint→0x670`, `GetImpressiveValue()→0x66C`, `StartOnFire→0x6BC`, `GetTribalPower→0x6C8`,
and `GetFoodType→<non-virtual>` (see below). `--self-test` exits non-zero on any drift.

### What was missing / wrong, per class (exact edits, in `bw1-decomp/black/*.h`)
- **Object** (`Object.h`): three vtable slots were declared NON-virtual / mis-positioned, compensated by 3
  trailing `_missing1/2/3` virtual placeholders — that kept the slot *count* right but shifted slots 0x668+.
  Fix: removed the 3 `_missing` placeholders; declared `virtual float GetImpressiveValue()` (0x66c) BEFORE the
  inherited-2-arg override; declared `virtual bool32_t IsTouching(Object*, float)` (0x6b8). Two slots stay
  NON-virtual on purpose (see below). Result: Object 535/535 slots, zero drift.
- **Mobile** (`Mobile.h`): three "overrides" were declared with the WRONG signature so MSVC APPENDED them as
  new slots instead of replacing the inherited slot in place:
  - `ValidToApplyThisToMapCoord` / `ApplyThisToMapCoord` used `const MapCoords*` (pointer) — base
    (`Object`) uses `const MapCoords&` (reference). Changed to `&`.
  - `BlocksTownClearArea() const` — base `Object::BlocksTownClearArea()` is NON-const (binary symbol
    `?BlocksTownClearArea@Object@@UAEIXZ`, byte-exact). A const member never overrides a non-const base, so it
    became a phantom new slot. Changed Mobile's to non-const. (Object's non-const symbol is byte-exact and must
    NOT change; Mobile's was not byte-exact, so this is safe.)
- **Living** (`Living.h`): the C++ class declared ~34 fewer virtuals than `LivingVftable`. Added 33 missing
  virtuals as `virtual` declarations in exact struct order at slots 0x878–0xb3c (SetFoodSpeedup, IsFoodSpeedUp,
  the Reaction-state block, the *ForChessGame block, IsPosValidForTurnAngle, …). Also fixed two override
  signatures that were appending phantom slots: `InitialisePhysics(const LHPoint*, …)` → `const LHPoint&`, and
  `GetBoundingSphere(LHPoint*, float*)` → `LHPoint&, float&` (match the `Object` base). Result: Living 720/720.

### The NON-VIRTUAL-but-in-vtable pattern (`GetFoodType`, `SetAge`) — `_vslot` placeholders
The binary places the addresses of a couple of NON-virtual members in the vtable: `??_7Object@@6B@`[0x668] =
`?GetFoodType@Object@@QAE…` (mangled **QAE** = non-virtual, byte-exact, and there IS a real
`call [reg+0x668]` to it), and `LivingVftable`[0x8d4] = `?SetAge@Living@@QAEXK@Z` (non-virtual). Declaring
these `virtual` in the C++ class would re-mangle their out-of-line definitions to **UAE** and break the
byte-exact match of those functions. So we KEEP them non-virtual and reserve their vtable slot with a
placeholder virtual (`GetFoodType_vslot` @0x668, `SetAge_vslot` @0x8d4). The placeholder occupies the slot so
every downstream virtual lands correctly; the real function stays QAE/byte-exact. (No expressive-C site
vcalls these by name, so the placeholder name costs nothing.)

### Ratchet (so it can't silently regress)
- `tools/vtable_drift.py --self-test` now asserts ZERO comment-drift AND exact slot counts for Object(535),
  Mobile(535), MobileWallHug(541), Living(720), plus computed `IsChild==0xAF8` / `IsDead==0xAF4`.
- `bw1-dtk/tools/probe_vtable.py --self-test` is the compiler-truth gate.
- Byte-exact floor recorded: **2952** (clean full rebuild: `rm build/BW1E142/src/Black/*.o` then build the
  Black `.o` targets — incremental builds under-report by ~1; always clean-rebuild before counting).

## Finishing a TU — the proven path (Abode example)
**asm-wrap transcription** from bw1-decomp `src/c` (the functions there are `asm("…")` blocks — byte-exact,
drift-immune). For Abode: **53 of 55** unported functions have asm-wrap source; 2 are trivial C one-liners.
Decomp practice: **match-first (asm-wrap), beautify-later (expressive C).**

## Contribution plan (git audit, tested 0-conflict)
1. **`pr/name-effectinfo` → upstream/main** — clean struct-field naming (proven 0-conflict). Ship first.
2. **`vtable_drift.py` → dtk-template** — clean file, BUT fix/document its unreliable drift-count first.
3. **Abode functions** — RE-AUTHOR onto upstream's empty `Abode.cpp` + a **per-TU `Object(cflags=["/G6"])`
   override** (NOT global `/G6`; NOT cherry-pick — they ride the whole port-banks foundation).
4. **DEFER:** global `/G6`, CRT reconstruction, port-banks bulk — architecturally incompatible with upstream's
   per-TU flags + `libcmt-lhlib-boundary`.

## iterate_dtk gate bug — FIXED (the metric was non-authoritative)
`iterate_dtk score` used `objdiff-cli diff`'s `match_percent`, which DIVERGES from the authoritative
report `fuzzy_match_percent` (== bytecount / measures.matched_functions). Proven: `??_GSetupButton`
reads 100.0 in the report but 99.55 via diff -> a lift loop gating on "iterate==100" REJECTS
genuinely byte-exact functions (false negatives) and churns. Fixed `score()` to read the report's
fuzzy (now agrees: ??_G 100=100). RULE: the REPORT is the only count/gate truth; `diff` is for
per-instruction inspection only.
