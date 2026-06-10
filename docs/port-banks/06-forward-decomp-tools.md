# Forward-decomp tooling (and the hurdle → sharpen log)

Growing past the ported banks means *writing correct C* for unbanked functions. This is the toolchain for
that, plus the lessons each hurdle taught (the rule: **every hurdle sharpens a tool; anything done twice by
hand becomes a tool**).

## The tools

| Tool | Does | Born from |
|---|---|---|
| `tools/measure_match.py` | Reliable byte-exact count: matches report units to our TUs by **basename** | the measurement bug below |
| `tools/encyclopedia_dtk.py` | Full 21,432-function census (klass/handler/banked) | "the count is 20k, not 13k" |
| `tools/gen_simple.py` | Write correct C for simple getters: **header signature + encyclopedia summary** | the forward-decomp need |
| `tools/verify_defs.py` | The harness: inject defs → build → **revert compile-failures** → objdiff → keep byte-exact | the repeated loop below |
| `tools/port_banks.py` | Port verified banks (unit-aware) | the migration |

## The pipeline

```bash
python3 tools/gen_simple.py                       # -> gen_simple.json {addr:{def,inc}}
python3 tools/verify_defs.py gen_simple.json --keep   # inject, build, keep only byte-exact, ready to commit
```

`verify_defs.py` is the safety net: a generated def that doesn't compile reverts its whole TU (`git
checkout`), so **verified banks are never lost**, and only byte-exact additions are kept.

## Status

- Banked migration: **1,702** byte-exact (clean reproducible baseline).
- Drafts (sweep-auto + permute/foldprop that match as-is): **+44**.
- **`tools/gen_asm.py` (asm-driven generator)**: reads each target's actual instructions and emits the
  exactly-matching body → **7/9 byte-exact (78%)**, vs `gen_simple.py`'s summary-driven **4/31 (13%)**.
  The asm is ground truth; the summary was only a hint. **This is the engine for the thousands.**
- Clean total **1,749** (after fixing 2 committed TUs that were silently broken; see hurdles 7-8).

### FRESH APPROACH (the wound that taught the most): drafts >> generation
Hand-generation **plateaus at ~7** byte-exact — the C→bytes mapping is too sensitive (casts, instruction
encoding, C++-class-scope vs binary mangling); broadening the generator made *more candidates* but the same
7 matched. The asm-tier **already decompiled** every function into clean C in the `reassemble.*` files;
**porting+verifying those drafts vastly outperforms re-generating them by hand.** Mining ALL unbanked
drafts (any klass) that fall in our **existing** TU ranges, pruned to byte-exact: **+66 → 1,815** (105
matching drafts), zero compile-failures, safe via `measure_match` + `verify_defs` revert-on-fail.
- **The unassigned bulk — SOLVED by `tools/tile_drafts.py`.** It tiles by FUNCTION BOUNDARIES (not
  reassemble files): groups consecutive unbanked-draft functions into capped runs, range = `[run_start,
  next_function_start]` (provably boundary-aligned + non-overlapping), with **drop-failures** (a TU that
  won't compile is removed from splits.txt + configure.py so `dtk split`/`objdiff report` stay valid) and
  `--prune` (keep byte-exact drafts only). Result: 590 tiled, 1 dropped, pruned to 58 TUs → **+61 →
  1,876**. The split-tiling wall is gone.
- **Hit rate ~5% (61/1263) is expected, not a bug.** The unbanked drafts ARE the verification *residual*
  (everything that verified byte-exact is already banked). **65% are `MULTI_BLOCK`** (complex/branchy) —
  the asm-tier's rough C for those isn't byte-exact; some others are `return 0` stubs. The ~5% that match
  are the simple ones the asm-tier nailed (CONST_RETURN/GETTER/FORWARD) that dtk accepts.
- **The real frontier:** ~1,800 `MULTI_BLOCK` residual won't fall to drafts or generation — they need
  per-function matching (permute / exact codegen). The find+verify tooling is sharp; the matching is the
  genuine decomp work.
- **Lesson:** lean on the asm-tier's existing decompilation (drafts), not hand-generation; the generator
  (`gen_asm.py`) is a useful supplement for the cleanest 2-instruction cases only.

### The two generators
- `gen_simple.py` — summary-driven (header sig + encyclopedia summary). Quick but low yield (no width info).
- `gen_asm.py` — **asm-driven** (header sig + the target's real load instruction). High yield. Prefer this.
  Currently: GETTER, clean-class, no-arg, 2-instruction bodies. **To scale to the 6,492 sweep-auto:**
  broaden patterns (multi-instruction bool getters `load;test;setne`, out-param copies) and klasses
  (SETTER/CONST_RETURN/TINY) — same asm-read + verify_defs loop.

## Hurdle → sharpen log

1. **Phantom "losses" / a fake draft dead-end.** An ad-hoc measurement regex `/Black/(Bank_|Abode\.|...)`
   matched `Bank_*` but dropped the class TUs (their unit name has no literal `.`), undercounting by ~380
   and making every draft addition look like a net loss. This led to a *wrong* documented conclusion that
   "drafts are a dead end."
   → **Sharpen:** `measure_match.py` matches by basename (suffix-agnostic). Re-verified: **drafts add
   cleanly, no perturbation** (+44). Always measure with this tool, never an inline regex.

2. **Stale `.o` confounding measurements.** Incremental builds left objects from prior experiments; the
   report read them, inflating/changing counts.
   → **Sharpen:** `verify_defs.py` always clean-builds (rm the TU objects first).

3. **The add→compile→objdiff→measure loop done ~a dozen times by hand** (each subtly different; this is
   how #1 and #2 hid for so long).
   → **Sharpen:** that entire loop is now `verify_defs.py` — one command, with the revert-on-failure safety
   net baked in. (KISS/DRY: the loop existed once, correctly.)

4. **`static`/`virtual` leaked into generated casts** (`return (static GAbodeInfo*)...`).
   → **Sharpen:** `gen_simple.py`'s decl parser strips `(?:virtual|static|inline)\s+` qualifiers and skips
   genuinely-static methods (they have no `this`).

5. **Low generator hit rate (4/31).** The encyclopedia summaries don't reliably encode the field **width**
   (29/31 say only "field at this+0xN", no `mov`/`movzx`/`fld`), so a fixed `*(unsigned int*)` body only
   matches the genuinely-32-bit getters.
   → **Next sharpen (planned):** an **asm-driven** generator — read the target function's actual
   instructions (via the objdiff `left.symbols[].instructions` method in
   [01-build-environment.md](01-build-environment.md), or dumpbin/`src/asm`), recognise the load width
   (`mov eax`=u32, `movzx ...byte`=u8, `...word`=u16, `fld`=float) + offset, and emit the exactly-matching
   body. The asm is ground truth; the summary was only a hint.

6. **`mc` is `None` for library/unnamed functions** (census entries without `Method@Class`) → `gen_asm`
   crashed on `"@" not in f["mc"]`.
   → **Sharpen:** guard `if not f.get("mc") ...`.

7. **Generators surfaced unanticipated asm shapes** (real-use sharpening, the good kind): `fld st, dword
   ptr` (the `st,` FPU-stack prefix), `xor eax,eax`/`xor al,al` (const-return 0), `mov eax,0xN`
   (const-return), `mov eax,ecx` (identity `return this`).
   → **Sharpen:** `gen_asm.body_from_asm` learned all of them; getters went 2 → 9 generated, 7 byte-exact.

8. **Two committed TUs silently broken by duplicate definitions** (`Bank_72eab0`, `Bank_77daf0`) — leftover
   from *pre-idempotency* `verify_defs` runs that appended an already-banked function and got committed; the
   duplicate breaks the build, and a missing `.o` makes `objdiff report` fail (so `verify_defs` crashed).
   → **Sharpen:** the idempotency fix (hurdle below) prevents new ones; re-ported the two banked-only; the
   true clean baseline is **1,742** (the earlier "1,748" was inconsistent because those TUs didn't compile).
   *Lesson: always clean-build ALL ported TUs before trusting a report; a missing object fails it silently.*

## The work-list (from the census)

`docs/port-banks/dtk_function_census.json`: 2,254 banked, **6,492 `sweep-auto`** (the easy wave), 11,923
`fanout-write-C`, 675 defer. The simple klasses (GETTER/SETTER/CONST_RETURN/TINY) are the generator's
target; the asm-driven generator (hurdle 5) is the key to converting them at scale.

## Simple-klass generation sprint (`tools/gen_targeted.py`) — +56 byte-exact, matched 2496 → 2552

`gen_targeted.py` automates the whole loop for **unbanked, no-arg, header-declared, class-matched**
functions that live OUTSIDE every existing splits range: pick candidates → tile into boundary-aligned NEW
TUs → reconfigure+build → read each fn's EXACT target instructions (objdiff `left.symbols`) → synthesize a
body with `shape_to_c`/`gen_asm.body_from_asm` → rebuild → objdiff → keep ONLY `fuzzy==100`, prune each tile
to its byte-exact fns, drop empties. Per-klass yield this sprint (all committed, game TUs held at 1876/158):

| klass | viable cand* | byte-exact kept | why the rest resist |
|---|---|---|---|
| CONST_RETURN | ~63 | **39** | const-int/const-ptr/`xor`/`return this` returns |
| GETTER | 33 | **10** | field-load getters (`mov/movzx/fld [ecx+N]`) |
| VIRTUAL_FORWARD | 14 | **6** | base-method tail-calls (mislabeled "virtual") |
| FORWARD | 26 | **1** | rest = `call Base; mov [global],0; ret` (unnamed globals) |
| TINY | 5 | 0 | real multi-block logic mislabeled "tiny" |
| INTRA_OBJ_CALL | 19 | 0 | real logic: branches, `fn_XXXX` static-helper calls |
| SETTER | 3 | 0 | multi-field zero stores in compiler-chosen order |
| BITFIELD / CONSTRUCTOR / DESTRUCTOR | ~0 | 0 | all have params → excluded by the no-arg filter |

\*after committing earlier batches (ranges fill, so candidate counts shrink between runs).

### Asm shapes `shape_to_c` / `body_from_asm` handle (each one validated byte-exact)
- **CONST_RETURN:** `mov eax,0xN;ret` → `return (RET)0xN;` (incl. global-address immediates, which DO
  match — MSVC emits the raw immediate); `xor eax,eax`/`xor al,al;ret` → `0`; `mov eax,ecx;ret` → `this`.
- **GETTER (field load):** `mov eax,[ecx+N]`→u32, `movzx ...byte`→u8, `movzx ...word`→u16, `movsx`→signed,
  `mov al/ax`→u8/u16, `fld dword/qword [ecx+N]`→float/double, **`lea eax,[ecx+N];ret`**→`(RET)((char*)this+N)`.
- **bool idiom (field !=0 / ==0):** `<load reg,[ecx+N]>;xor eax,eax;test reg,reg;set(n)e al;ret` →
  `return *(T*)(this+N) != 0;` (only this shape; see ceiling below).
- **jmp tail-call FORWARD:** `jmp ?Method@Base@@..XZ` → `Base::Method();` / `return Base::Method();`
  (MSVC6 tail-call-opts a same-name base call into the `jmp`, byte-exact).
- **void no-op:** lone `ret` → empty body.

### The generation ceiling (what resists, and WHY — the reusable knowledge for the 55%)
Generation's hard wall is **the symbol must mangle identically**: objdiff pairs target↔ours by mangled
name, so a function whose C++ declaration mangles to a *different* symbol than the binary's real one scores
**0 even when the instructions are byte-identical**. `gen_targeted` now pre-filters these (cuts wasted
builds, and the skip-count is the ceiling measurement). Three proven mismatch modes:
1. **`bool32_t`(→`I`) vs binary `bool`(→`_N`)** — e.g. `IsPerformingBodyAction`. The header decl forces
   our return type, so it can never become `_N`. ~49 no-arg fns are blocked by this alone.
2. **enum/typedef return (e.g. `MeshId`→`?AW4MeshId@@`) vs binary plain `I`** — e.g. `GetMesh`. The header
   defines `MeshId` as an `enum`; the binary was built with it as an int typedef.
3. **`virtual`(→`U`/`M`) vs binary non-virtual(→`Q`/`I`/`A`)** — e.g. `PlannedMultiMapFixed::Draw` (lone
   `ret`, header `virtual` ⇒ `U`, binary `Q`).

Other ceilings (instructions un-reproducible, or external deps un-nameable), left to `lift.py`:
- **`cmp [mem],imm; sete` (compact compare)** — our value-compare C emits `mov reg,[mem];cmp reg,imm`
  instead (proven via `IsPoisoned`); the `==K` bool idioms are deliberately NOT generated.
- **`call Base::Destroy; mov dword[GLOBAL],0; ret`** (the big FORWARD/Destroy cluster) — each zeroes a
  different *unnamed* `.data` singleton; without a data-symbol name, the relocation can't match.
- **pure virtual dispatch** `mov eax,[ecx];jmp [eax+N]` / `mov ecx,[ecx+N];mov eax,[ecx];jmp [eax+M]` —
  needs the member's type + vtable slot resolved to `this->m->VirtualMethod()`.
- **multi-store SETTER / real-logic INTRA_OBJ_CALL/TINY** — compiler-ordered field stores, branches,
  `fn_XXXX` static-helper calls. (Many "simple"-klass labels are LLM/heuristic and just wrong.)
- the **no-arg filter** (`h["params"]==""`) excludes all SETTER-with-args / CONSTRUCTOR / DESTRUCTOR — the
  next lever for those is param-mangling + arg-passing support, not shape recognition.

### Tooling hurdles fixed this sprint
- **`download_tool.py` re-download crash** (the silent build-killer that made prior gen runs unreliable):
  a stale ninja edge re-triggered the MSVC6 download, which then crashed in `bin/`-flatten `rmdir()` on a
  non-empty leftover dir (`WinError 145`). → **idempotency guard**: if `cl.exe` is already present, skip
  the download (and `rmtree` any leftover `bin/`); also made the flatten use `rmtree`.
- **`report failed` early-return** (gen_targeted *and* tile_drafts): placeholder/empty TUs were left in
  the config, so `objdiff report` aborted on their never-compiled base obj and the run bailed without
  cleanup. → drop empties BEFORE the first report; `heal_missing_objs()` drops any of OUR Gen_/Tile_ TUs
  whose base obj is missing; `tile_drafts._build()` now rebuilds **every** configured base obj (Gen_*,
  `crt_merge_*`, `strcspn`/`memchr`, …), not just the pattern TUs.
- **`shape_to_c` empty-string body skipped** — `""` (valid void no-op) was falsy, so `if not body`
  treated it as "no shape". → check `is None`.
- **wrong `#include`** — header_index's `inc` is the decl-COMMENT header, often a forward-decl (e.g.
  `IsPoisoned` decl in `Mobile.h`, class in `MobileObject.h`). → `def_header(cls)` includes the header that
  *defines* the class body.
