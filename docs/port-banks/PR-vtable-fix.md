# PR: correct the Object->Mobile->MobileWallHug->Living C++ vtable layout

**Branch:** `pr/vtable-layout-fix` @ 9a6ec8c4 (off upstream/main 3afd16ab) — headers only
(`black/Object.h`, `black/Mobile.h`, `black/Living.h`), +130/-15, conflict-free.

## The bug (stock, in the canonical headers)
The C++ class virtual-declaration chain laid out vtable slots differently from the binary's
`??_7*@@6B@` arrays (and the authoritative `struct *Vftable`). So virtual calls compiled to
the WRONG slot: `Living::IsChild()` -> `[reg+0xAA8]`, binary dispatches at `0xAF8` (a 20-slot
drift shifting every virtual past it). This blocked expressive-C decomp of every
virtual-calling function in the Object hierarchy. The maintainer's own `_missing1/2/3`
placeholders marked some of these slots as not-yet-understood.

## Root causes (compiler-verified)
- **Object**: 3 slots declared non-virtual/mis-positioned, masked by `_missing` stubs ->
  identified as real virtuals `GetImpressiveValue()` @0x66c and `IsTouching(Object*,float)` @0x6b8.
- **Mobile**: 3 "overrides" had wrong signatures (const-ness, ptr-vs-ref) so MSVC APPENDED them
  as phantom new slots instead of overriding -> fixed to match the Object base.
- **Living**: declared ~34 fewer virtuals than `LivingVftable` -> added in struct order
  (0x878-0xb3c); fixed `InitialisePhysics`/`GetBoundingSphere` ptr->ref signatures.

## Verification method (the compiler is ground truth)
- `tools/probe_vtable.py` compiles real one-vcall functions with the exact Black `/FAcs` flags
  and reads the emitted `call [reg+0xNN]`. Confirms IsChild 0xAA8->0xAF8, IsDead 0xAF4,
  GetImpressiveValue 0x66c, IsSpellSeed 0x670, StartOnFire 0x6bc, GetTribalPower 0x6c8.
- `tools/vtable_drift.py --self-test`: zero drift across the chain (slot counts 535/535/541/720).
- `tools/bytecount.py`: global byte-exact unchanged on clean rebuild (NO regression) — layout fix.
(`probe_vtable.py` is offered as a tool in the PR notes if useful.)

## Game-side knowledge (now in the header comments)
- **GetImpressiveValue** - how awe-inducing an object is; the (Living*,Reaction*) form scores it
  for a specific onlooker -> feeds the creature/villager reaction + belief response.
- **IsTouching** - spatial overlap/contact test (physics, placement, proximity).
- **Mobile gesture/town overrides** - apply a gesture-spell to a map cell; town keep-clear (build placement).
- **Living reaction-AI block** - flee/look/follow/inspect objects, go-to food/wood, in-hand, food-speedup
  (the source->desire->action reaction system); + lifecycle (Dying/Dead/BeingEaten/Birthday/SetAge);
  + the *ForChessGame creature battle minigame.

## Open question for the maintainer (deliberately NOT changed)
`GetFoodType`@0x668 and `SetAge`@0x8d4 are mangled QAE (non-virtual) yet sit in the vtable. Evidence
they may be virtual: GetFoodType is in every derived vtable, called only via `[reg+0x668]`, never
overridden; SetAge has 11 vcall sites and `Villager::SetAge` OVERRIDES it (a non-virtual decl makes
that override land at the wrong slot 0xB54). Relabeling QAE->UAE would touch ~130 vftable-array
entries + symbols, so they're left as documented placeholders (`_vslot`) reserving the slot, flagged
for your decision rather than relabeled blindly.
