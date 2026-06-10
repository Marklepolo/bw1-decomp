# Porting bw1-decomp banks → dtk-template (BW1E142)

Moving our verified work (banks + tools) from the cmake/MSVC6-staging project (`bw1-decomp`,
branch `gated-lifts-verified`) into this dtk-template worktree (branch `port-banks`).

> **📚 Full documentation:** [`docs/port-banks/`](docs/port-banks/README.md) — overview, build
> environment & reproduction, the `port_banks.py` tool reference, findings & lessons (incl. the
> draft-mining dead end), and the encyclopedia-guided forward-decomp plan. This file is the short version.

## ✅ DONE — 1696 / 1743 banked functions byte-exact in dtk (97.3%)
The full bank migration is ported and measured (`objdiff-cli report` over our TUs):
- **c-banked** (430 staging-C banks): 402 byte-exact — across class TUs (Abode + Villager*/GGame/
  SpellIcon/GameThingWithPos).
- **asm-banked** (1237, via `--batch`): the bulk byte-exact — across 92 `Bank_*` address-tiled TUs.
- **Total: 1696/1743 byte-exact**, up from the 474 first pass. Commit `70ec495a`.

## Key facts (proven)
- dtk's MSVC6 = `12.00.8804` = MSVC 6.0 SP5 = exactly our staging compiler → byte-exact reproduction.
- **The "asm-banked" are CLEAN C, not asm**: the ~1400 `asm/...` ratchet entries are clean-C bodies in
  `src/staging/runblack.reassemble.*.cpp` (unit-named by asm address range), with ZERO address-overlap
  with the 430 c-banked → genuinely new functions.
- **dtk's target = the real original** (COFF split) — stricter than our staging meter; it surfaced ~47
  "banks" that aren't byte-exact vs the original. These are compiler-scheduling near-misses (e.g.
  `push edi` save timing in `GetDesireToBeRepaired`), NOT the intra-obj-call ceiling (which remains
  unproven either way — the early IsRepaired example had an external callee).
- MAX_PATH: use the long-path-aware **pip ninja (1.13)**, not Strawberry's (`LongPathsEnabled=1`).

## The porter — `tools/port_banks.py` (v2, unit-aware)
- `port_banks.py --batch` — tiles the reassemble ranges into TUs, writes `src/Black/Bank_*.cpp`, and
  appends `splits.txt` + `configure.py`. **Unit-aware**: sources each banked function from its OWN
  verified unit file (`src/staging/<basename(unit)>.cpp`), matches BOTH `c/` and `asm/`. Uses **tight
  function-span ranges** `[min banked addr, max addr+size]` (size from symbols.txt) — loose file-name
  ranges overlap and crash the dtk split ("overlaps with previous split").
- `port_banks.py <TU.cpp> <LO> <HI>` — port one explicit range (the class TUs).
- Build env: `configure.py` cflags add `/I include /I include/black /I <MSVC6 CRT>`;
  `tools/port_setup.sh` seeds `include/` from `../bw1-decomp` (gitignored). `LH_RETURN` is guarded with
  `BW1_LH_RETURN_DEFINED`; depth-0 decls (globals/cross-refs) are auto-collected by the gather.

## objdiff-cli per-instruction diff (to chase the near-misses)
`objdiff-cli diff -1 <target.o> -2 <base.o> "<mangled>" -o out.json --format json` → top-level
`left.symbols[]` (target) + `right.symbols[]` (mine), each with `instructions[].instruction.formatted`
(NOT nested under sections). `report generate -p . -o rep.json` → per-function `fuzzy_match_percent`.

## Next
- The ~47 near-misses: compiler-scheduling (regalloc / register-save timing) — a permute grind (low
  priority vs. what's already landed).
- TU geography: the `Bank_*` are address-tiled with generic names; the maintainer can re-organize into
  per-class TUs later. Our 5–6 reassemble ranges that overlap the manual class TUs were skipped by the
  batch (their few functions can be folded into the class TUs via the unit-aware single-TU `port`).