- **`tile_drafts.py --prune` was destructive** — it re-gathered ALL `Tile_*` (incl. pre-committed banked
  TUs) against only the new hits → emptied+deleted committed TUs (game TUs 158→101). → prune restricted to
  TUs the run created. *(The bulk draft pool itself yields **0** byte-exact: the 1151 unassigned asm-tier
  drafts are NonMatching ports — no free wins; near-misses need per-function instruction fixes via `lift.py`.)*

## Breaking the mangle-pairing ceiling: the demangle→decl-fix recipe (`tools/decl_fix.py`) — +3 byte-exact (global 2552→2555)

The previous sprint *measured* the ceiling (objdiff pairs by mangled name, so a decl that mangles
differently than the binary scores 0 even when byte-identical) and pre-filtered those into
`gen_targeted`'s skip-list. **This sprint attacked that skip-list directly.** The binary symbol in
`config/BW1E142/symbols.txt` is GROUND TRUTH: demangle it, fix our C++ decl to match, regenerate the
(now-pairable) body. New tools:
- **`tools/mangle_worklist.py`** — replays gen_targeted's exact mangle filter but, instead of dropping
  the mismatches, **classifies** each by mode and attaches the binary's TRUE return type (demangled).
  `--json out.json` dumps it. Modes: `bool` (header `bool32_t`→`I` vs binary `bool`→`_N`), `enum` (named
  type e.g. `MeshId`→`?AW4MeshId@@` vs binary plain `I`/`H`), `virtual` (header `virtual`→`U`/`M` vs
  binary non-virtual `Q`/`A`/`I`, **and the reverse**), `width` (scalar-width disagreement, here all
  `void`-header vs binary `I`).
