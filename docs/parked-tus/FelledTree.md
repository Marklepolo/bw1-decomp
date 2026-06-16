# FelledTree — parked Matching TU (BW1E142 / v1.42)

**Status:** drafted + byte-verified by disassembly, **blocked on headers**, currently a
header-free placeholder in `src/Black/FelledTree.cpp` and `Object(NonMatching, …)` in
`configure.py`. Restore (below) once the base headers are fixed.

**Why blocked:** `FelledTree.h → DeadTree.h → … → Object.h / MapCoords.h`, which the upstream
header import left incomplete (undefined `MapCoordsFull`, `LH3DObject__ObjectType`,
`MultiChildList`, missing `param_4` types). dtk compiles *every* `.cpp` that exists on disk
(even NonMatching units, for objdiff), so a body that `#include`s `FelledTree.h` breaks the
whole build — hence the placeholder.

## Game meaning
A **FelledTree** is a tree that has been chopped down — the trunk lying on the ground that
villagers gather as a **wood resource**. It sits in B&W's `DeadTree` branch of the object
tree (`FelledTree : DeadTree : … : GameThing : … : Object : Base`). Like every saveable game
object it reports a **save-game type id** (`0x71`) for serialization and a **debug-overlay
label** (`"FelledTree:"`).

## Class
```
class FelledTree : public DeadTree   // src/Black/FelledTree.h (header OK once base headers fixed)
```

## Own functions (3) — disassembly is the source of truth
| symbol | addr | size | behaviour |
|---|---|---|---|
| `?GetSaveType@FelledTree@@UAEIXZ` | `0x005118C0` | 0x10 | `mov eax,0x71; ret` → returns save-game type id **0x71** |
| `?GetDebugText@FelledTree@@UAEPADXZ` | `0x005118D0` | 0x10 | `mov eax,0xBE8A6C; ret` → returns ptr to string **"FelledTree:"** (data global `0x00BE8A6C`) |
| `??_GFelledTree@@UAEPAXI@Z` | `0x005118E0` | 0x30 | scalar-deleting dtor: `call 0x608750` (base dtor), then if flag set `operator delete(this, 0xA0)` → **sizeof = 0xA0** |

```asm
; GetSaveType @0x005118C0
mov eax, 0x71
ret
; GetDebugText @0x005118D0
mov eax, 0xBE8A6C        ; -> "FelledTree:"
ret
; ~FelledTree (??_G) @0x005118E0
push esi
mov  esi, ecx
call 0x608750            ; base/own dtor (folded chain)
test byte [esp+8], 1
je   skip
push 0xA0               ; sizeof(FelledTree) = 0xA0
push esi
call 0x436970          ; ??3Base operator delete
add  esp, 8
skip:
mov  eax, esi
pop  esi
ret  4
```

## RTTI / vtable
| item | addr |
|---|---|
| vtable `??_7FelledTree@@6B@` | `0x008D697C` |
| RTTI `??_R4FelledTree@@6B@` | `0x009AB8B0` |
| RTTI `??_R0?AVFelledTree@@@8` | `0x00BE8A50` |
| debug string `"FelledTree:"` | `0x00BE8A6C` |

Vtable: only slots **1** (`??_G`), and the two `DeadTree`-introduced slots holding
`GetDebugText` / `GetSaveType` are FelledTree's own; all other slots inherit from
`DeadTree`/`GameThing`/`Object`/`Base` (run `tools/analyze_tu.py FelledTree` for the full map).

## Restore recipe (when Object.h / MapCoords.h are fixed)
1. Replace `src/Black/FelledTree.cpp` with:
   ```cpp
   #include "FelledTree.h"
   uint32_t FelledTree::GetSaveType()  { return 0x71; }
   char*    FelledTree::GetDebugText() { return "FelledTree:"; }
   FelledTree::~FelledTree() {}
   ```
2. `configure.py`: flip to `Object(Matching, "Black/FelledTree.cpp")`.
3. Add a `config/BW1E142/splits.txt` entry (intended ranges; verify on build):
   ```
   Black/FelledTree.cpp:
       .text       start:0x005118C0 end:0x00511910
       .rdata      start:0x008D697C end:0x008D85A0   # vtable ??_7
       .rdata$r    start:0x009AB854 end:0x009AB8C4   # RTTI ??_R4 + base descriptors
   ```
   (and the `??_R0` type descriptor `0x00BE8A50` in `.data` — carve if it duplicates at link).
4. Build (`configure.py --version BW1E142` + long-path ninja `-k 0`) and objdiff
   (`objdiff-cli report generate -p . -o rep.json`) → expect `code=100%`, `3/3 functions`.

_Generated with `tools/analyze_tu.py FelledTree`; addresses are BW1E142 (`runblack-decrypted.exe`, ImageBase 0x00400000)._
