# LHPoint.cpp (Lionhead/LH3DLib/development) — TU notes

Lionhead 3D-lib 2D/3D vector primitives. Currently lifted: **`Point2D::GetNormSq`** (BW1E142).

## Point2D::GetNormSq — `0x006115F0`, symbol `?GetNormSq@Point2D@@QAEMXZ`

```cpp
float Point2D::GetNormSq()
{
    return x * x + y * y;
}
```

**Technical.** Returns the *squared* Euclidean norm of the 2D vector `(x, y)`. `Point2D` is a
plain struct — `float x` @0x0, `float y` @0x4 (no vtable / RTTI). The function is a self-contained
leaf: no calls, no branches, no memory writes. MSVC6 `/O2` emits a quirky-but-deterministic x87
schedule (load both members, duplicate for the squares, add, then pop the spare stack slots):

```
d9 41 04   fld   [ecx+4]   ; y
d9 01      fld   [ecx]      ; x
d9 c0      fld   st(0)      ; dup x
d8 c9      fmul  st(1)      ; x*x
d9 c2      fld   st(2)      ; y
d8 cb      fmul  st(3)      ; y*y
de c1      faddp st(1)      ; x*x + y*y
dd da      fstp  st(2)      ; pop spare
dd d8      fstp  st(0)      ; pop spare
c3         ret             ; result in st(0)
```

20 bytes, then nop padding to the 0x20 symbol size. `return x*x + y*y;` reproduces all 20 bytes
exactly — including the redundant `fld st(0)` / `fstp` cleanup that is the MSVC6 fingerprint.

**Game.** Squared-magnitude is the workhorse for *horizontal-plane distance* throughout B&W: range
checks, nearest-target selection, pathing proximity. Comparing squared distances avoids a per-call
`sqrt`, so the engine uses `GetNormSq` (and compares against a squared threshold) on hot paths;
the true length (`Normalize`/`GetNorm`) is computed only when the actual magnitude is needed.

## Why this TU matters (method notes)

- **First genuine lift in a Lionhead SDK TU.** Earlier genuine lifts were in `Black/`
  (MPFEConnectionStatus, CameraHelp). LH3DLib had no compiled unit before this; the unit name is
  `Lionhead/LH3DLib/development/LHPoint.cpp` (source root `src/`), header resolved via `/I include`
  → `include/lionhead/lh3dlib/development/LHPoint.h` (the *repaired* copy; the stale `src/` copy has
  the auto-gen duplicate decls and is not on the include path).
- **`MatchingFor("BW1E142")`** — matching is claimed for v1.42 only; v1.00/v1.10 stay NonMatching
  (carved) until separately verified.
- **COMDAT links cleanly.** `GetNormSq` is emitted `Communal` (COMDAT). It folds with the carved
  copies at link with no duplicate-symbol error — the COMDAT path the maintainer recommends, and
  the reason a member function of a shared struct links here where non-COMDAT class methods dup.
- **Gate (WSL):** built in the `bw1-rtti` worktree (ext4, case-sensitive — avoids the NTFS
  filename-collision). Proof = the **empty-body differential**: with the real body the bytes at
  0x6115F0 equal the orig (`d9 41 04 … dd d8 c3`); replacing the body with `return 0.0f;` changes
  those exact bytes (`d9 05 …`) → the `.o` is genuinely LINKED, not dtk-carved. (Whole-exe sha is
  non-deterministic in this build due to the unrelated libcmt/CRT link gap, so the proof rests on
  the deterministic per-VA bytes, not the exe hash.)