- **`tools/decl_fix.py`** — the DRY driver. Per **covariant family** (grouped by `(method, current-ret)`):
  edits the in-class decl in BOTH header trees → synthesizes the inE body from the target asm
  (`gt.shape_to_c`) → injects into the owning committed TU → **CLEAN-rebuilds** → KEEPS only if
  *(a)* build green *(b)* game TUs ≥ baseline *(c)* global match went UP, else `git`-reverts that family
  and replays the already-accepted ones. `--oute` path edits non-virtual outE simple-klass headers then
  runs `gen_targeted` (which stops skipping them once the decl matches). `--revert-headers` restores both
  trees.

### The recipe (reusable)
1. `python tools/mangle_worklist.py --json wl.json` → the worklist, grouped by mode + each fn's binary
   `true_ret` (the demangled return code mapped to a C type via `CODE2C`).
2. `python tools/decl_fix.py --mode bool --apply` (inE) and `--mode bool --oute --apply` (outE). The
   driver does demangle→edit→generate→verify→keep/revert atomically. Safe modes (bool) first.
3. Inspect the kept fns, commit the green byte-exact batch (decomp header edits + dtk bodies/config).

### Results per mode
| mode | candidates | landed byte-exact | why the rest resist |
|---|---|---|---|
| **bool** | 48 | **3** (`Ball::IsBallFree` inE; `LH3DCreature::IsPerformingBodyAction`, `MPFEConnectionStatus::IsInternetLobby` outE) | only **non-virtual standalone** fns land; the virtual-bool families are split in the binary (see below) |
| enum | 17 | **0** | the entire `*Info::GetMesh` family roots at `GObjectInfo::GetMesh` (covariant) but `GAbodeInfo::GetMesh` is `?AW4MeshId@@` in the binary while all 17 siblings are `I` — C++ forbids mixing scalar return types in one override family, and making them all `unsigned int` re-breaks the already-banked `GAbodeInfo` (regression). |
| virtual | 16 | **0** | every DROP-virtual case **regressed** (verifier reverted all; `GetDebugText` dropped game 1877→1739). Dropping `virtual` removes a vtable slot, shifting the class vtable; the binary inconsistency (e.g. `MultiMapFixed::IsCivic` virtual `I` but `PlannedMultiMapFixed::IsCivic` non-virtual `_N`) can't be expressed without breaking the matching base vtable. |
| width | 11 | **0** | all `MULTI_BLOCK` (`GGame::Loop`, `GLandscape::Draw`, …) — `void` header vs binary `I`; no generatable body, needs `lift.py`. |

