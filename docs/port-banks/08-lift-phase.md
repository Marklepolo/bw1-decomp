# Lift phase — the 55% MULTI_BLOCK frontier (per-function matching)

Scope: the functions no generator/shape can produce — branchy `MULTI_BLOCK` logic where you read the
target's GPR/FPU instruction stream and write C that MSVC6 compiles to the *exact* bytes. Tools:
`lift.py` + `gpr.py` + `fpu.py` + `structmap.py` + `permute.py` + `idioms.py` (+ `iterate`/`nearmiss`).
100% IS reachable (dtk's compiler == the original MSVC6 SP5); it's a sustained per-function grind, not a push.

## Step 1 — map the core structs (DONE)
**Hurdle → sharpen (the first bug this phase found):** `structmap.py` globbed `<ROOT>/black/*.h`, which
exists in **bw1-decomp** but NOT in **bw1-dtk** (dtk's headers are in `include/black/`). So in dtk it parsed
**0 classes** — the earlier "Object@0x68 → no field" was really "no headers loaded." Fixed: glob `black/`
**or** `include/black/`. Now parses **915 classes** in both repos (mirrored, md5-identical — dtk `e60d2f7a`,
decomp `0f3dae5c`).

Core-hierarchy field coverage (the derived classes hold the logic, and they're well-mapped):

| class | fields | exact | to offset |
|---|---:|---:|---|
| Creature | 154 | 141 | 0x12c4 |
| Town | 72 | 65 | 0xf24 |
| Living | 36 | 30 | 0xdc |
| Villager | 20 | 12 | 0x12c |
| Animal | 17 | 17 | 0x144 |
| Abode | 16 | 11 | 0xb9 |
| GameThingWithPos | 10 | 10 | 0x4a0 |
| Object | 10 | 6 | 0x50 |
| MobileObject | 5 | 5 | 0x64 |
| GameThing | 5 | 5 | 0x10 |

(Object's own fields stop at 0x50 — it's a thin base; the depth is in the derived classes. Biggest mapped
classes overall: `LH3DCreature` 3784, `CHand` 157, `PlayerActionState`/`Creature` 154, `GGame` 102.)

**Usage in the lift loop:** `python tools/structmap.py Creature 0x12c` → field at that offset; or wire it via
`gpr.py --struct Creature` / `fpu.py --struct Creature` to auto-annotate `[reg+0xN]` while reading asm.

## Step 2 — near-miss drafts: harvest the asm-tier drafts at 70-99% fuzzy (DONE — characterized; the
residual is structural, not per-function-C-tweakable). Baseline held: **2056/158 game TUs, global 2889**.

**Hurdle → sharpen (the dtk-path bug this step found):** the shared `iterate.py`/`verify.py`/`permute.py`
are wired to **bw1-decomp's** flow (`cmake --build cmake-build-presets/objdiff`, objdiff-cli **on PATH**).
In **dtk** the build is ninja (`bw1-decomp/.venv/Scripts/ninja.exe build/<VER>/src/Black/<TU>.o`) and
objdiff-cli is at `build/tools/objdiff-cli.exe` driven by `-p . -u runblack-decrypted/Black/<TU> <sym>`.
So `iterate.py --diff` died with "objdiff-cli not found." **Sharpen:** added **`tools/iterate_dtk.py`** —
the dtk-native edit→ninja-one-`.o`→objdiff-one-symbol→keep-or-revert loop (same idea as iterate.py, dtk
plumbing). This is a **dtk-specific** tool (like the 35 other 45%/CRT tools), so per the 00-TOOLKIT sync
rule it lives ONLY in dtk — NOT mirrored to bw1-decomp (whose iterate.py already works for its cmake flow).
  * `python tools/iterate_dtk.py diff  <TU> <MangledSym>`   — per-instruction T-vs-ours diff (left=TARGET)
  * `python tools/iterate_dtk.py score <TU> <MangledSym>`   — current match_percent
  * `python tools/iterate_dtk.py try   <TU> <MangledSym> --old "C" --new "C"`  — edit/build/rescore; auto-revert unless it strictly improves (so the tree never regresses).

### The 36 near-misses, classified (none closable by per-function C edits — they're the MULTI_BLOCK residual)
Ran `objdiff-cli report generate` + listed every draft fn in [70,100). The 36 fall into 4 residual classes,
each verified by reading the per-instruction `iterate_dtk.py diff` (left=TARGET, right=ours):

1. **Bitfield getters (~14): the `xor eax,eax` signature.** Every `Is*`/`Get*Flag` one-liner
   (`CanBePickedUp@{Tree,Living,MobileObject,MobileStatic}`, `IsCannotBePickedUp/IsInScript/IsObjectInMap
   @GameThingWithPos`, `IsChild@Villager`, `IsSkeleton@Living`, `IsSpeedUp/IsPoisoned/IsAPotFromABuildingSite
   @Pot`, `GetShouldNotBeAddedToPlanned@Abode`, …) differs by EXACTLY one instruction: TARGET prepends
   `xor eax, eax` before the partial-register load (`mov ax/al,[ecx+OFF]`); ours omits it. That `xor`+partial-load
   is MSVC6's **bitfield-member read** signature. PROVEN un-reachable from C: tried every cast/width/sign/local
   variant via `iterate_dtk.py try` (`(uint16_t)~*…`, `unsigned int v=…`, `(int)(unsigned char)…`, byte locals)
   — **none** emit the `xor`. The real fix is to declare a true `unsigned f : N;` **bitfield** in the struct
   header (`field_0x24`/`field_0x7c`), which is a **Step-3 by-class structural migration** that touches 100+ TUs
   including GameThingWithPos.h (high regression risk; deferred — must be validated against the FULL report).
2. **Save family (~7) (`Save@{GameThing,GameThingWithPos,Object,Fixed,MultiMapFixed}`):** two residuals —
   (a) **data-global naming**: TARGET `mov eax,[0xbec990]` vs ours `mov eax,[_DAT_00bec990]` → `DIFF_ARG_MISMATCH`.
   0xBEC990 (the save-checksum flag, `extern "C" bool32_t DAT_00bec990`) has **no symbol in symbols.txt** and
   sits **inside an existing labeled blob** (`lbl_00BEC980`..`??_R0?AVGameOSFile@@@8`@0xBEC9B8), so it can't be
   cleanly named without restructuring the .data split; same value both sides — a harness symbol artifact, not a
   codegen diff. (b) **arg/`this` scheduling** in the `GameOSFileWriteCheckSum` macro's `file.Write(&v,4,NULL)`:
   TARGET defers the `lea`/`mov ecx` until after the const pushes; ours hoists it. Macro-reconstruction fidelity;
   not nudged by temp-vars or call-qualifier changes.
3. **Float getters (`GetDesireToBeRepaired`, `GetPercentAbodeFull*`):** `DIFF_ARG_MISMATCH` on the float const —
   TARGET `fld [0x8aa390]` vs ours `fld [__real@4@3fff8000…]`. Same value; objdiff just can't fold our MSVC
   80-bit `__real@` literal symbol against the target's named .rdata constant. Constant-pool naming artifact (+ a
   minor `push edi`/`xor edx` schedule shuffle).
4. **Pure scheduling (`Save@Fixed`, 90%, the single closest):** ONE swap — TARGET `push eax; mov ecx,edi` vs
   ours `mov ecx,edi; push eax` for the `__thiscall file.WritePtr(town_artifact)`. The this-ptr/arg push order is
   fixed by MSVC's calling-convention codegen; tried temp-var, unqualified call, `GameOSFile::` qualify — no move.

**Net:** 0 drafts closed to 100% this step (global stays 2889) — but the frontier is now *mapped*: the cheapest
wins are NOT in this draft set; they require (1) the bitfield struct migration and (2) the .data/.rdata constant-
pool symbol naming, both of which are batch/structural levers (Step 3 + a `dataglobals`/RTTI-split pass), so a
single coordinated change lifts a whole family at once rather than one fn at a time. `iterate_dtk.py` is the loop
that proves/disproves each candidate in seconds and auto-reverts, so it's the engine for those batches too.

## Step 3 — by-class leaf-first: lift a mapped class's leaf methods → its callers (high-fan-in first).
Two batch levers identified in step 2 that each close a near-miss FAMILY at once:
- **Bitfield migration:** declare the real `unsigned : N` bitfields in the well-mapped structs (GameThingWithPos
  field_0x24, Abode field_0x7c, …), rewrite the `Is*`/`Get*` getters to read the named bitfield, validate the
  WHOLE report (not just the fn) so no currently-matched accessor regresses. Expected: the ~14 `xor eax,eax`
  near-misses → 100% together.
- **Constant/global symbol naming:** give 0xBEC990/0xBEC994 and the .rdata float constants real split symbols
  (needs a .data/.rdata split-boundary fix so the addr isn't swallowed by `lbl_…`), which clears the
  `DIFF_ARG_MISMATCH` half of the Save/float-getter families.

## Step 3 — LEVER VALIDATION BY HAND (the cheap-experiment discipline paid off)
Validated each lever on real functions via `iterate_dtk.py try` (edit->build->score->auto-revert) BEFORE
dispatching agents. Findings that CHANGE the plan:

### Lever A (bitfield family) — CORRECTED. The fix is the BRANCH FORM, not a struct migration.
The ~14 near-misses differ from TARGET by a leading `xor eax,eax` (a redundant zero-extend the original
kept; dtk's MSVC6 optimizes it away). Empirically (auto-reverting tries):
- **BYTE bit-getters (uint8_t field): CLOSE with `if (field & MASK) return 1; return 0;`** -> emits
  `xor eax,eax; mov al,[x]; shr eax,N; and eax,1` = byte-exact. PROVEN +2: `Abode::GetShouldNotBeAddedToPlanned`
  (80->100), `GameThingWithPos::IsObjectInMap` (75->100). The agent's proposed **struct bitfield gives 80%**
  (union uint8_t : N tested -> no xor) -- DISPROVEN. `(field&MASK)!=0`, casts, `?:`, divides -- all 80%.
  => NO struct migration, NO 100+-TU blast radius, NO regression risk. Just a per-getter C rewrite.
- **WORD bit-getters (uint16_t field): a 98.8 codegen WALL.** ~60 forms tried. The `xor` only appears with
  the bare `(field & mask) >> N` form -- but that forces an 8-bit `and al,...`, while TARGET has `and eax,1`
  (32-bit). Adding `& 1` / branch / `!=0` to get the 32-bit and REVERTS the xor (back to 80%). The two
  requirements are mutually exclusive in dtk's MSVC6 -> not closable by C source (likely a /O codegen nuance).
  Word getters are seeds at 98.8, not wins. (`IsInScript` bit9, `IsCannotBePickedUp` bit13 left at clean 80%.)

### Generalize + sharpen (next)
The BYTE branch form is a proven, safe, repeatable lever -> a `byte-bit-getter -> branch-form` rewriter
(scan for `return (FIELD & MASK) != 0;`/`(... & 1)` where FIELD is uint8_t, rewrite to the branch form,
verify each, keep 100%). Skip uint16_t/uint32_t fields (the 98.8 wall). This closes the byte slice of the
xor-eax family at once. The WORD wall needs a compiler-flag investigation, deferred.

## Step 4 — the /G6 RE-SWEEP (post-`3454d107`). The WORD wall + the branch-form hack are GONE.
The `/G6 (PentiumPro)` flag (`configure.py` cflags_base, commit `3454d107`) makes MSVC6 emit the
partial-register-stall `xor eax,eax` before partial-register loads/compares. The committed `+37` was a
pure-flag windfall (it flipped ALREADY-WRITTEN getters from <100 to 100 with NO source change) and
`920414c2` then reverted the Step-3 branch-form hacks back to natural C. This step RE-SWEEPS to harvest the
family the generators previously SKIPPED (synthesized as plain loads that scored <100 pre-/G6, so the
verify-gate dropped them).

**Baseline reconfirmed (clean full rebuild + report): game 2093/158, global matched 2926.**
GOTCHA banked: do NOT `ninja -t clean` — it deletes the `copy_obj`/`merge_crt_obj` CRT split objects
(`crt_merge_*.o`) and the downloaded `objdiff-cli.exe`, after which `report generate` dies "os error 2"
(file not found) and `measure_match` silently reads a STALE report (showed a phantom 2056/2889 = baseline
minus the +37). Rebuild objects by targeting the full `^build/.../src/Black/*.o` set (the `.exe`/`.dll`
link fails on a missing `LHAudio-linked.dll` — that's an unrelated env artifact; objdiff only needs the
`.o`s). Also: `tile_drafts.py`/`gen_targeted.py` rewrite `configure.py` with CRLF (no content change) and
the dtk-split step (`ninja config.json`) rewrites `config/<VER>/symbols.txt` with ~250 lines of CRT-symbol
REORDER churn — both are pre-existing build artifacts (present at pristine HEAD too); `git checkout` them
before committing.

### What the generators yielded post-/G6 (the honest result: the auto-shapes are nearly exhausted)
- `gen_targeted.py` (UNASSIGNED-outside-splits, klasses BITFIELD/GETTER/CONST_RETURN/TINY/SETTER): the
  candidate pool is only ~28 fns; almost all are `unhandled shape` or compile-fail. **+1** after the tool
  sharpen below.
- `tile_drafts.py` (1145 asm-tier drafts -> 529 TUs): **0** newly-100. The asm-tier drafts are MULTI_BLOCK;
  /G6 doesn't close them. (Confirms the Step-2 finding: the cheap wins are NOT in the draft set.)
- `gen_inplace.py` (INSIDE existing TU ranges): 245 synth, but **197 are ALREADY matched** (the +37 etc.)
  and the remaining 48 are virtual struct-by-value/pointer getters that compile-fail (unrelated to /G6).

### The actual /G6 lever found: the `field ==/!= K` compare-bool getter (NEW shape)
The previously-`unhandled` shape `mov reg,[ecx+OFF]; xor eax,eax; cmp reg,K; set(n)e al; ret` is EXACTLY
what `return field == K;` compiles to under MSVC6 **/G6** (the load form + the now-emitted `xor`). Step 2/3
had DELIBERATELY EXCLUDED the `==K` form from `gen_asm._bool_idiom` because pre-/G6 our codegen omitted the
`xor` (the docstring even says "the `cmp reg,K` (==K) form is deliberately excluded"). /G6 removed that
wall. **Sharpen:** extended `gen_asm._bool_idiom` to also accept `cmp reg,K` -> `return field ==/!= 0xK;`
(safe: targets that instead use the compact `cmp [mem],imm` simply lack the 5-instr `load;xor;cmp reg,K`
shape, so it never mis-fires). Harvested **`PFootball::IsPlaytimeStarted`** (`field@0x7c == 3`, new
`Gen_643960.cpp`). `gen_asm.py` is a dtk-only forward-decomp tool (NOT in bw1-decomp) -> no mirror needed.

### Two singleton bit-getters closed by NATURAL C (the byte branch-form hack is now unnecessary)
Both inside `Abode.cpp` (game-counted), both were at 0% (undefined), both byte-exact under /G6 with the
plain comparison form (verified via `verify_defs.py --keep`):
- `GameThing::IsAvailable` (`0x401810`): asm `xor eax,eax; mov al,[ecx+0xa]; not al; and eax,1` =
  `return (*(uint8_t*)(this+0xa) & 1) == 0;`
- `Abode::ShouldFootpathsGoRound` (`0x403ef0`): asm `mov al,[ecx+0x58]; and al,2; xor ecx,ecx; cmp al,2;
  setne cl; mov eax,ecx` = `return (*(uint8_t*)(this+0x58) & 2) != 2;`

### RESULT
**game 2093 -> 2095 (+2, the two Abode singletons), TUs 158/158 (no regression); global matched
2926 -> 2929 (+3: +PFootball in Gen_643960).** Clean full rebuild + report confirmed. Per-klass: BITFIELD
+2 (the Abode bit-getters), GETTER +1 (PFootball `==K`). The /G6 shift specifically enabled the `field==K`
compare-bool shape and the byte bit-getters' NATURAL comparison forms (no `__asm`/branch-form hack).
**The auto-generatable simple-getter reservoir is now empirically EXHAUSTED** (every remaining `unhandled`
shape across our TUs at size<=0x20 is a COUNT-1 singleton or a MULTI_BLOCK/call shape) — further coverage
is the per-function MULTI_BLOCK grind (Step 1-3 toolkit), not a generator re-run.
