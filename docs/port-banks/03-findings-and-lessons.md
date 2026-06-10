# Findings & lessons

The non-obvious things this migration taught us. These are the reusable knowledge.

## 1. dtk is a *stricter, more correct* checker than our old meter

`bw1-decomp`'s cmake objdiff compared staging (MSVC6) against a target that **wasn't always the real
original** (sometimes a clang-compiled `src/c` body, or an equivalence). dtk's target is the **actual
original binary**, COFF-split from the exe. Recompiling our "byte-exact banks" against it revealed that
**~47 of them aren't byte-exact vs the true original** (1696/1743). That's not a regression — it's dtk
*catching* false-positives our meter let through. Net: the dtk migration **improved our verification**.

The ~47 split into two kinds (below).

## 2. Overload / address-data mismatches (4 functions)

For overloaded methods, the staging `// win1.41 <addr>` comment is sometimes wrong. Example:

```
?IsCreature@GameThing@@UAEIXZ          = .text:0x00401820   (the virtual, no args)
?IsCreature@GameThing@@QAE_NPAVCreature@@@Z = .text:0x00401830   (takes Creature*)
```

but staging put the `IsCreature(Creature*)` body under `// win1.41 00401820` — i.e. the body for one
overload sits at the *other* overload's address. The porter (which trusts the address) then writes the
wrong body → 0% match. These are data errors in the staging markers, not codegen issues.

## 3. Compiler-scheduling near-misses (~24, the real tail)

The rest are **MSVC6 register-allocation / instruction-scheduling** differences — the classic
matching-decomp last mile. Two confirmed by the per-instruction diff:

- `Abode::GetDesireToBeRepaired` (≈93%): the *only* real diff is **`push edi` timing** — MSVC6 saves edi
  in the prologue (ours) vs just before its first use (target). Barely controllable from C source.
- `Abode::SetShouldNotBeAddedToPlanned` (≈75%): a call-free bitfield setter where MSVC6 orders
  `and dl,0xfb` vs `shl al,2` differently than the original. Swapping the C `|` operands didn't change it
  (the compiler schedules independently); it needs a real permute pass.

These are a **permute grind** (semantics-preserving source variants until the bytes match), low priority
versus everything else. They are **not** the "ceiling" below.

## 4. The intra-obj-call "ceiling" — unproven, not dissolved

Earlier in the session I claimed dtk's COFF-split target "dissolves" the old project's intra-obj-call
ceiling (the ~810 functions whose same-object call couldn't be matched in the cmake meter). **That claim
was wrong** — the supporting example (`Abode::IsRepaired`) calls `GetPercentRepaired`, which turned out to
be *external* to the TU (an inter-object reloc that always matched). We never actually tested an in-TU
callee. **Status: open.** Don't assume it either way.

## 5. The draft-mining "dead end" — ⚠ RETRACTED (it was a measurement bug)

> **CORRECTION (see [06-forward-decomp-tools.md](06-forward-decomp-tools.md)):** the "net-loss / dead end"
> below was a **measurement artifact**. The ad-hoc counting regex dropped the class TUs (~380 functions),
> faking the losses. With the reliable `tools/measure_match.py`, **drafts add cleanly with no
> perturbation** (+44 measured). The original (wrong) reasoning is kept below for the record.

### (original, retracted) The draft-mining dead end (6 attempts)

The reassemble files contain clean-C **drafts** for *every* function in their range, including ~11k
**unbanked** (unverified) ones. Tempting: port the drafts too, mine the ones that happen to match in dtk.
The encyclopedia even lets us *target* the matchable ones. It does not work. Record so nobody re-tries it:

**Targeting works.** Encyclopedia-picked "easy" functions (`handler` ∈ {sweep-auto, permute, foldprop})
match at **16%** as drafts, vs **7.5%** for blind drafts. So the encyclopedia correctly identifies the
matchable subset (see doc 04).

**But drafts cannot be ported.** Every configuration is a **net loss**:

| Attempt | What happened |
|---|---|
| `--batch-full` (all drafts, own tiling) | 1251 (< 1696). ~80/172 TUs compile-fail; a bad draft kills its whole TU, taking the verified banks in it down too |
| easy-filtered, combined tiling | 1390. Re-tiling with extra addresses perturbs the fragile banked ranges |
| + per-TU compile-fallback | still 1390 — fallback found **0** compile failures, yet banks were lost |
| + `next-symbol-start` alignment | 1390, worse — `symbols.txt` has intra-function labels, so it *truncated* TUs |
| + `max+size` rounded up to 16 | 1390 — overlaps from the wider tails |
| **fixed committed ranges + insert drafts + revert-fallback** | **1365**, 0 compile failures |

That last one is the diagnostic clincher: ranges *fixed*, zero compile failures, and **still** ~373 banked
functions lost to gain ~42 drafts. **Root cause:** adding a draft body to a TU pulls in extra `#include`s
and declarations, which **changes that TU's compilation context and silently shifts the *banked* functions'
codegen** — so they stop matching. Drafts simply cannot share a translation unit with verified banks, and
in their own TU they'd overlap the banked ranges.

**Conclusion: 1,696 is the robust ceiling for *porting existing work*.** More functions require real
forward decomp (doc 04), where each new function is written correctly in its own context — no perturbation.

`tools/port_banks.py --batch-full` is kept only as a **diagnostic** (its docstring carries this caveat).

## 6. Side finding (unrelated RE, same session)

Confirmed from code: an **Egyptian Wonder on the neutral player** divides the wood cost of *every* build on
the map (a dev oversight). Traced to `BuildingSite::GetWoodValue` @0x43c0c0 ÷ `GetPlayer().perTribePower
[EGYPTIAN]`, where `GameThing::GetPlayer` ignores `this` and returns the fixed neutral player. Full
write-up: `_repos/bw1-decomp/Documentation/Egyptian_Wonder_Global_Build_Discount.md`.