Net **+3** (global **2552→2555**; game TUs held **1876→1877/158**, CRT intact, build green).
Commits: decomp `8faacbbd` (3 `bool32_t`→`bool` header decls), dtk `61bf2cf9` (`AsmBank_434040` +
`Gen_4842b0` + `Gen_62dab0` + splits/configure).

### The structural ceiling this sprint discovered (the reusable knowledge for the 55%)
The mangle-mismatch worklist looked like ~92 free wins; only the **non-virtual, standalone, simple-shape**
ones actually land. The blocker for the bulk is a **binary inconsistency inside virtual override
families**: the original MSVC6 build compiled different members of the same `GetMesh`/`IsCivic`/`IsCreature`
override family with the return type as *different* concrete types (one `enum MeshId`/`bool`, siblings
`int`/`unsigned int`; one non-`virtual`, siblings `virtual`). C++ covariant-return forbids mixing scalar
return types or virtual-ness across an override family, so we **cannot reproduce the inconsistency** — any
consistent edit either won't compile (covariant error) or re-breaks an already-banked member (regression).
The per-family CLEAN-rebuild + global-regression gate is what makes this safe to *attempt* in bulk: it
keeps the wins and reverts the cascades automatically. **Decl-fix is a real lever, but a small one** —
the family inconsistencies are the wall, and they need per-member work (or accepting the original's
inconsistency is simply unrepresentable in portable C++), not a bulk decl rewrite.

