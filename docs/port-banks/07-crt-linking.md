# 07 — CRT linking: recovering "libcmt linking" via COFF-merged multi-function splits

How dtk-template's "libcmt linking" coverage was scaled from **61** placed CRT
objects to **8 merged runs covering 672 CRT functions (619 byte-exact)**, and the
tooling that makes it reproducible for v1.0 / v1.1 / v1.2.

## Headline result

> **Global `matched_functions` 1936 → 2496 (+560); `complete_code` 12968 → 85160
> (+72192).** Game TUs unchanged at **1876 / 158**. Build green.
> Commits: `ad98989e` (build unblock), `1d300c8e` (merge), `27567076` (dup-resolve).
>
> **WALL 2 follow-up (`.text` boundary labels):** a later sprint added **126 CRT
> `.text` function labels** (`tools/label_crt_text.py`), taking global
> `matched_functions` a further **2555 → 2689 (+134), zero regressions**, game TUs
> held at **1877 / 158** — see "WALL 2 residual — SOLVED" below.

The original game statically linked ~253 objects from MSVC 6.0 SP5
`LIBCMT.LIB` / `LIBCPMT.LIB`. dtk-template can reproduce a CRT object byte-exact
by copying the patched `.obj` into a split (`copy_obj` rule). The previous
`scale_crt.py --single` placed only **61** of them; **144 were dropped as
"misaligned"** and **26 as "build-fail"**. This pass clears both walls.

---

## The two walls (and why they fall)

### WALL 1 — misaligned (144 objects)

dtk **hard-requires every split to START on a 4-byte boundary**. MSVC packs CRT
functions back-to-back with **no inter-function padding**, so most individual
objects do not start on a 4-byte boundary → they cannot be standalone splits.
dtk also has **no native way** to feed several source objects into one split.

**Fix:** synthesise ONE COFF object per *run* of consecutive CRT functions whose
combined span begins on a 4-byte boundary, and place it as a single split. The
`copy_obj` rule copies it; objdiff compares it against the binary over the whole
run and matches each function. → `tools/merge_crt_obj.py` + `scale_crt.py --merge`.

### WALL 2 — build-fail (26 math/float objects) → **dissolved by WALL 1**

memcmp, strchr, strspn, tolower, asin, acos, pow, 87fmod, fpinit, atox,
ieeemisc, longjmp, intrncvt, adj_fdiv, … These build-failed as *standalone*
splits (alignment + single-`.text`-section copy of multi-COMDAT objects). As
**part of a merged run** they build fine and are byte-exact: **all of them are
now placed**, and most match 100% (`_memcmp`, `_strchr`, `_fmod`, `_atoi`,
`_tolower`, `__copysign`, `_asin`, `_acos`, …). The few still <100% (`_pow`,
`_calloc`, `_memcpy`) are blocked by the **same data-symbol gate as WALL 2's
residual** (below), not by a build error.

---

## COFF-merge mechanics (`tools/merge_crt_obj.py`)

A patched MSVC 6.0 COFF object (`machine 0x14C`) has each function in its **own
COMDAT `.text` section** (multi-section objects are the norm: 101/236 objects),
plus `.data`/`.rdata`/`.bss`/`.debug$F`/`.drectve`/`.CRT$*`. 199/236 objects have
`.text` relocations.

`merge_sections(secs, out, run_start, run_end, binary)` builds ONE COFF whose
single `.text` is the run's functions laid at their **true binary offsets**:

1. **Section, not object, is the unit.** The MSVC linker **reorders and scatters
   an object's COMDATs across the image** (e.g. `winput`'s `__winput` is at
   0x7D5243 but its helper `__hextodec` is at 0x7D0862, ~17 KB away). So we work
   per `.text` section and **anchor each to its real VA**:
   - by its defined symbol's address in `symbols.txt` (preferred), else
   - by a **masked signature search** of the section's bytes in the binary
     (relocation sites wildcarded), confined to a window around the object's
     labeled sections so a short common COMDAT can't false-match far away. This
     recovers **unlabeled static helper COMDATs** (e.g. `_flsall`) that have no
     `symbols.txt` entry.
2. **Place at `VA - run_start`; fill gaps from the BINARY.** The gaps are the
   linker's exact inter/intra-function padding (almost always `0xCC` int3).
   Copying the binary bytes makes the merged `.text` byte-identical to the
   binary over the whole split.
3. **Per-section binary verification.** Before placing a section, every
   non-relocation byte is compared to the binary. A mismatch ⇒ it's the **wrong
   variant of a duplicate** (a function compiled into two objects where the
   linker kept only one — e.g. `__hextodec` is 55 bytes in `input.obj` but 90 in
   `winput.obj`; the binary has the 55-byte one) or a bad anchor → **skip it**.
   This single check both resolves duplicates (recovered the 8th run, +191
   functions) and hardens placement.
