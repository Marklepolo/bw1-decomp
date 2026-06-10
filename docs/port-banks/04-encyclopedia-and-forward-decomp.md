# The function encyclopedia + the forward-decomp plan

How to grow *past* the 1,696 ceiling, using the asset we already have.

## The encyclopedia (still valid)

`bw1-decomp/Documentation/function_encyclopedia.json` classifies **all 13,188 functions** of the original
binary. It's intact and remains correct — it describes the *original*, which doesn't change. Structure:

```json
{ "census": { "by_klass": {...}, "by_handler": {...} },
  "functions": [ { "fn": "SetPos@GameThingWithPos", "klass": "SETTER",
                   "handler": "sweep-auto", "summary": "...", "confidence": "high" }, ... ] }
```

**Each record is directly actionable:**
- `fn` = **`Method@Class`** → map to address via dtk `symbols.txt` (`?Method@Class@@...` = `.text:0x...`).
- `handler` = the recommended *treatment* (difficulty signal).
- `klass` = the function's *shape*.
- `summary` = a human description (often the body/behaviour); `confidence` = how sure the classifier was.

### `handler` census (the treatment plan)

| handler | count | meaning |
|---|---:|---|
| `phase2-defer` | 5505 | library/CRT, data-globals, hardest — skip / defer |
| `fanout-write-C` | 4432 | real decomp: write correct C |
| `sweep-auto` | 3021 | easy / predictable codegen |
| `permute` | 161 | needs source permutation |
| `foldprop` | 69 | fold / constant-propagate |

### `klass` census (the shape)

```
MULTI_BLOCK 6440  DATA_GLOBAL 1904  INTRA_OBJ_CALL 1193  CONSTRUCTOR 752  FORWARD 692
CONST_RETURN 606  DESTRUCTOR 557    TINY 306             GETTER 282       SETTER 232
VIRTUAL_FORWARD 201   BITFIELD 12   UNKNOWN 11
```

The **simple klasses** — `GETTER`, `SETTER`, `CONST_RETURN`, `TINY`, `BITFIELD`, `FORWARD`,
`VIRTUAL_FORWARD` — have predictable codegen. The **hard** ones — `MULTI_BLOCK`, `INTRA_OBJ_CALL`,
`DATA_GLOBAL` — are where the real work (and the open ceiling question) lives.

### `Method@Class` → address (the cross-ref)

```python
sym_mc = {}                                   # Method@Class -> [addr,...]  (overloads collapse)
for line in open('config/BW1E142/symbols.txt', encoding='latin-1'):
    m = re.match(r'\s*\?(\w+)@(\w+)@@\S*\s*=\s*\.text:0x([0-9A-Fa-f]+)', line)
    if m: sym_mc.setdefault(m[1]+'@'+m[2], []).append(int(m[3], 16))
```

(Confirmed working: of the encyclopedia's "easy" functions, 837 mapped to addresses, 413 were unbanked and
had drafts. Drafts were a dead end — see doc 03 — but the *mapping* is sound and reusable for real decomp.)

## The forward-decomp plan (the only clean way past 1,696)

Drafts don't work (doc 03). The clean path is to **write correct C**, one function at a time, each landing
in its own context — no shared-TU perturbation. Prioritized by the encyclopedia:

1. **Simple unbanked klasses first** (`GETTER`/`SETTER`/`CONST_RETURN`/`TINY`, on the order of a few
   hundred not-yet-banked). Their bodies are mechanical:
   - `GETTER` → `return this->field;` (field = the struct member at the offset the asm reads).
   - `SETTER` → `this->field = arg;`
   - `CONST_RETURN` → `return <constant>;` (constant from `.rdata`/the immediate).
   - `TINY` → a one/two-statement body.
   The struct field offsets come from the `bw1-decomp` headers (`black/*.h`); the offset the function
   touches comes from its asm / the encyclopedia `summary`.
2. **Verify each in isolation:** write the body → compile its TU → `objdiff-cli report` → keep if 100%.
   Because each correct function is written for *its* real context, there's no perturbation; this is
   additive and safe (unlike drafts).
3. **Then `fanout-write-C` proper** (4432) — genuine per-function decomp for the multi-block functions.

### Tooling to build for this (next session)

- A **simple-klass C generator**: for each unbanked `GETTER`/`SETTER`/`CONST_RETURN`, read the struct from
  the header + the accessed offset, emit the body, drop it in the function's TU, compile, keep-if-100%.
  This is the natural successor to `port_banks.py` and would convert the encyclopedia's ~hundreds of simple
  unbanked functions into byte-exact matches cleanly.
- Reuse from `tools/`: the resolver/symbolizer (`symbolize.py`, `symbols.py`, `vtable.py`), `rdata.py`
  (constants for CONST_RETURN), and the `objdiff-cli diff` method from doc 01 to debug near-misses.

### Honest expectation

This is **per-function decomp**, not batch porting — slower, genuinely additive. The batch-portable work
(our existing verified banks) is done at 1,696. Everything beyond is real reverse-engineering, and the
encyclopedia is the map that makes it tractable and prioritized.
