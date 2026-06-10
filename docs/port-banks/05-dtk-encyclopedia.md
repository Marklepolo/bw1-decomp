# The full dtk function census (all 21,432 functions)

The original `bw1-decomp/Documentation/function_encyclopedia.json` was built by an LLM fan-out over the
**~13,188 *then-unbanked* functions** — it never covered the whole binary. dtk's split exposes the real
total: **21,432 `.text` functions**. `tools/encyclopedia_dtk.py` builds a complete, current, address-keyed
census of all of them, so the entire decomp work-list is appraised in one place against dtk's ground truth.

## Build it

```bash
python3 tools/encyclopedia_dtk.py            # print the census
python3 tools/encyclopedia_dtk.py --write    # also write docs/port-banks/dtk_function_census.json
```

It merges four sources, in priority order, per function (keyed by dtk address):

1. **dtk `symbols.txt`** — mangled name, address, size (authoritative; all 21,432).
2. **our ratchet banks** — `banked: true` if the function is verified in `bw1-decomp` (via `port_banks.banked_units`).
3. **the old LLM encyclopedia** — `klass` + `summary`, merged by `Method@Class` (`klass_src: "llm"`, the quality tier).
4. **a heuristic** — name + size → `klass` for everything the LLM never saw (`klass_src: "heuristic"`).

So we keep LLM quality for the functions it classified, get coverage for the other ~18k cheaply, and fold
in our dtk progress — no expensive re-run.

## Census (current)

```
dtk .text functions: 21432 | banked (ratchet): 2254 | LLM-classified: 3136 | heuristic: 18296
```

(Of the 2,254 ratchet banks that map to dtk, **1,696 are confirmed byte-exact** in dtk; the rest are the
near-misses / unported tail — see doc 03.)

**By handler (the treatment plan):**

| handler | count | meaning |
|---|---:|---|
| `fanout-write-C` | 11,923 | real decomp — write correct C (multi-block, ctors/dtors, intra-obj-call) |
| `sweep-auto` | 6,492 | **easy** — predictable codegen (getters/setters/const-returns/tiny/forwards) |
| `done-banked` | 2,254 | already verified in bw1-decomp |
| `phase2-defer` | 675 | library/CRT/data-global — skip/defer |
| `permute` | 81 | needs source permutation |
| `foldprop` | 7 | fold/constant-propagate |

**By klass (banked / total):**

```
MULTI_BLOCK    12190 (451)   CONST_RETURN 3568 (360)   TINY 2852 (42)    GETTER 1389 (1117)
DESTRUCTOR       628 (211)   INTRA_OBJ_CALL 208 (0)     FORWARD 161 (0)   VIRTUAL_FORWARD 147 (2)
CONSTRUCTOR      126 (18)    SETTER 81 (53)             DATA_GLOBAL 75 (0) BITFIELD 7 (0)
```

Note `GETTER` is **1117/1389 banked** — we've already done most getters. The unbanked simple functions
(the `sweep-auto` 6,492) are the next forward-decomp wave (doc 04).

## Record shape (`dtk_function_census.json`)

```json
{ "addr": "0x004016a0", "mangled": "?IsRepaired@Abode@@UAEHXZ", "size": 32,
  "mc": "IsRepaired@Abode", "klass": "GETTER", "klass_src": "llm",
  "handler": "done-banked", "banked": true }
```

## Using it as a work-list

```python
import json
c = json.load(open('docs/port-banks/dtk_function_census.json'))['functions']
# the easy forward-decomp queue (unbanked, predictable codegen):
todo = [f for f in c if f['handler']=='sweep-auto' and not f['banked']]
# only the LLM-verified klasses (highest confidence) among those:
sure = [f for f in todo if f['klass_src']=='llm']
# the hard backlog:
hard = [f for f in c if f['handler']=='fanout-write-C' and not f['banked']]
```

## Caveats

- **`klass_src` matters.** 3,136 functions carry the original LLM klass+summary (trust these). 18,296 are
  **heuristic** (name + size only): `??0`→CONSTRUCTOR, `??1`/`??_E`→DESTRUCTOR, `?Get*`/`?Set*`/`?Is*`→
  accessor *if small*, size≤6→TINY, ≤0x10→CONST_RETURN, else MULTI_BLOCK. Good for a coverage map and
  prioritization; not a substitute for reading the asm on a given function.
- Overloads collapse on `Method@Class` for the LLM merge, so a few overloaded methods inherit a sibling's
  LLM klass. The heuristic and `banked`/`size`/`addr` fields are always per-function-exact.
- To upgrade quality, re-run the LLM `classify-encyclopedia` fan-out over the `klass_src=="heuristic"`
  set — but that's a large compute; the heuristic map is enough to drive prioritization now.
