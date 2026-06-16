# Genuine byte-exact LINKED lift — playbook

How to land a *genuine* lift (your `.cpp` is actually linked into the byte-exact exe) rather than a
**carved/gap-filled false positive** (the exe is byte-exact whether or not your code is used). First
proven on **`MPFEConnectionStatus::IsInternetLobby`** (BW1E142) — the first genuine byte-exact linked
B&W function.

## 0. Why this is hard (the trap)
`dtk shasum` ("N files OK") proves the dtk's CARVE of the original is faithful — it stays byte-exact
even if your `.o` is never linked (a Matching unit with no working split is silently carved). So a
green shasum alone is NOT proof. The only proof is the **empty-body test**: change the function body;
the exe MUST change. See [[baw-genuine-lift-baseline]], [[baw-matching-tu-completeness-gate]].

## 1. The calibration platform — a byte-exact whole-exe baseline (WSL)
Only a working whole-exe build can run the empty-body test. Get one first:
- Set **every Black unit to `NonMatching`** in `configure.py` (only the 7 zlib + 3 libcmt units stay
  `Matching`). In particular GJPersistent and CreatureInitialSourceInfo MUST be NonMatching — linking
  them throws lld-link `duplicate symbol` on shared carved COMDAT (`??_7Base`, RTTI). This is a LOCAL
  verification config (uncommitted), like the other workarounds in CLAUDE.md.
- `python3 configure.py --map --version BW1E142 && ninja`
- Confirm: `build/BW1E142/runblack-decrypted.exe` sha1 == `9c9aea96f046911ab1b7e496fae511ed5ebbfefe`
  (== orig), `dtk shasum -c config/BW1E142/build.sha1` all OK.

## 2. Pick a SELF-CONTAINED candidate
A lift can only link if its `.o` emits **only its own unique strong symbols** (the zlib model). Reject:
- **Polymorphic** classes (any `??_7`/`??_R0`/`??_G`/`_vfunc`, or a virtual method — mangling access
  char `U`/`E`/`M`). Their RTTI/vtable duplicate the carve → link fails.
- A class deriving from a **shared carved base** (Base, GBaseInfo, …) → duplicate `??_7Base` etc.
- **Guarded file-scope globals** (`__sinit_<tu>_cpp` in mac; the 15-byte run-once dtor guard our
  toolchain can't emit — see CISI).
- **STL** TUs (`<sstream>`/`<string>` — wibo `lstrcpynA` gap + header-inline mismatch).
- Functions whose body **calls** a symbol our C++ can't name: debug-param mangling (`GData::Rand` is
  `?Rand@GData@@QAEIJ@Z` = 1-param symbol but 3-param body → needs `asm("…")`, which **MSVC6 cl.exe
  rejects in C++** → `C2290`), old cfront mangling (`_LHRand__FlRU`), or an **incremental-link thunk**
  (`call 0x5106b0` jmp-thunk). These need symbol-forcing we can't do cleanly.
- A function whose **slot contains inter-function linker filler** you can't reproduce (e.g.
  `IsLanLobby`'s slot ends with a dead `call 0x4017f9` — the dtk places your `.o` for the whole block
  so the filler must match; pick a sibling whose slot trailing is plain nop).

**Ideal = trivial getters / pure math with NO external calls and clean MSVC mangling.** Find them with
`tools/selfcontained_scan.py` (strict non-poly classes). Confirm each function with
`tools/crack.py 0xADDR --disasm`. Use mac_symbols.tsv for the authoritative name + sibling list
(nothing is "unnamed").

## 3. Write the lift
- One `src/Black/<TU>.cpp` `#include`-ing the existing co-located `.h` (the C++ class). Body in clean
  C++ only (no `__asm`, no pointer/offset casts).
- **Header convention (mandatory for EVERY function in EVERY header):** an address comment directly
  above each declaration, EXACTLY:
  `// win1.41 {08x win_addr} mac {08x mac_addr} {demangled mac name}`
  e.g. `// win1.41 0041a2b0 mac 1007c6d0 Animal::SetStateSpeed(void)`. Win addr from
  `config/BW1E142/symbols.txt`; mac addr + demangled name from `reference/mac_symbols.tsv` (we only
  annotate v1.41). If you add a function to a header, add its comment too.
