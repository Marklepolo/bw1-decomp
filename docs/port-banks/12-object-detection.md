# 12 — Object (TU) boundary detection from the binary

Goal of the TU-mapping phase (approach: detect boundaries from the binary, not align-with-upstream):
recover the original `.obj` boundaries of `BW1E142`'s `.text` so each function lands in its real TU —
the prerequisite for clean per-function matching, COMDAT fidelity, and the per-object "Frankenstein"
compiler build. Tool: `tools/detect_objects.py`. Output: `_objects.json` (443 objects).

## Why this is hard (learned empirically — every standard signal fails or is partial)
| signal | result | verdict |
|---|---|---|
| inter-function **gaps** | gap≥16 → 2,468 cands (~3× too many); only **2%** coincide with a real boundary | 16-byte *function* alignment, NOT object boundaries |
| **class names** | reliable where present (`@X@@` ⇒ X's object), but only **45%** of functions named | partial; getter regions are named virtuals |
| call/data **connectivity** | `span=0` across the getter/thunk regions (huge fraction) | blind exactly where names are the only signal |
| **data-ordering** (splat/dtk PS2/GC trick) | **non-monotonic** on MSVC PE — 8,500 backsteps (funcs also ref shared low globals) | does not transfer |

No single signal works — which is precisely why naive attempts fail.

## The method that works — FUSION of complementary signals
The named-virtual regions and the unnamed-code regions are **complementary**, so fuse:
1. **class-name transition** among named functions = a reliable cut (an override is named `@Derived@@`,
   not `@Base@@`, so a `@X@@` method genuinely belongs to X's object).
2. **object-start markers**: `??0` ctors, `_crt_global_initialize_*`, `??__E*` dynamic initializers.
3. **connectivity break in live code**: no call edge spans the cut within a window AND ≥3 local call
   edges exist (so it's real code, not a dead getter run), AND the **local-data** island is disjoint.
   *Local-data* = data addresses referenced by ≤8 functions (drops shared globals — the thing that
   broke data-ordering).
4. **COMDAT merge**: classes whose dominant presence is *scattered* across ≥3 objects (inline/template
   instantiations, e.g. `LHMatrix`, `LH3DMesh`) have their small (≤4-fn) islands absorbed into the host.
5. **adjacent same-class merge**: consecutive objects with the same dominant class = one multi-chunk
   `.obj` → merged.

## Accuracy (honest)
- **443 objects** detected vs the Rich-header's **~951** (which includes many tiny COMDAT/template/CRT
  sections that are NOT source files) → the *meaningful* TU count is ~400–600, so 443 is in-band.
- **Validated by eye** on the Abode hierarchy: cleanly separates `Base → GameThing → GameThingWithPos →
  Object → MultiMapFixed → Abode → PlannedAbode → Windmill → SetupBox`, with `LHMatrix`/`LH3DMesh`
  COMDATs isolated. This matches the known class structure.
- **Residual error (known, not hidden):** a multi-class `.obj` (e.g. `Abode.cpp` defining Abode +
  PlannedAbode + Windmill) may split into per-class objects; a second non-adjacent chunk of a class
  (COMDAT methods) may stay separate; a handful of singleton mis-cuts. It is a high-quality
  **approximation**, not ground truth.

## How to use / sharpen further
- `python tools/detect_objects.py` → `_objects.json` (`[start, end, nfuncs, dominant_class]`).
- `python tools/detect_objects.py --validate 0x401000` → objects around an address (eyeball check).
- Next-sharpen ideas (diminishing returns): RTTI `??_R4` complete-object-locators to confirm class
  starts; merge non-adjacent same-class COMDAT chunks; cross-check against upstream main's reassemble
  ranges; per-object compiler attribution via `compiler_sweep.py` (which build byte-matches each object).

## Next phase (TU mapping proper)
Feed `_objects.json` into `splits.txt`: reconcile against our 224 existing TUs, and for objects not yet
mapped, add splits. Then build + measure byte-exact per object, ratchet no-regress. The per-object
partition is also what makes the Frankenstein build (SP5 bulk + 8047-beta C objects + SP3/SP4 minority)
assignable.

## v2 improvements (measured, not eyeballed)

Two research agents (one hunting ground truth + MSVC artifacts, one surveying the SOTA "delinking" /
compile-unit-recovery literature) drove these:

- **No public `.map`/`.pdb` for B&W exists** (confirmed across archive.org / TCRF / Hidden Palace /
  BetaArchive / the openblack decomp). So there is no external oracle - we detect AND validate from the
  binary's own partial ground truth.
- **PRIVATE-CALL MUST-LINK VETO (new primary signal):** a private/static function's callers are all in
  one tight window (caller-span < 0x1800); a call to it is an intra-object edge that CANNOT cross a real
  boundary. A class-change cut is vetoed when >= `veto_T` such edges cross it - this keeps multi-class
  `.objs` together and never cuts through a static helper. (This is the APS "articulation point /
  biconnected component" idea in lightweight form.)
- **Label-free DASHBOARD (`--dashboard`)** so tuning is measured, per the SOTA validation guidance:
  `data_overlap` (REcover's GA objective: local-data addrs referenced from >1 object), `call_cross`,
  **`PRIV_call_cross`** (the hard one - private calls crossing a boundary = definite error), `class_split`.

Measured spectrum (Abode validated by eye at every setting):
```
  veto_T=None objs=305  data_overlap=3.0%  PRIV_call_cross=5.7%  class_split=58%
  veto_T=2    objs=264  data_overlap=3.0%  PRIV_call_cross=2.9%  class_split=55%   <- default
  veto_T=1    objs=224  data_overlap=2.9%  PRIV_call_cross=2.1%  class_split=52%
```
Error metrics improve monotonically with merging (no sharp knee) => **the exact object count is
under-determined without a `.map`/`.pdb`**; `veto_T` trades granularity vs the private-call constraint.
`PRIV_call_cross` is the principled flooring signal (drive it toward its floor).

## Roadmap to the theoretical maximum (SOTA "delinking", refs below)
Implemented: class/marker cuts, private-call must-link veto, COMDAT + adjacent merges, dashboard.
Not yet (ranked by payoff):
1. **APS articulation points / biconnected components** of the call graph -> seed splits inside
   over-merged regions + a principled count estimate (MS patent US10203968; REcover 2025).
2. **Data-overlap-minimisation** (genetic / greedy) - generalises the >8-ref filter; ~75% precision on
   ELF (REcover, springer 10.1007/s11416-025-00565-1).
3. **Contiguity-constrained Louvain** on a call+address-adjacency graph, alpha-sweep (OSTI 1664640).
4. **PELT change-point** on a per-function feature sequence (ruptures; arXiv 1101.1438).
5. **FLIRT/FLAIR the MSVC 6.0 `.libs`** to lock CRT/MFC library objects (we HAVE the libs) - converts a
   chunk from "infer" to "known" + shrinks the problem (hex-rays FLIRT).
6. **Rich-header per-language count** (C++ 690 / C 261) as a hard target after subtracting FLIRT'd libs.
7. **RTTI must-links** (`??_R0` TypeDescriptor name + vtable[-4]->COL) as constraints (caution:
   COMDAT-folded `/OPT:ICF` stubs are boundary-AMBIGUOUS; `/OPT:REF` leaves dead-strip gaps).

Refs: REcover https://link.springer.com/article/10.1007/s11416-025-00565-1 ; APS patent
https://image-ppubs.uspto.gov/dirsearch-public/print/downloadPdf/10203968 ; modularity
https://www.osti.gov/biblio/1664640 ; PELT https://arxiv.org/pdf/1101.1438 ; FLIRT
https://docs.hex-rays.com/core/flirt.md ; Rich header https://github.com/dishather/richprint .

## v3 testing outcome — SOTA data-overlap signal REJECTED (rigorously)
Tested the REcover data-overlap signal both directions; both fail on this binary:
- **as a CUT** (cut where local-data is disjoint from neighbours): over-segments to ~2,100-2,400 objects.
  3,103 fires, **84% in UNNAMED functions concentrated in the high-address library/CRT/utility regions**
  (0x66xxxx-0x7bxxxx, e.g. `__ftol`) where each function references its own distinct local data, so
  "data-disjoint" is true intra-object. (It does NOT fire in getter regions - getters have no data.)
- **as a MERGE** (merge adjacent objects sharing >=2 private-data addrs): **over-merges** - chains across
  real boundaries (e.g. Abode -> 0x4140c0, a 225-fn blob spanning many objects).
- **CRITICAL LESSON: the dashboard FALSELY REWARDED the over-merge** (a giant blob trivially lowers
  call_cross/data_overlap/PRIV_call_cross). The label-free metrics monotonically prefer merging, so they
  can be GAMED. They must be paired with (a) an eye-check on a KNOWN region (Abode) and (b) a count/
  contiguity sanity check. `data_merge` is left as a tunable param but **OFF by default**.

Net: v3 == v2's class-based detector (class/marker cuts + private-call must-link veto + COMDAT + adjacent
-same-class merge) is the validated **ceiling for STATIC detection**: 264 objects, Abode clean.

## Where the real frontier is (two clear next levers)
1. **The unnamed high-address library/CRT region is the genuinely-ambiguous part** (could be many tiny
   one-fn .objs per the Rich count, or fewer). The right tool is **FLIRT against the MSVC 6.0 `.libs`**
   (we have them) to LOCK each library object as ground truth - resolves that region instead of guessing.
2. **The lifting feedback loop is the true boundary refiner** (no `.map`/`.pdb` exists, so static
   detection is under-determined by construction): carve TUs from this partition -> lift C++ -> the
   compiler reveals truth (a static symbol referenced across a boundary => boundary wrong; a TU that goes
   byte-exact => boundary right; a per-object compiler mismatch => a missed boundary) -> revise. The
   detector + dashboard then act as the referee for each revision. Don't over-grind static detection.

## v3 FINAL - the meaningful improvement (two real wins, everything else tested & rejected)
1. **GAMING-RESISTANT DASHBOARD.** The old single-number metrics (data_overlap/call_cross) were
   monotonically lowered by merging, so a giant over-merged blob 'scored best' (it fooled me into a bad
   data-merge). Replaced with **pairwise class F1** (over-MERGE mixes classes -> precision drops;
   over-SPLIT scatters a class -> recall drops) + purity + PRIV_call_cross. Verified: it now ranks the
   over-merge WORST. This is the key measurement fix - tuning is finally trustworthy.
2. **`dcls` CTOR/DTOR FIX (the big detector win).** v1/v2 `dcls` only matched `?method@Class@@` and
   silently treated **constructors `??0`, destructors `??1`, deleting-dtors `??_G`/`??_E`, operators**
   as UNNAMED (~610 labels lost). Those ctors/dtors are object-START anchors; missing them merged
   adjacent objects. Fixing it moved the partition **264 -> 396 objects (into the meaningful ~400-600
   range)** and purity **0.542 -> 0.628** at the same veto=2 setting. Abode validates clean by eye.
   Dashboard across veto (fixed dcls): None=460/F1.404/pur.676/PRIVx271, veto3=426/.396/.652/153,
   **veto2(default)=396/.390/.628/115**, veto1=343/.381/.585/73.

TESTED & REJECTED this round (rigour, eyeball-verified): data-overlap as CUT (over-segments ~2400) and
as MERGE (over-merges + fools old metric); call-connectivity cuts (over-segment); label propagation via
call graph (only 62%% precision, +94 labels - call graph too sparse). Net: class-name signal + ctor/dtor
anchors + private-call must-link veto is the validated STATIC ceiling (~396-426 objects). Further gains
need FLIRT (library region) or the LIFT->byte-match->REVISE loop (the real ground-truth refiner).

## v3 additional improvement - `--lib-segment` (library-region carving)
The high-address unnamed region (0x700000-0x7bf000) is statically-linked library/CRT code with no class
signal, so the default merges it into giant blobs (up to 257 fns). `--lib-segment` adds call-connectivity
-break cuts in UNNAMED runs only (no class signal to conflict), carving those blobs: **1110 objects,
F1=0.418, purity=0.717** (vs default 396/0.390/0.628) - higher on the gaming-resistant metric and closer
to the Rich ~951. Cost: singleton noise. OFF by default because that region is matched via libcmt-linking,
not lifted as game TUs - the default (396) is the clean game-code partition for the lift loop. Use
`--lib-segment` for full-coverage object mapping.
