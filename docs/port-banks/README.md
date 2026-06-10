# `port-banks` — porting bw1-decomp's verified work into dtk-template

This folder documents the **migration of the `bw1-decomp` project's verified, byte-exact function bodies
("banks") into this dtk-template worktree**, plus all the tooling, build setup, findings, and the plan for
what comes next. It is the handoff record for the `port-banks` branch.

## Headline result

> **1,696 / 1,743 banked functions reproduce byte-exact in dtk (97.3%)** — up from 474 at the start.
> One `objdiff-cli report` over our translation units confirms it. Branch `port-banks`, HEAD `18bc3790`.

The migration of existing verified work is **done**. The remaining ~47 are compiler-scheduling near-misses
(not the migration's fault — see findings). Growing *past* 1,696 needs real forward decomp, not porting.

## Why this works at all

`bw1-decomp` (cmake / MSVC6 "staging" project) and dtk-template both compile with **MSVC 6.0 SP5**
(`12.00.8804`), and dtk's **BW1E142** target is the same `win1.41` binary we rebuild byte-exact. So our
verified C bodies, recompiled here against dtk's COFF-split target, reproduce the original's bytes exactly.
The migration is mostly a *plumbing* problem: get each verified body into a dtk translation unit (TU) with
the right `#include`s and declarations, in a `splits.txt` range that doesn't collide.

## What's in this folder

| Doc | Contents |
|---|---|
| [01-build-environment.md](01-build-environment.md) | Reproduce the build: compiler, includes, MAX_PATH fix, `port_setup.sh`, objdiff (`report` + the per-instruction `diff` method) |
| [02-port_banks-tool.md](02-port_banks-tool.md) | `tools/port_banks.py` reference — modes, the unit-aware gather, the recipe, every gotcha hit and fixed |
| [03-findings-and-lessons.md](03-findings-and-lessons.md) | dtk-is-a-stricter-checker, the near-misses, the ceiling correction, and the **draft-mining dead end** (6 attempts) |
| [04-encyclopedia-and-forward-decomp.md](04-encyclopedia-and-forward-decomp.md) | The function encyclopedia (still valid) + the concrete plan to grow past 1,696 |
| [05-dtk-encyclopedia.md](05-dtk-encyclopedia.md) | **Full census of all 21,432 dtk functions** — `tools/encyclopedia_dtk.py` → `dtk_function_census.json`; the complete work-list with klass / handler / banked status (the old encyclopedia only covered the then-unbanked 13,188) |
| [06-forward-decomp-tools.md](06-forward-decomp-tools.md) | **Writing new C** — `gen_simple.py` (header sig + summary → C) + `verify_defs.py` (the inject→build→revert→objdiff→keep harness) + `measure_match.py`; the hurdle→sharpen log incl. the **retraction of the draft "dead end"** (a measurement bug) |
| [07-crt-linking.md](07-crt-linking.md) | **"libcmt linking" scaled 61 → 8 merged runs / 672 CRT functions** — `merge_crt_obj.py` (COFF-merge: per-section binary-anchored placement, dup-resolution, reloc remap) + `scale_crt.py --merge` (run-picking around game-TU obstacles, 4-byte-alignment snapping). Global `complete_code` +72192; build-fails dissolved; the WALL-2 data-symbol residual + `recover_crt_syms.py` groundwork |

The root [`../../PORT_NOTES.md`](../../PORT_NOTES.md) is the short status sheet; this folder is the deep version.

## TU inventory (what got ported)

- **Class / cluster TUs (c-banked, the 430 "staging-C" banks):** `Abode.cpp`, `Villager_*.cpp` (×4),
  `GGame_*.cpp`, `SpellIcon_*.cpp`, `GameThingWithPos_*.cpp`, `AsmBank_434040.cpp` → 402 byte-exact.
- **`Bank_*.cpp` (×92, the ~1400 "asm-banked" functions):** address-tiled from the reassemble ranges →
  ~1294 byte-exact. (Generic `Bank_<lo>` names; the maintainer can re-organize into per-class TUs later.)

## Commit timeline (branch `port-banks`)

```
0017f044  foundation: configure.py include roots + 62 tools + port_setup.sh + pilot Abode
fd9ece53  port_banks.py: working porter (address-matched bodies + depth-0 decls). Abode 375/388
6003690b  remaining staging-C banks: 7 TUs. 403/430
391778ec  exclude reassemble + decl guards. 402/430 (+ near-miss/overload analysis)
cd1a80df  PROVE asm-banked are clean C: ported one reassemble range -> 72/73 byte-exact
d3040b54  port_banks v2 (unit-aware) + full asm-banked batch: 92 TUs, 1237 functions
70ec495a  fix batch: TIGHT function-span ranges. TOTAL 1696/1743 (97.3%)
3983e9f2  cleanup superseded loose-range files
9d06e70c  PORT_NOTES current
18bc3790  port_banks --batch-full diagnostic (drafts = net-loss, documented)
```

## Reuse note

`tools/port_banks.py` is generic (reads the ratchet + `symbols.txt` + staging files). To re-run the whole
port from scratch: see [02-port_banks-tool.md](02-port_banks-tool.md). To reproduce the measurement: see
[01-build-environment.md](01-build-environment.md).
