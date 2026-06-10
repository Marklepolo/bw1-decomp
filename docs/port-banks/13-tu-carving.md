# 13 — Carving a single-class TU out of the Abode multi-class blob

## Why
BW1E142's `0x401000-0x407840` is ONE dtk unit (`Abode.cpp`) holding many interleaved classes. An inherited
virtual that is **overridden through the chain** (e.g. `MultiMapFixed::GetCollideData`, declared at
Object/Fixed/MultiMapFixed) is referenced only by *its* class's vtable, which `Abode.cpp` never
instantiates → it compiles to an **empty symbol (0%)** and can never be lifted in place. Giving that class
its own TU makes its vtable (hence its overridden virtuals) emit. This is the detector→carve→lift loop.

## Hard constraints (verified)
- **No holes:** every dtk unit is ONE contiguous `.text` range (0 of 224 units have >1 range). MultiMapFixed
  (`0x401490-0x401640`) sits in the *middle* of Abode → carving it is a **3-way split**:
  `AbodeFront 0x401000-0x401490` + `MultiMapFixed 0x401490-0x401640` + `Abode 0x401640-0x407840`.
- Methods route to the unit whose range contains their **target address**.

## Tool: `tools/carve_tu.py` (built this session)
Slices a TU's `.cpp` by the `// win1.41 <addr>` comment each method carries, routes each method-block to
the output TU whose range contains its address, and prints the splits.txt + configure.py edits. Dry-run by
default; `--apply` writes the `.cpp` files.
```
python tools/carve_tu.py Abode 0x401000:0x401490:AbodeFront 0x401490:0x401640:MultiMapFixed 0x401640:0x407840:Abode
```
**Validated dry-run:** 426 method-blocks → AbodeFront 10, MultiMapFixed 2, Abode 414. (The 2 MMF blocks are
`SetPower`+`GetPercentRepaired` — the only MMF methods *defined* in Abode.cpp; the other ~5 byte-exact MMF
methods are **inline in MultiMapFixed.h**, emitted via COMDAT.)

## Apply procedure
1. `python tools/carve_tu.py Abode <ranges> --apply`  (writes AbodeFront.cpp, MultiMapFixed.cpp, rewrites Abode.cpp)
2. splits.txt: replace Abode's single `.text` line with the 3 ranges; keep `.rdata`/`.rdata$r`/`.data` with
   the `Abode` entry (carved TUs get `.text`-only; their rodata refs become cross-unit relocations).
3. configure.py (~line 251): add `Object(NonMatching, "Black/AbodeFront.cpp")` and `.../MultiMapFixed.cpp")`.
4. `python configure.py` (re-splits via dtk + regenerates build.ninja), then `ninja`.

## Risks to VERIFY before trusting the carve (a wrong carve REGRESSES byte-exact methods)
1. **Inline-method emission (the big one):** the Base/GAbodeInfo/GObjectInfo methods at `0x401000-0x401400`
   are **header-inline**, currently byte-exact via Abode.o's COMDAT. After carving, **AbodeFront.o** must
   re-emit them — it only will if AbodeFront.cpp instantiates those classes' vtables (it defines FixedObject
   methods, so FixedObject emits; Base/GAbodeInfo/GObjectInfo inlines may NOT unless referenced). **Check the
   global matched count does not drop** after `configure.py + ninja`; if AbodeFront regresses, the front
   classes need their own carves or a forced reference.
2. **.rdata/.data:** carved getters here have no rodata refs (verified by disasm), so `.text`-only is safe;
   re-check if a carved method references a string/const.
3. **Preamble duplication:** carve_tu copies the FULL include preamble into each new `.cpp` (always compiles;
   wasteful). If Abode.cpp ever grows file-scope statics/helpers ABOVE the first `// win1.41`, they'd
   duplicate across TUs (ODR) — currently the preamble is includes only.

## Payoff
Once MultiMapFixed.cpp exists + its vtable emits, the **overridden-virtual getters** (`GetCollideData` and
peers) can be lifted there (they were blocker-class-1 in-place). Validate by lifting `GetCollideData`
(`return collide_data;`, `mov eax,[ecx+0x78]`) → it should go byte-exact in the MMF unit.

## Apply-attempt findings (learned the hard way, reverted clean)
- **The project PRE-REGISTERS class TUs as empty NonMatching stubs.** configure.py has TWO Object groups:
  the active group (~line 251: Abode.cpp, AbodeInfo.cpp, ...) and a big ALPHABETICAL NonMatching group
  (~line 532+) listing ~hundreds of class names as empty `.cpp` stubs -- incl `MultiMapFixed.cpp`,
  `MultiMapFixedInfo.cpp`, `PlannedMultiMapFixed.cpp`. So full per-class decomposition is ANTICIPATED;
  a carve should **populate the existing stub**, not create a new file.
