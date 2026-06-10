# 00 — Toolkit inventory — READ THIS BEFORE BUILDING A NEW TOOL

**Pre-flight rule (mandatory):** a tool almost certainly already exists. Skim this file first; only
build new when nothing here fits. **84 tools in `bw1-dtk/tools/` + 9 archived in `tools/archive/` +
58 in `bw1-decomp/tools/`.** 55 of them carry a passing `--self-test` (the trustworthy core).

**Sync rule:** the shared tools are **content-identical** across `bw1-dtk/tools/` and
`bw1-decomp/tools/` (md5-verified). When you sharpen a shared tool, **mirror it to both repos.**
dtk-specific tools (build/CRT/port machinery) live only in dtk.

**Line endings:** both repos are **LF everywhere** (`core.autocrlf=false` + `core.eol=lf`). Don't
reintroduce CRLF; never put a literal `#`-comment inside a `symbols.txt` symbol line (dtk rejects it).

---
## THE measurement loop — the one truth (use nothing else to count)
```
# run from bw1-dtk
build/tools/objdiff-cli.exe report generate -p . -o rep.json
python3 tools/bytecount.py            # global + every TU
python3 tools/bytecount.py Abode      # one TU
```
Truth = report `measures.matched_functions` (== functions with `fuzzy_match_percent >= 100`).
**Do NOT count via `objdiff-cli diff -u`** — it includes folded/CRT symbols and undercounts.
Always **clean-rebuild** the `.o` before counting (`rm build/BW1E142/src/Black/<TU>.o`); incremental
builds under-report by ~1.

## THE per-function match loop (dtk)
1. `iterate_dtk.py diff <TU> <mangled-sym>` — instruction diff (left=TARGET binary, right=OURS).
2. edit the `.cpp`, `iterate_dtk.py score <TU> <sym>` — authoritative report fuzzy %, keep/revert.
3. near-miss finisher: `permute.py <Name@Class>` (objdiff-scored source permuter).
4. compiler ground-truth for vcalls/regalloc: `probe_vtable.py` (`/FAcs` listing of real vcalls).

---
## ACTIVE CORE (the current per-function-matching frontier — daily drivers)

### Measure / gate / ratchet
`bytecount.py` (authoritative count) · `compiler_sweep.py` (sweep a near-miss TU across EVERY
available cl.exe build → which build byte-matches; the binary is a multi-compiler patchwork, see
`10-compiler-rich-header.md`) · `measure_match.py` · `phase.py` (matching dashboard) ·
`staging_coverage.py` · `ratchet.py` (no-regress guard) · `verify.py` / `verify_defs.py` /
`verify_isolate.py` · `liftgate / autogate / draftgate / fanout_gate.py` (verify-gated batch loops)

### Lift / analyse one function
`lift.py` (symbol-annotated x86 + staging stub) · `gpr.py` (GPR/integer algebra) · `fpu.py` (x87
algebra) · `exprlib.py` (shared symbolic-expr model) · `idioms.py` (MSVC branchless `sbb`/`setcc`) ·
`structmap.py` (`[esi+0x140]`→named field) · `rdata.py` (.rdata float/int constants)

### Resolve names / xrefs / vtables
`symbolize.py` (any VA → fn/data) · `symbols.py` (call target → `Class::Method` + class rels) ·
`auto_harvest.py` (batch-lift trivial+clean targets per TU: CONST/EMPTY/GETTER, name-clean gate, bisection compile-isolation, verify-keep-revert; nested-class aware) · `cascade_rettype.py` (--scan finds void-symbol fns that emit a return value = dtk return-type error; --method/--to cascades the fix across a virtual's override family) · `promote_fn.py` (make an undecompiled fn_XXXXXX CALLABLE: rename placeholder -> ?Method@Class@@ + decl, so its caller lifts byte-exact) · `vtbl_bin.py` (**AUTHORITATIVE** vtable slot<->method, read straight from the binary `??_7Class@@6B@`; use THIS for vcall slots) · `vtable.py` (asm-corpus REAL/STRUCT -- **25.1% of slots resolve WRONG by address** vs the binary; deprecated for resolution, keep only for raw_call codegen) (offset↔method, authoritative arrays) · `vtable_drift.py` (struct-vs-class drift,
ratchet-pinned `--self-test`) · `find_xrefs.py` (the canonical xref, all decomp tiers) ·
`find_virtual_impls.py` · `taint_xref.py` (flow-sensitive)