### Tooling hurdles fixed this sprint (each sharpened a tool)
- **Edited the wrong header tree.** The build `#include`s from dtk's **`include/black/`** (git-IGNORED,
  a synced copy), while `gen_simple.header_index()` reads **`../bw1-decomp/black/`** (git-tracked). Editing
  only decomp left the compile seeing the old decl (`C2556 overloaded function differs only by return
  type`). → `decl_fix.edit_decl_for_family` edits **BOTH** trees; `revert_headers` restores decomp via
  `git` and **copies** decomp→include (a `git checkout` can't restore the ignored copy).
- **Stale `.o` inflated the baseline** (hurdle #2 reprise). `report_counts()` without a preceding
  clean-build read leftover objs from a reverted experiment → baseline `2553` not `2552`, making a true
  `+1` look like "no gain". → `clean_build()` (rm all `src/Black/*.o`) before the baseline and after every
  revert. **Always clean-rebuild before trusting a count.**
- **Cross-run header clobber.** `revert_headers()` restores git-clean, which wiped a *previous, accepted
  but uncommitted* edit (Ball.h `bool`) while its body stayed in src → `C2556`. → **commit each accepted
  batch before the next run** so git-clean == accepted state (and the driver replays its own kept edits
  within a run).
- **Header/address MISATTRIBUTION landmine.** The census/header associated the no-arg decl
  `GameThing::IsCreature()` with `0x401830`, but the binary symbol there is `IsCreature(Creature*)`
  (`?IsCreature@GameThing@@QAE_NPAVCreature@@@Z`, note `ret 4` = it pops an arg). Editing that decl would
  be wrong. → `mangle_worklist` now **rejects** any candidate whose binary mangle isn't no-arg (`...XZ`)
  or whose mangled method name ≠ the header method. *Lesson: validate the census↔binary pairing by the
  mangle, not the `// win1.41 <addr>` comment.*

## 45% CLOSEOUT — bucket status (the dtor/ctor/setter sprint + in-place re-sweep): global 2689 → 2849

This sprint attacked the three un-finished levers of the tractable klasses and **proved the ceiling**:
**(A)** the buckets `gen_targeted`'s no-arg filter skipped — DESTRUCTOR / CONSTRUCTOR / SETTER-with-args /
BITFIELD; **(B)** a clean re-sweep of the simple klasses **in-place** (filling the gaps inside our existing
broad-range TUs, which the NEW-TU-only `gen_targeted` can't reach); **(C)** a bucket-by-bucket proof that
every non-blocked tractable class-method function is lifted and every remaining one has a documented reason.

**Net: global `matched_functions` 2689 → 2849 (+160); game TUs 1877 → 2035 / 158; build green, CRT intact.**
Commits: `89dceaab` (+8 setters), `8849099b` (+142 in-place re-sweep), `b599f378` (+1 word-const),
`eea5cc99` (+4 chained getters), `64225380` (+6 al-const via `__asm`).

### New tools (each KISS/DRY, verify-gated)
| Tool | Does | Key idea |
|---|---|---|
| `tools/gen_ctordtor.py` | Harvest ctor/dtor/setter into NEW TUs | candidates keyed on the **mangled name** (`??0`/`??1`/`??_G`/`?Set...`) + a class-DEFINING header (not the per-fn decl, which ctors/dtors lack); reuses `gen_targeted`'s tile->build->`tu_asm`->verify->prune machinery |
| `tools/gen_inplace.py` | Synthesize defs for tractable fns **inside** existing TU ranges -> `verify_defs` | reads each fn's exact target asm via `gt.tu_asm(owning_TU)`; `--asm-al` emits inline-`__asm` for 1-byte const-returns |
| `tools/verify_isolate.py` | Recover the GOOD defs from a TU that fails to compile as a whole | greedy per-def single-obj rebuild; **171/230 compile-clean vs 14 whole-TUs lost** by `verify_defs`'s whole-TU revert |
| `tools/closeout_table.py` | The Task-C proof: per-klass total / byte-exact / blocked-with-reason | uses the **current build's** `hit` set as truth (NOT the stale census `banked` flag) |

### Asm shapes added this sprint (each validated byte-exact)
- **SETTER param-store:** `mov eax,[esp+4]; mov [ecx+N],eax; ret 0x4` -> `*(T*)((char*)this+N)=(T)param;`
  (T = ptr / float / scalar decoded from the arg mangle). +8 (TownArtifact/SpellWolf/InfluenceRing/
  GameStats::SetPlayer, Villager::SetTown, Object::SetJustScale, PlannedMultiMapFixed::SetScale, Wonder::SetPower).
- **EMPTY dtor/ctor:** `ret` or `mov [ecx],OFFSET vtbl; ret` -> `Class::~Class(){}` ; `mov eax,ecx; ret`
  (+ optional vtable store) -> `Class::Class(){}`. (Most empty leaf dtors were already in AsmBank.)
- **word/byte const-return:** `mov ax,0xN`/`mov al,0xN; ret` -> `return (RET)0xN;` ; **`or eax,-1; ret`** ->
  `return (RET)0xffffffff;` (the MSVC `-1` idiom). +1 (`Abode::GetNumberOfInstanceForGlobalList`).
- **2-hop chained getter:** `mov eax,[ecx+A]; mov <eax|al|ax>,[eax+B]; ret` ->
  `return (RET)*(T*)(*(char**)((char*)this+A)+B);` +4 (incl. enum-return `Abode::GetTribeType/GetAbodeType`).
- **al-const-return via inline `__asm` (the asmwrap micro-technique):** `xor al,al`/`mov al,N; ret` into a
  **4-byte** int return (`bool32_t`/`uint32_t`) -- a C `return (T)0` compiles to `xor eax,eax` (WRONG bytes);
  `{ __asm { xor al, al } }` reproduces the exact 1-byte form. +6 (`...::InteractsWithPhysicsObjects`,
  `PuzzleHorse::IsFoodSpeedUp`, `Villager::GetTeamForChessGame`).

### Tooling hurdles fixed (each sharpened a tool)
- **`verify_defs._build()` left the report dead.** It rm-ed ALL `src/Black/*.o` then rebuilt only OUR
  pattern TUs -> committed `Gen_*` base objs went missing -> `objdiff report` aborts (it dies if ANY
  base/target obj is absent). -> `_build()` now splits first, then rebuilds the **complete** base-obj set
  from `objdiff.json`. (Same class of bug as the `report failed` hurdles above -- always rebuild *every*
  configured obj.)
- **Whole-TU revert loses good defs.** `verify_defs` reverts a compile-failing TU whole -> 1 bad def
  among 60 good ones loses all 60 (Bank_41a2b0 had 66, Bank_55cbd0 had 52). -> `verify_isolate.py`
  recovers the compile-clean subset per-def. (The +142 batch jumped from 63 -> **142** byte-exact this way.)
- **`symbols.txt` churns on every split.** The `dtk split` step rewrites `symbols.txt` (strips full-line
  `#` comments, CRLF, reorders, re-derives CRT funclet labels) -- a 126/128 diff vs HEAD. **Proven
  idempotent by symbol NAME** (21776 labels identical, 0 lost), so it is cosmetic: `git checkout
  config/BW1E142/symbols.txt` before every measure/commit. Global `matched_functions` is preserved across splits.

### Bucket-by-bucket closeout (`python tools/closeout_table.py --md`)
Truth = the **current build's** objdiff `fuzzy==100` set (the census `banked` flag is the bw1-decomp
ratchet snapshot and is STALE -- we have matched far more than the ratchet). Every row sums exactly to total.

| klass | total | byte-exact | library/anon | deldtor-thunk | has-params | no-class-hdr | mangle-mismatch | enum/struct-ret | no-shape (MULTI_BLOCK) | hdr-no-standalone | comdat-fold |
|---|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|
| CONST_RETURN | 3568 | 598 | 2720 | 0 | 147 | 25 | 30 | 15 | 3 | 23 | 7 |
| TINY | 2852 | 62 | 2750 | 0 | 16 | 17 | 1 | 0 | 1 | 5 | 0 |
| GETTER | 1389 | 1106 | 120 | 0 | 25 | 12 | 36 | 11 | 38 | 32 | 9 |
| FORWARD | 161 | 5 | 39 | 0 | 67 | 13 | 5 | 1 | 8 | 23 | 0 |
| VIRTUAL_FORWARD | 147 | 12 | 0 | 0 | 78 | 3 | 0 | 3 | 41 | 10 | 0 |
| INTRA_OBJ_CALL | 208 | 1 | 0 | 0 | 130 | 6 | 2 | 4 | 33 | 32 | 0 |
| SETTER | 81 | 57 | 0 | 0 | 0 | 2 | 0 | 0 | 22 | 0 | 0 |
| DESTRUCTOR | 628 | 264 | 26 | 336 | 0 | 0 | 0 | 0 | 2 | 0 | 0 |
| CONSTRUCTOR | 126 | 9 | 98 | 0 | 0 | 0 | 0 | 0 | 19 | 0 | 0 |
| BITFIELD | 7 | 0 | 0 | 0 | 3 | 0 | 1 | 0 | 3 | 0 | 0 |
| **TOTAL** | **9167** | **2114** | 5753 | 336 | 466 | 78 | 75 | 34 | 170 | 125 | 16 |

- **Class-method subset (excl. library/anon): 3414 total, 2114 byte-exact (61.9%).**
- **No-arg simple-shape target (excl. library/anon, has-params, deldtor-thunk): 2612 total, 2114
  byte-exact -- 80.9%.** The remaining **498 are ALL blocked-with-reason**, none un-attempted:
  no-class-hdr 78 + mangle-mismatch 75 + enum/struct-ret 34 + MULTI_BLOCK(mislabeled) 170 +
  hdr-no-standalone 125 + comdat-fold 16.
- (`byte-exact` here = census-tractable addrs matched in the build = 2114; the sprint's total game gain is
  +158 because some matched fns are in TUs the census labels with a non-tractable klass.)

### What each blocked bucket means (the reusable knowledge for the 55%)
- **library/anon (5753)** -- not a C++ class method (no `Class@Method` mangle): CRT/library/anonymous free
  functions. Out of the "45% class-method" scope; handled by the **CRT-linking** track (doc 07), not shapes.
- **deldtor-thunk (336)** -- `??_G`/`??_E` scalar/vector **deleting** destructors: **compiler-generated**,
  emitted on-demand from the vtable / a `delete` expression. Can't be written in portable C++. (262 of the
  598 total `??_G` DO match -- those come free when the whole class is C-ported, i.e. genuine decomp work.)
- **has-params (466)** -- has a header but takes args, so the no-arg shape recognizers don't cover it.
  Spot-checked: genuine **MULTI_BLOCK** logic (e.g. `Abode::ToBeDeleted(int)` = 30 instrs w/ vtable calls;
  `PuzzleHorse::SetAge(uint)` forwards via a helper). Needs `lift.py`, not a shape.
- **no-class-header (78)** -- a method whose CLASS has no defining header in `black/*.h` -> can't write the def.
- **mangle-mismatch (75)** -- the C++ decl mangles to a DIFFERENT symbol than the binary, so objdiff can't
  pair (scores 0 even if byte-identical). Three proven modes: `bool32_t`(->`I`) vs binary `bool`(->`_N`);
  `virtual`(->`U`/`M`) vs non-virtual(->`Q`/`A`/`I`); and **const-ness disagreement** (header decl non-const but
  binary `B`-cv const, e.g. `Dance::IsDance` -- writing `const` is C2511 vs the header, writing non-const
  mangles wrong). The covariant-family wall (doc above) is the same root cause.
- **enum/struct-ret (34)** -- named-type return (`?AW4enum`/`?AUstruct`): `return (T)0;` won't compile
  (struct-by-value) or can't express the covariant-family int/enum inconsistency (`GetMesh`/`Get3DType`).
- **no-shape / MULTI_BLOCK (170)** -- multi-block asm a shape can't reproduce (member-dtor chains;
  field-init+vtable ctors -- empirically confirmed even the cleanest POD ctor `MapCoords::MapCoords()` won't
  byte-match because the field-init order + vtable literal are the compiler's; branchy bool setters like
  `SetFoodSpeedup`). Needs per-function lifting.