- **No `m_` prefix** for members — use the plain field name (e.g. `type`, not `m_type`).
- Worked example (`MPFEConnectionStatus.cpp`):
  ```cpp
  #include "MPFEConnectionStatus.h"
  bool MPFEConnectionStatus::IsInternetLobby() { return type == LOBBY_TYPE_INTERNET; }
  ```
  `type==0` compiles to `mov edx,[ecx]; xor eax,eax; test edx,edx; sete al; ret` — byte-exact.

## 4. Make it a Matching build target (the dtk mechanism)
A unit only gets a `cl` rule + is placed when it has a **splits.txt block**. The block must cover the
**whole symbol** (the dtk errors if a split "ends within symbol"). For a partial-TU lift, claim only
the function(s) you provide; the dtk carves the rest of the original `.cpp`'s `.text`.
- `configure.py`: flip the unit to `Object(Matching, "Black/<TU>.cpp")`.
- `config/BW1E142/splits.txt`: add (TAB-indented)
  ```
  Black/MPFEConnectionStatus.cpp:
  	.text       start:0x0062DAC0 end:0x0062DAD0
  ```
  (full symbol range from symbols.txt — here IsInternetLobby is 0x62DAC0..0x62DAD0: 10 B code + 6 B
  nop, all one symbol).
- `python3 configure.py --map --version BW1E142`

## 5. The un-gameable gate (all four)
1. `python3 tools/exact_gate.py <TU>` → `ALL EXACT` (per-fn byte match, relocs masked).
2. `ninja` builds + links clean (no `duplicate symbol`) and the progress shows your unit **linked**
   (e.g. "8/37 files linked", up from the 7 zlib).
3. `dtk shasum -c config/BW1E142/build.sha1` → runblack OK (sha1 9c9aea96 == orig).
4. **Empty-body test** — the proof of LINKED-not-carved: change the body (e.g. `return false;`),
   `rm` the `.o`, `ninja`. The exe sha1 MUST change (here → `f603d1d1…`, shasum FAILED). Restore the
   real body; sha1 returns to 9c9aea96. If the exe stays byte-exact with a wrong body, it was CARVED
   → false lift. (`tools/verify_lift.py` automates 1-3 + prints the check-4 procedure.)