4. **De-duplicate COMDAT-folded sections by VA.** Two identical functions folded
   to one address (different names, same VA — e.g. `?ArrayUnwindFilter` /
   `?FrameUnwindFilter`) get **both names emitted** but bytes placed once.
5. **Relocations are KEPT and remapped** (VirtualAddress shifted, target carried
   as an undefined external **by name**). objdiff normalises relocations: it
   matches a reloc when the target **name resolves in `symbols.txt`** to the
   address the binary's relocation points at. (Resolving the bytes in-place and
   dropping the reloc does NOT work — objdiff expects a relocation where the
   binary has one; that was a measured 99% vs 100% dead end.)
6. **Whole-`.text` self-check** vs the binary (raises on any non-reloc diff), so
   a structurally wrong run is dropped, never committed.

The COFF writer emits: header, one `.text` section header, `.text` body,
relocation table, symbol table (`.text` section symbol + its **18-byte** aux
section-definition record + the external/defined symbols), string table.

> **Bug that cost an hour:** the aux section-definition record must be **exactly
> 18 bytes**. `struct.pack("<IHHIHBB", …)` is 16 + the `+ b"\x00\x00\x00"` made
> **19**, shifting every following symbol record → the function symbol decoded as
> garbage (`class=0`, `naux=2`). Correct: `"<IHHIHB"` (15) + 3 pad = 18.

---

## Run-picking (`scale_crt.py --merge`)

1. Extract every CRT object; `collect_sections()` anchors each `.text` section.
2. **Obstacles** = every split that is NOT a managed CRT object — the **158 game
   TUs** plus the 2 hand-committed CRT singletons (memchr/strcspn, kept). The
   CRT region is **not** cleanly separate: the game TU `Bank_7e6d10` sits inside
   it, so a single giant split is impossible.
3. **Greedy runs:** walk anchored sections in address order; extend a run while
   the next section (a) does not make `[run_start, sec_end]` cross an obstacle
   and (b) the gap to it is ≤ 128 bytes (a larger gap = foreign non-CRT code; cut
   so a split stays a tight CRT cluster). Overlapping (duplicate) sections stay
   in the run; the merge dedups them.
4. **Boundary snapping (the alignment rule):**
   - **Start:** trim leading sections until the start is 4-byte aligned **AND**
     not straddled by a labeled symbol whose `symbols.txt` extent overestimates
     its size. (`_signal`'s extent is computed up to the next *labeled* symbol
     `_raise`, but an *unlabeled* static `_ctrlevent_capture@4` sits between
     them; a run starting at the static collides with dtk's auto-split for
     `_signal`. Trim past it.)
   - **End:** snap **up** past any labeled symbol straddling the computed end
     (the obj's `.text` rawsize is shorter than the symbol's binary extent
     because of trailing padding, so a naïve end bisects the last function →
     dtk "split ends within symbol").
5. Merge each run → `lib/crt_obj/crt_merge_<start>.obj`; place split
   `[run_start, run_end]`; configure entry. A run is **kept iff it builds**
   (byte-exactness is guaranteed by the merge self-check). Per-function 100% is
   then gated only by reloc targets being in `symbols.txt`.

`--merge` is the default; `--single` keeps the legacy one-object path.

---

## Final coverage (commit `27567076`)

| run | funcs 100% / total | complete_code |
|---|---|---|
| crt_merge_007aee98 | 2 / 3 | 188 |
| crt_merge_007c5604 | 4 / 4 | 96 |
| crt_merge_007c5ec0 | 139 / 149 | 11824 |
| crt_merge_007c90a0 | 117 / 123 | 13850 |
| crt_merge_007cc974 | 21 / 27 | 4528 |
| crt_merge_007ce318 | 191 / 204 | 31389 |
| crt_merge_007d6354 | 119 / 133 | 20668 |
| crt_merge_008a5b0c | 26 / 29 | 2388 |
| **total** | **619 / 672** | **85131** |

Dropped: 16 objects **unanchorable** (a `.text` section with no `symbols.txt`
symbol and no unique in-window binary match — e.g. all-relocation COMDATs, or
data-only objects `nlsdata*`, `ctype`, `days`).

---

## WALL 2 residual — SOLVED: the blocker was missing `.text` FUNCTION labels, not data labels

> **Result (this sprint):** `tools/label_crt_text.py` adds **126 `.text` function
> labels**. **Global `matched_functions` 2555 → 2689 (+134), zero regressions.**
> Game TUs unchanged at **1877 / 158**. Build green. The symbols.txt diff is
> purely additive (+126 lines, no existing symbol touched). Of the original 53
> <100% functions, **17 reached 100% directly**; the rest of the +134 are
> previously-unlabeled CRT helper functions that became individually matchable.
> CRT-merge below-100 dropped 53 → 42 (over a now-larger, fully-split function set).
>
> The 6 **COMDAT-fold aliases** (same address, different name) are **deliberately
> NOT applied** (`--with-aliases` is opt-in, default off): dtk's split **dedups
> same-address symbols to ONE name**, so an alias *replaces* the existing symbol
> rather than adding a second — measured net ~0 and one regression
> (`__stricmp` → `__strcmpi` broke its match).