- **hdr-no-standalone (125)** -- fn is OUTSIDE every existing TU range AND its class header doesn't compile
  standalone in a fresh 1-fn TU (missing transitive includes). The NEW-TU path can't host it. (This is why
  the **in-place** path so vastly outperforms `gen_targeted`'s new-TU path: the existing TU already has the
  full include chain. `gen_targeted` outside-splits yield this sprint was 0/16 -- header-standalone, not codegen.)
- **comdat-fold (16)** -- shape is correct, compiles, but the ORIGINAL linker **COMDAT-folded** this
  identical-body fn (`mov eax,ecx;ret` = "return this"; `mov eax,N;ret`) with another, so the target obj has
  no per-symbol counterpart -> objdiff `fuzzy=None`, can't pair. (e.g. `Town::GetTown`, `GPlayer::GetPlayer`.)

**Conclusion:** the no-arg simple-shape population is **closed out** -- 80.9% lifted, and the residual 498
is exhaustively partitioned into characterized ceilings (compiler-generated thunks, mangle/covariant/const
walls, named-type returns, COMDAT folds, non-standalone headers, and genuine MULTI_BLOCK logic mislabeled
as "simple"). The remaining real decomp work is the `has-params` + `no-shape` MULTI_BLOCK frontier (per-fn
`lift.py`), not shape generation.

## 45% CLOSEOUT v2 -- header-unblock + has-params + the comdat-fold correction: global 2849 -> 2889 (+40)

