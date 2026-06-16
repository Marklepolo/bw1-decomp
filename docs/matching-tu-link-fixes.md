# Linking a polymorphic Matching TU byte-exact

Upstream's libcmt/COMDAT work (dtk v0.0.9, commits `556178ad`/`d4c1e54a`) lets the **full link
run** for the first time. That exposes two latent issues in any *Matching* TU that defines a
**polymorphic class** (a class with a vtable + virtual destructor). `Black/Persistent` (the first
such TU) hit both. Both are toolchain artifacts, not source bugs — the C++ stays clean.

## 1. `??_R0` RTTI type descriptor — duplicate symbol

`lld-link: error: duplicate symbol: ??_R0?AV<Class>@@@8`

The class's RTTI **type descriptor** (`.data`) is emitted as a COMDAT by the Matching `.o` **and**
as a strong symbol by the `.data` baseline. lld-link errors on strong+COMDAT of the same name.

**Fix:** mark it `scope:weak` in `config/<ver>/symbols.txt` so the baseline copy becomes a
foldable COMDAT and lld folds the two (identical bytes). Leaves the `.data` layout untouched
(any trailing `__FILE__` string `lbl_…` stays in the baseline) — no carve/alignment risk.

```
??_R0?AVPersistent@@@8 = .data:0x00BEF860; // type:object size:0x19 scope:weak
```

## 2. `??_E` vector deleting destructor in the vtable — undefined symbol

`lld-link: error: undefined symbol: ??_E<Class>@@UAEPAXI@Z  (referenced by ??_7<Class>)`

Our MSVC6 c1xx front-end (OmniBlade `msvcwin9x`) emits the **VECTOR** deleting destructor `??_E`
in a polymorphic vtable's dtor slot; Lionhead's retail c1xx emitted the **SCALAR** deleting
destructor `??_G`. This is a pure **front-end codegen difference**, reproducible with **no**
available toolchain — verified across **7 MSVC6 front-ends** (6.0 / 6.3 / 6.4 / 6.5 / 6.5pp / 6.6 /
8047-beta) and the full flag matrix (`/Gd /Gr /Gz /Gy /Gc /Gh /GA /Gt /Gf /GF /vmg /vms /Zp* /Za …`)
plus every class shape (inline/implicit/out-of-line dtor, `operator new`/`delete`, base class,
member/usage variations). Like the run-once dtor guard, it needs Lionhead's exact c1xx.

The two forms are interchangeable for a never-array-deleted class, the retail vtable already points
at the `??_G` we emit **byte-exact**, and `??_E` has no body in our `.o` (only the vtable references
it). So alias the unreferenced `??_E` onto `??_G` at link:

```python
# configure.py: config.ldflags
"/alternatename:??_EPersistent@@UAEPAXI@Z=??_GPersistent@@UAEPAXI@Z",
```

The vtable slot then relocates to the real `??_G` (0x580A40) — byte-identical to retail, no spurious
`??_E` body. Add one `/alternatename` line per polymorphic Matching class.

## Result
`Black/Persistent` stays **Matching** and links byte-exact. The only remaining full-link error is
the pre-existing **libcmt gap** (`__Tolower_lk`/`__Toupper_lk`), which a local workaround config
(`modules: []`, dummy DLLs) hits but the CI's clean config + upstream's libcmt commits satisfy.

Both fixes are **project-wide**: every future polymorphic Matching TU needs the `??_R0` weak mark
and a `??_E→??_G` alias. A dtk-level auto-handling (emit the baseline `??_R0` weak; auto-alias each
`??_E` whose `??_G` exists) would remove the per-class boilerplate.