### The diagnosis (what the prior premise got wrong)

The earlier note said the 53 need **data** labels. That is **wrong**, and the
reason is `objdiff-cli report generate` runs with **`function_reloc_diffs = None`
(relaxed)**: when the TARGET (dtk-split-from-binary) object has **no relocation**
at a site but our BASE (merged) object **does** (a DIR32 to a data/IAT symbol),
`reloc_eq`'s `(None, Some(_)) => return relax_reloc_diffs` makes it **match
anyway**. dtk's split objects contain **only REL32** relocations (relative
call/jmp) and **zero DIR32** — so unlabeled CRT data references are *already*
tolerated. Adding data labels changes nothing for the match (and destabilises the
splitter — see below).

The real blocker is **symbol-boundary misalignment**. Our merged base obj defines
**every** function in the run, including unlabeled static CRT helper COMDATs
(`_LcidFromHexString`, `_crtGetLocaleInfoA@16`, `_LangCountryEnumProc@4`, …).
dtk's target obj only creates a symbol for each **name in `symbols.txt`**; an
unlabeled helper sitting between two labeled functions gets **absorbed into the
preceding labeled symbol**. objdiff then compares e.g. a **341-byte** target
`_IsThisWindowsNT` against our **54-byte** one — the extra bytes (a *different*
function) all diff → the function reports ~14 %. Label the missing helper and dtk
splits the target symbol correctly → the per-function compare aligns → 100 %.

> **Debug lesson that cost the most time: `left` = TARGET (dtk split), `right` =
> BASE (our obj) in the `objdiff-cli diff` JSON.** Counting "attached DIR32
> relocations" per side and getting the sides backwards made it *look* like our
> DIR32 relocs were being dropped. They are not — the base has them; the **target
> has none** (dtk emits only REL32), and relaxed mode bridges the gap. Always
> confirm a side's identity by its reloc count (target == split obj's `nrel`).

### The recipe that worked (`tools/label_crt_text.py`)

1. For every defined function symbol (COFF `type 0x20`, external) in each
   `lib/crt_obj/crt_merge_*.obj`, compute its binary VA (`run_start + value`).
2. Keep it iff: not already in `symbols.txt`, not a `$`-local, and its VA lies
   **inside a `crt_merge_*` split** (so the label is a *sub-function* of a managed
   split — never a new standalone split that would need 4-byte alignment).
3. Emit each as a `.text:` label, `type:function`, in an idempotent
   `# >>> … (BEGIN/END)` managed block, **NO inline `#`** (dtk rejects it; dtk also
   **strips full-line `#` comments and converts the file to CRLF** when the split
   runs — the labels persist as plain lines, so re-runs stay idempotent by name).
   **Skip COMDAT-fold aliases** (a VA that already has a *different* name): unlike
   adding a brand-new symbol, dtk's split **dedups same-address symbols to one
   name**, so the "alias" overwrites the existing symbol instead of adding a
   second — net ~0 and risks a regression. (`--with-aliases` keeps them, off by
   default.)
4. **`ninja` (re-split) then `report generate`.** The split is a *ninja* step
   (`rule split`) gated on `config.json`, **not** on `symbols.txt` directly — so
   after editing `symbols.txt` you MUST rebuild `config.json`
   (`ninja build/BW1E142/config.json` or a full `ninja`) to regenerate the target
   objects with the new boundaries. (Running only `configure.py` is not enough;
   running only `objdiff-cli` reads STALE target objs — this masked the fix for a
   while.)

Apply: `python tools/label_crt_text.py --apply` → `python configure.py -v BW1E142`
→ `…/ninja.exe` → `objdiff-cli report generate` → `python tools/measure_match.py`.
Idempotent and re-runnable (recomputes against `symbols.txt` minus its own block).

### Why the remaining 42 resist (characterised, not yet beaten)

- **SEH funclets (~13):** `_free`, `__heap_alloc`, `_calloc`, `_realloc`,
  `__msize`, `___crtGetLocaleInfoA/W`, `___crtGetStringTypeA/W`, the exception
  helpers, `??_L…`, `?__ArrayUnwind…`, `__rt_probe_read4@4`. MSVC compiles a
  `try/catch` body into the **same `.text` COMDAT** with no separate symbol, so
  our merged obj's function symbol spans it; dtk auto-labels the catch
  continuation as a tiny `fn_<addr>` (often **4 bytes**, the
  `$ExceptionContinuation` entry). Target = small + a funclet; base = one big
  symbol → boundary mismatch. Fixing this requires **our merged obj to split the
  funclet** (a `merge_crt_obj.py` change emitting funclet sub-symbols), which
  edits `lib/crt_obj/*` — out of this sprint's scope.