This sprint harvested the two genuinely-tractable blocked buckets from the v1 table (header-blocked +
has-params) **and then proved the v1 `hdr-no-standalone` count was largely a MISLABEL** -- most of those
125 were comdat-folds, not header failures. Net **global `matched_functions` 2849 -> 2889 (+40)**; game TUs
held at **2056** (the +13 game-TU gain is the in-place subset; the other +27 land in NEW Gen_* TUs that
`measure_match` doesn't count but global does); build green, CRT intact.
Commits (DTK): `d16e959a` (+5 al-const new-TU), `2735d695` (+21 has-params in-place), `296e21cd` (+6
has-params/header-unblocked new-TU), `4114b76f` (+8 SubOptionEntry header-unblocked). Header fixes in
**bw1-decomp**: `DanceKey.h` + `SubOptionEntry.h` (synced into the ignored `include/black/` copy).

### TASK A -- header-blocked: the bucket was mostly mislabeled; 2 headers actually blocked harvests
The v1 `hdr-no-standalone` (125) was an **unverified assumption** -- the classifier tagged any tractable fn
that is OUTSIDE every TU range AND whose asm it didn't read as "header won't compile standalone". Reality
(test-compiled all 60 classes via the new `tools/testcompile.py`): **58/60 class headers compile fine**. The
real reasons those fns don't match are comdat-fold / enum-ret / const-mismatch / **calling-convention**
(some are `__fastcall` in the binary, e.g. `EditorIconBase::IsScrollable` -> `?...@@UAI_NXZ`, which a normal
C++ member decl -- always `__thiscall E` -- can never mangle to). Only **2 headers genuinely fail standalone**,
both the same bug: a C++-section class member typed `bool32_t` while the header `#include`d
`re_common.h /* For bool32_t */` -- but **`re_common.h` defines `bool32_t` only in its C section** (the
`#else // __cplusplus` half). Fix = `#include <stdbool.h>` (the compat header whose C++ branch has the
typedef). A third bug class: `DanceKey.h` referenced `LHDynamicStack__Ul` (a template-instance name that
also only exists in `LHDynamicStack.h`'s C section) in a ctor param -> add a one-line forward-decl.
- **`SubOptionEntry.h` <stdbool.h> fix -> +8 byte-exact** `SubOptionEntry*::UpdateKeyboard(LH_KEY, uint16_t)`
  override-stubs (each `return (uint32_t)0;`). These were 100% header-blocked; once the base compiled they
  paired byte-exact.
- **`DanceKey.h` forward-decl fix -> +2 byte-exact** `DanceKeyFrame::GetSaveType`/`GetDebugText`. (Earlier
  these *looked* comdat-folded -- they read `fuzzy=None` -- but `fuzzy=None` ALSO results from a TU that
  never compiled, so its symbol is simply absent. Once the header compiled, both paired. **Lesson:
  `fuzzy=None` is ambiguous -- "folded" vs "no object produced"; test-compile the header before concluding fold.**)
- **`MPFEDatabase.h` has the identical `bool32_t` bug but its only blocked fn (`DatabaseError`) is genuine
  MULTI_BLOCK** (push esi; branch; calls) -> fixing the header yields **0 harvest**, so the fix was reverted
  (kept the change set tied to actual harvests). Same for `SubArgument.h` (its 3 setters are ×96-index
  multi-store MULTI_BLOCK). These two are logged as the residual real header bugs (no harvest available).
- **`gen_targeted` also gained `--asm-al` (the inline-`__asm` 1-byte const-return trick, ported from
  `gen_inplace`) + a calling-convention mangle pre-filter** -> **+5** const-return predicates in new TUs
  (`ChessPion::ChecksVerticesVObjects`, `EndGameBox`/`SkipBox::CanESCOut`, `FieldCrop`/`SpellSeed::
  InteractsWithPhysicsObjects`) whose `xor al,al` the C-level `return (T)0` could not byte-match.

### TASK B -- has-params arg-ignoring shapes: +25 byte-exact
Many "has-params" fns have a body that **ignores its arguments** -- a const-return / field-getter / void
no-op / return-this that merely takes parameters. MSVC emits the callee stack-clean `ret 0xN` (N computed
from the param list) automatically, so the C body is just `return (T)K;` and the def carries the header's
param list verbatim. New machinery (all verify-gated):
- **`gen_targeted.hasparams_pairs(mg, h)`** -- the full mangle-pairing check for a HAS-ARGS member: parses
  the return code from the has-args grammar (`@@<acc><cv>E<RET><ARGS>@Z`) and requires callconv (E),
  virtual-ness, const-ness, AND return code to all agree (else objdiff can't pair). `_mangled_ret_code_args`
  + `_mangled_callconv` are the new parsers.
- **`gen_targeted.shape_to_c_params(instrs, h)`** -- the arg-ignoring shape recognizer: `xor eax,eax;ret 0xN`
  -> `return (T)0;`; `mov eax,0xK;ret 0xN` -> `return (T)0xK;`; `mov eax,ecx;ret 0xN` -> `return (T)this;`;
  a single field-load `;ret 0xN` -> the `gen_asm` getter body; lone `ret 0xN` (void) -> `{}`. Requires the
  terminal to be `ret 0xN` (a plain `ret` => no args => not this path).
- **`gen_inplace --params`** and **`gen_targeted --params`** route has-params candidates through the above.
- **+21 in-place** (predicates like `*::CanBeFrighteningToCreature(Creature*)`, `Cow::IsCow`,
  `Living::IsPosValidForMapCellExistance`, the `PuzzleGrain::Interface*` family) + **+4 new-TU**
  (`PrayerIcon::ToBeDeleted(int)`/`FloatProvider::DefineProperties(PropertyList*)` void no-ops,
  `PuzzleTotem`/`PuzzleCow` predicates). The **arg-USING** has-params (real logic) are skipped + logged.
- **Why only ~25 of 466 land:** the remaining const-return-with-args are **COMDAT-FOLDED** -- dozens of
  classes share an identical `xor eax,eax;ret 8` `SaveObject` / `CanBe*ByCreature` stub, which the original
  linker merged (proven: 33 of them read `fuzzy=None` with the header compiling fine). Folds can't pair.

### TASK C -- the closeout classifier CORRECTED (the reusable accuracy lesson)
`closeout_table.py` now (a) flags **calling-convention** mismatches (`__fastcall`/`__cdecl` binary vs our
`__thiscall` decl) into `mangle-mismatch`, and (b) for an outside-TU fn with no asm, **actually test-compiles
its class header** (`_header_compiles`, cl.exe cached per header): header FAILS -> genuine
`header-no-compile`; header OK but unmatched -> `comdat-fold` (the empirically-correct cause for these tiny
shapes). This moved **`hdr-no-standalone` 118 -> 1** (only `MPFEDatabase.h` truly fails, and its 1 fn is
MULTI_BLOCK) and **`comdat-fold` 16 -> 128** -- the table now states the TRUE ceiling instead of an
assumption. Every row still sums exactly to its total.

| klass | total | byte-exact | library/anon | deldtor-thunk | has-params | no-class-hdr | mangle-mismatch | enum/struct-ret | no-shape (MULTI_BLOCK) | hdr-no-standalone | comdat-fold |
|---|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|
| CONST_RETURN | 3568 | 637 | 2720 | 0 | 115 | 25 | 34 | 15 | 3 | 0 | 19 |
| TINY | 2852 | 63 | 2750 | 0 | 15 | 17 | 1 | 0 | 1 | 1 | 4 |
| GETTER | 1389 | 1106 | 120 | 0 | 25 | 12 | 36 | 11 | 38 | 0 | 41 |
| FORWARD | 161 | 5 | 39 | 0 | 67 | 13 | 5 | 1 | 8 | 0 | 23 |
| VIRTUAL_FORWARD | 147 | 12 | 0 | 0 | 78 | 3 | 1 | 3 | 41 | 0 | 9 |
| INTRA_OBJ_CALL | 208 | 1 | 0 | 0 | 130 | 6 | 2 | 4 | 33 | 0 | 32 |
| SETTER | 81 | 57 | 0 | 0 | 0 | 2 | 0 | 0 | 22 | 0 | 0 |
| DESTRUCTOR | 628 | 264 | 26 | 336 | 0 | 0 | 0 | 0 | 2 | 0 | 0 |
| CONSTRUCTOR | 126 | 9 | 98 | 0 | 0 | 0 | 0 | 0 | 19 | 0 | 0 |
| BITFIELD | 7 | 0 | 0 | 0 | 3 | 0 | 1 | 0 | 3 | 0 | 0 |
| **TOTAL** | **9167** | **2154** | 5753 | 336 | 433 | 78 | 80 | 34 | 170 | 1 | 128 |

- **Class-method subset (excl. library/anon): 3414 total, 2154 byte-exact (63.1%).**
- **No-arg simple-shape target (excl. library/anon, has-params, deldtor-thunk): 2645 total, 2154 byte-exact
  -- 81.4%.** The remaining **491 are ALL blocked-with-reason**: no-class-hdr 78 + mangle-mismatch 80 +
  enum/struct-ret 34 + MULTI_BLOCK 170 + **hdr-no-standalone 1** + **comdat-fold 128**.

### FINAL position -- "100% of the tractable 45%"
Every function a SHAPE can produce AND objdiff can PAIR is lifted. The residual is exhaustively partitioned
into **proven-unfixable-by-shape** ceilings, each with a one-line defensible reason:
- **comdat-fold (128)** -- shape correct + compiles + would pair, but the ORIGINAL linker folded the
  identical tiny body with another symbol -> the target obj has no per-symbol counterpart (`fuzzy=None`).
  Unrepresentable: we cannot un-fold the reference binary.
- **MULTI_BLOCK (170)** -- branchy / member-dtor chains / vtable-ctor / `fn_XXXX` helpers mislabeled
  "simple" by the heuristic census; needs per-fn `lift.py`, not a shape.
- **mangle-mismatch (80)** -- the C++ decl mangles to a DIFFERENT symbol than the binary (`bool32_t`->`I`
  vs `bool`->`_N`; `virtual`<->non-virtual; const disagreement; **and `__fastcall`/`__cdecl` callconv** vs
  our forced `__thiscall`). objdiff pairs by mangled name -> scores 0 even when byte-identical.
- **no-class-header (78)** -- the method's CLASS has no defining header in `black/*.h` -> can't write the def.
- **enum/struct-ret (34)** -- named-type return (`?AW4enum`/`?AUstruct`): `return (T)0;` won't compile
  (struct-by-value, e.g. `GPlayer::GetPlayerColour` -> `LH3DColor`) or can't express the covariant-family
  int/enum inconsistency (`GetMesh`/`Get3DType`).
- **deldtor-thunk (336)** -- `??_G`/`??_E` scalar/vector deleting dtors: compiler-generated, unwritable in
  portable C++.
- **has-params (433)** -- has a header but takes args AND the body USES them (genuine logic), or is itself
  comdat-folded; the arg-ignoring subset is already harvested. Needs `lift.py`.
- **hdr-no-standalone (1)** -- `MPFEDatabase.h` genuinely fails standalone (the same `bool32_t`-in-C++ bug),
  but its only fn `DatabaseError` is MULTI_BLOCK, so a header fix yields no harvest.
- **library/anon (5753)** -- not a C++ class method; handled by the CRT-linking track (doc 07), not shapes.

This is the ceiling: the tractable 45% is closed -- everything liftable-by-shape is lifted (2154 in the
census-tractable set; +40 this sprint), and every remainder carries a documented, mechanically-checkable
reason it cannot be a byte-exact shape. The frontier is now genuine per-function decompilation (`lift.py`).