## 5b. Worked lift #3 — `Point2D::GetNormSq` (an SDK TU, MatchingFor 1.42)
The third genuine lift, and the first in a **Lionhead SDK** unit (LH3DLib). Key differences from the
`Black/` lifts:
- **Unit lives outside `Black/`:** `Object(MatchingFor("BW1E142"), "Lionhead/LH3DLib/development/LHPoint.cpp")`
  (source `src/Lionhead/LH3DLib/development/LHPoint.cpp`). The header is found via `/I include` →
  `include/lionhead/lh3dlib/development/LHPoint.h` (the REPAIRED copy; the `src/` copy is the stale
  auto-gen with duplicate decls — don't include that one). No header repair was needed.
- **`MatchingFor("BW1E142")`** instead of `Matching`: claims the match for 1.42 only; 1.00/1.10 stay
  NonMatching (the function `MatchingFor(*versions)` returns `config.version in versions`). Use this
  whenever you've only verified one version.
- **Body:** `float Point2D::GetNormSq() { return x*x + y*y; }` → the exact MSVC6 `/O2` x87 schedule
  (`fld;fld;fld st0;fmul st1;fld st2;fmul st3;faddp;fstp st2;fstp st0;ret`), 20 bytes at 0x6115F0.
- **COMDAT auto-folds:** the compiler emits it `Communal`; it links with no duplicate-symbol error
  (the COMDAT path — this is why a member of a shared struct links where non-COMDAT class methods dup).
- Full TU notes (tech + game): `docs/tu/LHPoint.md`.

## 5c. Running the gate in WSL (the actual platform)
exact_gate/objdiff and the per-fn check run on Windows, but the **whole-exe build + empty-body test**
run in **WSL on ext4** (case-sensitive — avoids the NTFS auto-split filename collision,
[[baw-windows-case-collision-fix]]). A ready worktree with the toolchain pre-downloaded:
`~/bw1-rtti` (non-git copy; has `build/compilers`, `build/tools`, ninja). Recipe:
1. Copy the `.cpp`, add the `configure.py` Object line + the splits block (the WSL update mode
   **preserves** the block — unlike a plain Windows `configure.py` which regenerates/wipes it).
2. `python3 configure.py --version BW1E142` then `ninja build/BW1E142/src/<unit>.o` (compiles in-build).
3. `ninja -k 0` → links `runblack-decrypted-linked.exe`.
4. **Empty-body differential** (the proof): read the bytes at the function VA with `pefile`
   (`pe.get_data(VA-ImageBase, size)`); they must equal the orig. Then change the body, `rm` the
   `.o`, rebuild, re-read — the bytes at that VA MUST change ⇒ linked, not carved.
   ⚠️ Do **not** rely on the whole-exe sha1 here: the unresolved libcmt/CRT link gap makes the linked
   exe non-byte-exact AND the link is non-deterministic between identical builds. The deterministic,
   decisive signal is the **per-VA bytes**, not the exe hash.

## 6. Next candidates (and their known hurdle)
- `MPFEConnectionStatus::IsLanLobby` (`type==1`) — function byte-exact; its slot has the
  `call 0x4017f9` filler, so needs the block to stop at the real fn end or the filler reproduced.
- `Point2D::GetNormSq` / `Normalize` (LHPoint.h) — pure FP math, clean mangling, no external calls;
  watch the x87 schedule (`return x*x+y*y` may need the exact temp form).
- More trivial getters across the strict-non-poly list (`selfcontained_scan.py`).
- Whole-TU (all functions of a small non-poly `.cpp`) once the per-fn pattern is solid.

## 7. Verified gotchas (2026-06-14, maintainer/collab-confirmed — read before lifting)
- **symbols.txt VC++ names are SYNTHESIZED guesses, not ground truth.** The Windows binary is stripped;
  the `?…@@…` names are generated from the Mac signatures, which loses the return type (CodeWarrior
  doesn't encode it → guessed), can have the wrong param count (Mac sig ≠ Windows), and the generator
  may have bugs. On a "mangling mismatch": derive the correct mangling from the real signature and
  **RENAME the symbol in symbols.txt** — do NOT use `asm("…")` labels (MSVC6 rejects them in C++; the
  maintainer rejects them too). Tools: `mangle_check.py` (header decl vs symbol), `sig_arity.py`
  (binary `ret N` vs declared params — thiscall/stdcall only; cdecl/static needs a call-site extension).
- **Release call-site tracking macros (NOT a debug build).** `__FILE__`/`__LINE__` are passed to certain
  functions (the RNG, the overloaded `operator new ??2@YAPAXIPBDI@Z`) via a macro at every call site; the
  consuming code is `#ifdef`'d out but the args are still pushed, so the real release signature has the
  extra params (e.g. `GameRand(long,char*,uint)`). This is why the release is full of filename strings.
  Model the real signature (body ignores the tracking params).
- **COMDAT dup-symbol fix = label the FIRST instance COMDAT, never `weak`.** Linking a class TU dup-symbols
  on shared `??_7`/`??_R0`/float-consts; the fix is the symbols.txt `comdat` attribute on the defining
  instance (COMDAT folds with COMDAT). Float consts are already done via the libcmt work. (libcmt full-link
  gap is RESOLVED — the whole exe links byte-exact now.)
- **Polymorphic-class destructors gate on `Base`.** The vector/scalar deleting dtor (`??_E`/`??_G`) and the
  inlined `destroyed`-flag check (e.g. the "run-once guard" in `*Info` array dtors — it's inlined
  `Base::~Base`, `??1Base@@UAE@XZ`=`mov [ecx],??_7Base; mov [ecx+4],1; ret`) are **Base destructor codegen**.
  The maintainer is solving this **at Base first**; the whole `Base`/`*Info` family (most of the game) falls
  out once Base's dtor is right. Don't ship per-class `/alternatename` hacks.
- **DIAGNOSE-FIRST, identify before labeling.** Never name a byte pattern or call something a "toolchain gap"
  before resolving what its flags/addresses/callees ARE (`symbolize.py <addr>`, `crack.py`, disasm the
  callee). I got the CISI "guard" and the GJPersistent string type wrong by pattern-matching shape instead
  of identifying targets. Run tools to FALSIFY your frame; never escalate an interpretation outward unverified.