- **objdiff one-reloc-per-instruction (~6, incl. 3 at 99.98 %):** instructions
  like `mov dword ptr [DATA_A], DATA_B` carry **two** relocatable operands;
  objdiff's x86 attaches **one** reloc per instruction, so the other operand
  compares the placeholder vs the real value → a single permanent
  `DIFF_ARG_MISMATCH`. `___init_time`, `___init_monetary`,
  `___get_qualified_locale` are otherwise 100 %.
- **Duplicate-name jump-table fragments (~8):** the unrolled `memcpy`/`memmove`
  byte-copy dispatch defines `LeadUp1`/`UnwindUp0`/`TrailUp3`/… **with the same
  name in two objects at two addresses** — a `symbols.txt` name maps to ONE
  address, so both can't be labeled; the region also mixes code + a jump table.
- **`$`-locals / INTERIOR data-in-blob:** `$`-prefixed compiler locals can't be
  global symbols; some data targets sit *inside* the `lbl_00C2D417` mega-blob
  (the whole CRT `.data` region as one label) and would need that blob split.

### Data labels are a dead end here (obstacle #1 confirmed)

`tools/recover_crt_syms.py` recovers data/import target addresses, but applying
**any** `.data` label past the initialized region triggers
**`Symbol gap_… size out of section bounds`**: `.data` has a large
**bss/virtual tail** (raw `0x9C6000`–`0xC3A808`, virtual to `0xFBFE00`), and dtk
computes a gap symbol from the last raw-`.data` label (`lbl_00C3C229`) to the next
labeled symbol *in the bss*, which exceeds the raw section. A bounding "cap"
symbol just moves the error onto itself (the cap is then the out-of-bounds one).
Since relaxed mode already makes these data relocs match, the data labels buy **no
matched functions** anyway — so they are intentionally NOT applied.

> **Lesson: never put `#` in a `symbols.txt` symbol line** (full-line `#`
> comments are fine, inline ones are rejected as `Unknown symbol attribute '#'`).
> Both `recover_crt_syms.py` and `label_crt_text.py` emit clean lines; provenance
> lives in the BEGIN/END comments + git history.

> **Build-unblock prerequisite (commit `ad98989e`):** HEAD `8f7a33f3` did **not**
> build — the 219 `detect_crt` labels carried a trailing `# detect_crt` marker
> after the `//` comment, which dtk rejects (`Unknown symbol attribute '#'`), and
> 8 labels landed inside an existing sized symbol (e.g. `_asctime` inside
> `fn_007C76FD size:0x1A0`) → "split ends within symbol". Stripped the markers;
> removed the now-stale `size:` from the 8 parents. **Lesson: never put `#` in a
> `symbols.txt` symbol line** — full-line `#` comments are fine, inline ones are
> not. `recover_crt_syms.py` emits clean lines accordingly.

---

## Reuse for v1.0 / v1.1 / v1.2

The same `LIBCMT.LIB`/`LIBCPMT.LIB` are used across versions, so the pipeline
ports directly: point `EXE`/`SYMBOLS`/`VERSION` at the target, run
`python tools/scale_crt.py --merge`. Everything is binary-anchored and
self-checked, so a wrong anchor drops its run rather than corrupting the build.

## Tools added/changed

- `tools/merge_crt_obj.py` — COFF reader+writer; `collect_sections`,
  `merge_sections` (address-placed, binary-anchored, dup-resolving), `object_span`.
- `tools/scale_crt.py` — `--merge` mode: run-picking, boundary snapping, splice,
  build, drop-failures, measure. (`--single` = legacy path.)
- `tools/recover_crt_syms.py` — data/import symbol recovery from reloc sites
  (WALL 2 data-label groundwork; **a dead end** — relaxed-mode already tolerates
  these relocs and `.data` labels hit the bss-bounds gap bug; kept for reference).
- **`tools/label_crt_text.py`** — the WALL-2 fix: labels the **missing `.text`
  function symbols** so dtk's split objects share our merged objs' boundaries.
  Idempotent managed block; `--apply` / `--only` (bisect) / `--with-aliases` (the
  off-by-default unsafe COMDAT-fold aliases). **+134 matched_functions, zero
  regressions.** Run, then `ninja` (re-split) + `report generate`.
- `tools/crt_diag.py` / `tools/crt_cat.py` / `tools/crt_plan.py` — diagnostics:
  per-function unresolved reloc targets, target categorisation (CLEAN / alias /
  interior / `$`-local / `.text`), and per-function feasibility profile. Used to
  characterise the residual; reusable for future CRT passes.