### Match / finish near-misses
`iterate_dtk.py` (**dtk loop** — `diff`/`score`/`try`) · `iterate.py` (bw1-decomp cmake flow) ·
`permute.py` (source permuter) · `probe_vtable.py` (compiler vcall truth) · `nearmiss.py` /
`nmdiag.py` (keep/diagnose 90%+ seeds) · `effmatch.py` (semantic-equivalence) · `boundary.py` /
`label_split.py` (boundary-artifact near-misses) · `forge.py` (unified pipeline)

### Structs / signatures / auto-fill
`name_structs.py` / `name_structs2.py` (inheritance-aware `*Info` namer + byte-exact verify) ·
`struct_apply.py` / `struct_sizes.py` (binary-truth sizes) · `sig_arity.py` / `sigfix.py` ·
`bitfield.py` · `retwidth.py` · `dataglobals.py` · `foldprop.py` / `fold_graph.py` (COMDAT twins) ·
`autolift.py` · `lift_thunks.py` · `fwdthunk.py` / `vforward.py`

### Census / triage / corpus
`encyclopedia.py` / `encyclopedia_dtk.py` (function census) · `triage.py` / `propose.py` ·
`corpus.py` (local-first corpus resolver — lets analysis tools run from either repo) ·
`clang_ast.py` (libclang AST parse of staging `.cpp` — **bw1-decomp cmake flow**; libclang 18.1.1
is in the venv, so run its self-test from bw1-decomp; it SKIPs in dtk by design)

### Port (bw1-decomp banks → dtk)
`port_banks.py` · `port_splits.py` · `carve_tu.py` · `lift_scan.py` (classify a TU's undecompiled methods: CONST/EMPTY/GETTER/TAILV) · `fix_mangling.py` (fix self-class back-ref names in symbols.txt) · `mangle_check.py` (header-decl vs symbol: find clean liftable targets / flag header bugs) (split a multi-class TU into per-class TUs by win1.41 addr; see docs/port-banks/13-tu-carving.md) · `tile_drafts.py` · `portledger.py` (C→Rust verified manifest)

### B&W research
`find_tribal_consumers.py` (every tribe-Wonder power consumer)

## BUILD INFRA — leave alone (invoked by configure.py / build.ninja; archiving breaks the build)
`project.py` · `ninja_syntax.py` · `post_link_patch.py` · `testcompile.py` · `download_tool.py`
(idempotency-guarded) · `changes_fmt.py` · `decompctx.py` · **the CRT cluster** (`scale_crt.py`
[in configure.py], `merge_crt_obj.py`, `make_crt_obj.py`, `detect_crt.py`, `feed_crt_labels.py`,
`label_crt_text.py`, `recover_crt_syms.py`, `crt_cat.py` / `crt_diag.py` / `crt_plan.py`)

## ARCHIVED — phase-complete, kept-runnable → `tools/archive/` (see its README)
The forward-decomp **generation** cluster (the "45% simple-klass slice — DONE", superseded by the
per-function lift→iterate→permute loop): `gen_simple` · `gen_asm` · `gen_targeted` · `gen_ctordtor` ·
`gen_inplace` · `mangle_worklist` · `decl_fix` · `bucket_dump` · `closeout_table`. Still run via
`python tools/archive/<name>.py`. Not deleted — just out of the active list so the core reads clean.

---
**Key gotchas banked** (detail in `06-forward-decomp-tools.md` + `07-crt-linking.md`):
objdiff diff JSON `left=TARGET` / `right=BASE`; `fuzzy=None` is ambiguous (COMDAT-fold **or** TU
didn't compile → test-compile first); covariant-return forbids enum/bool/virtual mangle fixes inside
an override family; the build `#include`s the **git-ignored** `include/black/` copy AND tracked
`bw1-decomp/black/` (edit both).

**Hand-match lesson (RemoveDeletedVillagerFromAbode):** when a function floors at ~80% with correct
logic, the residual is usually MSVC6 **register allocation** (e.g. refusing to enregister a constant
`0` into a callee-saved reg across a call) — confirm with `iterate_dtk diff`, and reach for
`permute.py`, not hand-guessing (every constant-foldable C spelling hits the same floor).