- **configure.py validates uniqueness:** adding a 2nd `Object("Black/MultiMapFixed.cpp")` failed with
  `Duplicate object name Black/MultiMapFixed.cpp`. -> don't add an Object that already exists.
- **carve_tu clobbered the tracked empty stub** (it blindly wrote MultiMapFixed.cpp). FIXED: carve_tu now
  has a clobber guard (reports existing outputs, aborts apply without --force).

## Corrected carve recipe (for MultiMapFixed)
1. `carve_tu.py Abode ... --force` to populate the EXISTING src/Black/MultiMapFixed.cpp stub (+ the front).
   The front (0x401000-0x401490) still needs a home -- its FixedObject methods (0x401400-0x401490) could go
   to a `Fixed`/`FixedObject` stub if one exists; the inline Base/GAbodeInfo methods (0x401000-0x401400)
   are the REGRESSION RISK (see below).
2. splits.txt: add the MultiMapFixed `.text 0x401490-0x401640` range (the stub currently has NO range) and
   shrink Abode appropriately. Front needs its own contiguous range too (no holes).
3. configure.py: do NOT add a duplicate Object; if needed, MOVE `MultiMapFixed.cpp` from the NonMatching
   group to the active group (or leave it -- it's already registered).
4. `python configure.py` (re-split) + `ninja`; **verify global matched count does NOT drop**.

## STILL-OPEN risk before this is safe
The front 0x401000-0x401400 is header-INLINE Base/GAbodeInfo/GObjectInfo methods currently byte-exact via
Abode.o's COMDAT. Splitting the unit there may stop them emitting (regression). The clean carve likely
needs the front classes carved into THEIR stubs too (Base.cpp/GAbodeInfo.cpp/GObjectInfo.cpp if they
exist), so each class's vtable+inlines emit in its own TU. That makes this a MULTI-carve, best done as a
focused sweep with regression-gated verification -- not a single drive-by. carve_tu + the stub list are
the tools; the dtk reconfigure is the gate.

## Reconfigure plumbing (learned the hard way; carve attempt #2, reverted clean @2959)
- **The build config chain:** configure.py -> `config/<VER>/config.yml` (configure.py reads ONLY this, via
  `config.config_path`). config.yml line 5 = `splits: config/BW1E142/splits.txt` -> so splits.txt IS the
  live split source, but **reached through config.yml**, not by configure.py directly.
- **configure.py defaults to BW1E100** (DEFAULT_VERSION=0). Running it with NO args writes a wrong-version
  ~3KB STUB build.ninja (only tool-download rules). **Always `python configure.py -v BW1E142`.** Recovery
  from the stub: just re-run with `-v BW1E142` (build.ninja is untracked/generated, 774KB when correct).
- **THE REMAINING BLOCKER:** with splits.txt 3-way (AbodeFront/MultiMapFixed/Abode) + an AbodeFront Object
  + populated .cpp files, `configure.py -v BW1E142` regenerated a FULL build.ninja but with **NO compile
  rules for AbodeFront.o / MultiMapFixed.o**. So configure.py emits compile rules from the dtk SPLIT UNITS
  (the per-unit target objects dtk produces from splits.txt), and that split did NOT regenerate the new
  units -- likely the split output is CACHED and not re-run on a splits.txt edit. NEXT: find the
  force-resplit / cache-invalidation (delete the split-output cache under build/BW1E142/ and/or a configure
  flag), OR confirm whether NonMatching stub objects are excluded from compile-rule emission until promoted.
- **Verified no-regression recovery:** restore the 4 files (Abode.cpp/MultiMapFixed.cpp/splits.txt/
  configure.py) from backups + `rm AbodeFront.cpp` + `configure.py -v BW1E142` -> global matched back to 2959.

## carve_tu.py is now pinned (sharpen-with-tests, per request)
3 bugs fixed against real use: (1) win1.41 regex (addrs have NO 0x prefix); (2) clobber guard (it had
overwritten a tracked stub); (3) --force not stripped from argv (crashed parsing). Added `--self-test`
(5 checks: preamble isolation, block count, no-0x+0x addr parsing, address routing, block-text carry) --
ALL PASS. Run `python tools/carve_tu.py --self-test`.

## RE-SPLIT CRACKED (local trace + research agent, both agree)
**Rule emission (project.py):** `add_unit` iterates the units in **`build/<VER>/config.json`** (the dtk
SPLIT output), NOT `config.libs[].objects`. A TU gets a `cl` compile rule IFF: (1) a unit with that name
exists in config.json, AND (2) its `.cpp` source exists on disk. The `Object(NonMatching, ...)` entry only
supplies cflags/source metadata that attach WHEN a matching config.json unit is found. Matching vs
NonMatching is irrelevant to rule emission (all 224 working TUs are NonMatching).

**Why config.json was stale (root cause):** the ninja `split` edge is
`build config.json: split config.yml | dtk.exe` -- its only explicit input is config.yml. splits.txt is
*supposed* to become a dep via the depfile `build/<VER>/dep`, but **that file was EMPTY (0 bytes)** -- a
broken/incomplete depfile from a prior split -- so ninja had NO `splits.txt -> config.json` edge and never
re-split on a splits.txt edit. Stale config.json -> new units absent -> no `cl` rule.

**THE FIX (reliable, PROVEN):**
```
rm build/<VER>/config.json   # invalidate the split cache
ninja                        # split rule regenerates config.json from config.yml->splits.txt,
                             # then the `configure` generator rule reruns project.py -> build.ninja gets
                             # the new units' cl rules, then builds.
```
Verified: after this, config.json gained the AbodeFront/MultiMapFixed units and they COMPILED (AbodeFront
42 fns, MultiMapFixed 23 fns appeared in the report). `configure_args = -v BW1E142` is recorded so the
auto-reconfigure uses the right version. (Note: full `ninja` also tries to LINK the exe and fails on a
missing LHAudio-linked.dll -- a pre-existing local issue; byte-exact verification only needs the `.o` +
`objdiff-cli report`, so build the specific `.o` targets, not the default link.)

**HARDENING (agent rec, NOT yet applied -- build-infra, test before trusting):**
`config.reconfig_deps = [splits.txt, symbols.txt]` in configure.py so edits auto-trigger reconfigure;
and/or ensure dtk writes a proper depfile. Until then, the manual `rm config.json` is the reliable path.

## But a BARE carve REGRESSES -13 (measured, then reverted to 2959)
Mechanically the carve builds, but global dropped 2959->2946: MultiMapFixed 1/23, AbodeFront 23/42 (Abode
413/543). Cause = the carved `.cpp` files don't emit the class's **inline/COMDAT methods** that Abode.o
used to provide (the carved TU doesn't instantiate the class's vtable, so its inline virtuals aren't
emitted), AND (agent gotcha) the `.rdata`/`.data` ranges weren't re-partitioned to the carved TUs.
=> A NET-POSITIVE carve = split + **LIFT the class's methods into the carved TU** (including its KEY
function -- the first non-inline non-pure virtual -- so MSVC emits that class's vtable + its inlines) +
re-partition the data ranges. The split alone is not free; it trades the COMDAT-provided inlines for the
ability to lift the class's own (incl. overridden-virtual) methods.

## DECISIVE: carving MMF is the WRONG tool (the key-function rule)
Carve attempt #3 dug into WHY the bare carve regressed and WHY GetCollideData never emits. Root cause:
**MultiMapFixed is a SCATTERED class** -- its methods live in several units: the 0x4014xx cluster (in the
Abode blob), 0x422xxx, and the MAIN cluster at **0x52exxx** (`GetDoorPos`@0x52e370, GetInfluence,
CheckMapObject, Built, Repaired...). `GetDoorPos`@0x52e370 is MMF's FIRST virtual = its **vtable key
function**, and it lives in **Bank_52c330.cpp** (0x52c330-0x53bd60).

MSVC emits a class's vtable -- and the definitions of its inherited-but-overridden virtuals (like
`MultiMapFixed::GetCollideData`) -- ONLY in the TU that defines the **key function**, and references them
as `extern` everywhere else. So:
- `GetCollideData` never emitted in Abode.cpp (0%) because Abode.o references it `extern`; its definition
  belongs to MMF's key-function TU (Bank_52c330.cpp), where GetDoorPos is -- and GetDoorPos is undecompiled
  there, so MMF's vtable doesn't emit ANYWHERE yet -> GetCollideData is 0% everywhere.
- The 0x401490 carve regressed -13 because that cluster's MMF methods were COMDAT-emitted via Abode's ctor
  (??0Abode@0x401350) instantiating Abode's vtable; splitting them off the ctor's TU breaks that, and they
  can't re-emit in a cluster that lacks both ??0Abode AND the key function.

### Correct unlock (NO carve, NO regression)
To emit MMF's overridden virtuals, lift MMF's **key function `GetDoorPos`** in its home TU
**Bank_52c330.cpp** (where 0x52e370 lives). That makes MSVC emit MMF's vtable there, after which
`GetCollideData` + the other overridden MMF virtuals can be lifted in Bank_52c330.cpp and will emit.
This is plain IN-PLACE lifting -- the carve was never needed for MMF.

### When IS carve_tu the right tool?
Only for a class whose methods are CONTIGUOUS in one range AND whose construction / key-function is IN that
range (so the carved TU self-contains its vtable instantiation). A scattered base class like MMF is not
that. carve_tu + the cracked re-split (rm config.json) remain valid for such targets; MMF isn't one.
