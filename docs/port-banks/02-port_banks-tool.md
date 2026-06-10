# `tools/port_banks.py` — the bank porter

Ports `bw1-decomp`'s verified C bodies into dtk `src/Black/*.cpp`. This is the workhorse of the migration.

## What a "bank" is

A **bank** = a function whose C body is verified byte-exact in `bw1-decomp`'s **ratchet** (its
no-regression ledger). Ratchet entries are keyed `<unit>::<mangled>`:

- `c/<class-unit>::<mangled>` — e.g. `c/Abode.008::?Find...@Abode@@...` → verified C in
  `src/staging/Abode.008.cpp`. (~430 of these, the "c-banked".)
- `asm/<reassemble-unit>::<mangled>` — e.g. `asm/.../runblack.reassemble.0099.00434040-0043f980::?...`
  → verified C in `src/staging/runblack.reassemble.0099.00434040-0043f980.cpp`. (~1400, the "asm-banked".)

**The key realization:** both tiers are *clean C* in `src/staging`. "asm-banked" is a misnomer — those
functions live in files *named by asm address range*, but their bodies are C, with **zero address overlap**
with the c-banked. So all ~1830 are portable the same way.

## How it maps a bank to a dtk TU

```
ratchet "<unit>::<mangled>"  ──split──▶  unit, mangled
mangled  ──dtk symbols.txt──▶  address           (?Foo@Bar@@... = .text:0x00xxxxxx)
unit     ──basename + ".cpp"──▶  src/staging/<basename>.cpp     (the function's OWN verified file)
address  ──// win1.41 <addr> marker──▶  the brace-matched function body in that file
```

This **unit-aware** sourcing (each function from *its own* verified file) is what makes v2 correct: a
function that appears in several staging files (a draft copy + the verified one) is always taken from the
unit the ratchet blessed, so there's no dedup ambiguity.

## Modes

```bash
python3 tools/port_banks.py <TU.cpp> <LO_hex> <HI_hex>   # port ONE explicit range (the class TUs)
python3 tools/port_banks.py --batch                       # tile the asm-banked reassemble ranges -> Bank_*.cpp
python3 tools/port_banks.py --batch-full                  # ALSO port unbanked drafts (DIAGNOSTIC; net-loss, see 03)
python3 tools/port_banks.py --self-test
```

`--batch` writes the `Bank_*.cpp`, then **appends** the new TUs to `config/BW1E142/splits.txt` and
`configure.py` (as `Object(NonMatching, "Black/Bank_*.cpp")`). It **skips** any reassemble range that
overlaps an already-assigned TU (the class TUs), so run the class TUs first.

## Key functions

- `banked_units()` → `{addr: staging_file}` for ALL banks (c/ + asm/), from ratchet + symbols.txt.
- `all_units()` → `{addr: reassemble_file}` for ALL `win1.41` functions in reassemble files (banked +
  unbanked drafts), deduped lowest-file-wins. Used only by `--batch-full`.
- `gather_range(lo, hi, addr_file)` → for every addr in `[lo,hi)`, brace-extract its body **from its own
  file**, plus all depth-0 `#include`s and declarations. Returns `(funcs, includes, decls)`.
- `write_tu`, `port`, `batch(addr_file=None)`.

## Recipe — re-run the whole port from scratch

```bash
# 0. headers
tools/port_setup.sh
# 1. class / cluster TUs (c-banked), one per explicit range:
python3 tools/port_banks.py Abode.cpp 0x401000 0x407840
python3 tools/port_banks.py Villager_55c970.cpp 0x55c970 0x55cb70
# ... (GGame_54c180, Villager_74f900/756450/7630f0, SpellIcon_726350, GameThingWithPos_768570, AsmBank_434040)
# 2. asm-banked tiles:
python3 tools/port_banks.py --batch
# 3. build + measure  (see 01-build-environment.md)
```

## Gotchas hit and fixed (so you don't re-hit them)

1. **Match by ADDRESS, not name.** The ratchet key is `<unit>::<mangled>`; an early attempt keyed on
   `method@class` and found 0 functions. Map mangled→addr via `symbols.txt`.
2. **Depth-0 declarations are mandatory.** Staging files declare globals/cross-refs at file scope
   (`extern "C" GGame* game;`, `Town* abode_town_00c4cc6c;`, forward decls). A combined dtk TU needs ALL
   of them or it won't compile. `gather_range` collects every depth-0 line ending in `;`.
3. **Brace-depth tracking.** Some staging files (e.g. `Villager.cpp`) mix functions *with* and *without*
   `// win1.41` markers. Without running brace-depth, an unmarked function's `return 0;` leaks in as a
   "declaration" and breaks the compile. Fix: track depth across the whole file; collect decls only at
   true file scope. Also reject statement keywords (`return|goto|if|...`) defensively.
4. **TIGHT, aligned ranges.** A TU's `.text` range must be `[min banked addr, max addr + size]` (size from
   `symbols.txt`). The **loose file-name ranges** of the reassemble files **overlap** → `dtk split` fails
   with *"overlaps with previous split"*. (Don't "align to next function start" instead — `symbols.txt`
   has intra-function labels, so that truncates TUs and drops functions.)
5. **Exclude reassemble for the c-banked single-TU `port` (v1 behaviour), or use unit-aware (v2).** A
   c-banked address also appears in reassemble files as a copy; pick the verified named-unit body. v2's
   unit-aware `banked_units()` handles this automatically.

See [03-findings-and-lessons.md](03-findings-and-lessons.md) for the `--batch-full` draft caveat and why
drafts can't be ported at all.
