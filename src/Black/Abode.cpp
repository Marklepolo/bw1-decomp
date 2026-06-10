#include "MultiMapFixed.h"
#include "MultiMapFixed.h"
#include "MultiMapFixed.h"
#include "MultiMapFixed.h"
#include "MultiMapFixed.h"
#include "MultiMapFixed.h"
#include "MultiMapFixed.h"
#include "Abode.h"
#include "AbodeInfo.h"
#include "Audio.h"
#include "BaseInfo.h"
#include "ControlHand.h"
#include "Fixed.h"
#include "Game.h"
#include "Game3DObject.h"
#include "GameOSFile.h"
#include "GameStats.h"
#include "GameThing.h"
#include "GameThingWithPos.h"
#include "Global.h"
#include "InterfaceStatus.h"
#include "Object.h"
#include "ObjectInfo.h"
#include "PlannedAbode.h"
#include "PlannedMultiMapFixed.h"
#include "Player.h"
#include "Rand.h"
#include "SoundGuidance.h"
#include "Town.h"
#include "TownInfo.h"
#include "Utils.h"
#include "Villager.h"
#include "VillagerInfo.h"
#include "ViscousLiquid.h"
#include "Windmill.h"
#include "stdbool.h"
#include <cstddef>
#include <lionhead/lh3dlib/development/LH3DCamera.h>
#include <lionhead/lh3dlib/development/LH3DMem.h>
#include <lionhead/lh3dlib/development/LH3DMesh.h>
#include <lionhead/lhaudio/ver7.0/LH_SamplePlayOptions.h>
#include <stdint.h>

Town* abode_town_00c4cc6c;
extern "C" GGame* game;
extern "C" GGlobal global;
extern "C" LH3DCamera g_camera;
extern "C" int windmill_int_00c4cc7c;
extern "C" void Draw__13HowManyPeopleFllP7LHPoint(uint32_t, uint32_t, LHPoint*);
extern "C" void KnockKnock__13HowManyPeopleFv(void);
GAbodeInfo infossss[0x93];

// win1.41 00402bc0 mac inlined Abode::SetToZero(void)
// Zero-initialise the Abode-specific state (everything past the MultiMapFixed base):
// villager population tallies (adult_count, field_0xb5/0xb6/0xb7), the two resource
// stores (resources[FOOD]=0xbc, resources[WOOD]=0xc0), the smoke/destruction meshes,
// and a few scalar flags. Called once from the constructor before anything else fills
// these in. Retail keeps eax=0 (xor) and stores it to each field in this exact order;
// EXPRESSIVE C - no asm-wrap.
void Abode::SetToZero()
{
    field_0xb6 = 0;
    adult_count = 0;
    field_0xb7 = 0;
    field_0x94 = 0;
    resources[0] = 0;
    resources[1] = 0;
    smoke = NULL;
    destruction_mesh = NULL;
    field_0x7c = 0;
    field_0xb0 = 0;
    field_0xb5 = 0;
    field_0xb9 = 0;
}

// win1.41 00401350 mac 1033b330 Abode::Abode(MapCoords const &, GAbodeInfo const *, Town *, float, float, float, int)
Abode::Abode(const MapCoords& coords, const GAbodeInfo* info, Town* _town, float y_angle, float scale, float food, int wood)
    : MultiMapFixed(coords, (const GMultiMapFixedInfo*)info, y_angle, scale, food, wood)
    , drinking_water(0, 0)
{
    SetToZero();
    if (_town)
    {
        _town->AddStructureToTown(this);
        index = (uint8_t)town.payload->abode_list.count - 1;
    }

    game->map.field_0x8 |= 1;

    FindNearestDrinkingWater(200.0f);
}

// win1.41 00401400 mac 10513b00 FixedObject::CanBeFrighteningToCreature(Creature *)
bool32_t Fixed::CanBeFrighteningToCreature(Creature* creature)
{
    return false;
}

// win1.41 00401410 mac 10570f10 FixedObject::CanBeSleptNextToByCreature(Creature *)
bool32_t Fixed::CanBeSleptNextToByCreature(Creature* creature)
{
    return true;
}

// win1.41 00401420 mac 105e81f0 FixedObject::CanBeDestroyedByStoning(Creature *)
bool32_t Fixed::CanBeDestroyedByStoning(Creature* creature)
{
    return true;
}

// win1.41 00401430 mac 100b19c0 FixedObject::CanBeSetOnFire(Creature *)
bool32_t Fixed::CanBeSetOnFire(Creature* creature)
{
    return (field_0xa & 0x8) == 0;
}

// win1.41 00401440 mac 1056c2a0 FixedObject::CanBePickedUpByCreature(Creature *)
bool32_t Fixed::CanBePickedUpByCreature(Creature* creature)
{
    return false;
}

// win1.41 00401450 mac 1057a200 FixedObject::CanBeCrushed(void)
bool32_t Fixed::CanBeCrushed()
{
    return true;
}

// win1.41 00401460 mac 10554e40 FixedObject::VillagerMustAvoid(Villager *)
bool32_t Fixed::VillagerMustAvoid(Villager* param_1)
{
    return true;
}

// win1.41 00401470 mac 1057ad40 FixedObject::GetTownArtifact(void)
GameThing* Fixed::GetTownArtifact()
{
    return town_artifact;
}

// win1.41 00401480 mac 10588280 FixedObject::IsTownArtifact(void)
// Returns whether this fixed object has been claimed as a town artifact. The
// engine stores the owning artifact as a pointer (town_artifact, +0x54); a
// non-null pointer means "yes". Emits the canonical MSVC pointer-to-bool test
// (mov edx,[ecx+0x54]; xor eax,eax; test edx,edx; setne al).
bool32_t Fixed::IsTownArtifact()
{
    return town_artifact != NULL;
}

// win1.41 00401550 mac 1035b520 MultiMapFixed::SetPower(float)
// No-op in the base class: only powered structures (e.g. Wonders / worship sites)
// carry per-tribe power, so the generic setter does nothing here.
void MultiMapFixed::SetPower(float power)
{
}

// win1.41 00401640 mac 105602b0 Abode::CastAbode(void)
Abode* Abode::CastAbode()
{
    return this;
}

// win1.41 00401650 mac 10565230 Abode::GetShouldNotBeAddedToPlanned(void)
bool32_t Abode::GetShouldNotBeAddedToPlanned()
{
    return (field_0x7c & 4) != 0;
}

// win1.41 00401660 mac 1031a9a0 Abode::SetShouldNotBeAddedToPlanned(int)
void Abode::SetShouldNotBeAddedToPlanned(bool value)
{
    field_0x7c = (field_0x7c & ~(1 << 2)) | ((value & 1) << 2);
}

// win1.41 00401680 mac 10371be0 Abode::RestartBeingFunctional(void)
void Abode::RestartBeingFunctional()
{
}

// win1.41 00401690 mac 1037f370 Abode::SetTown(Town *)
void Abode::SetTown(Town* _town)
{
    town.payload = _town;
}

// win1.41 004016a0 mac 10066b80 Abode::IsRepaired(void)
bool32_t Abode::IsRepaired()
{
    return GetPercentRepaired() >= 1.0f;
}

// win1.41 004016c0 mac 10055bb0 Abode::IsBuilt(void)
bool32_t Abode::IsBuilt()
{
    return ((field_0x58 & 2) != 2) && GetPercentBuilt() >= 1.0f;
}

// win1.41 004016f0 mac 101cbc80 Abode::CausesTownEmergencyIfDamaged(void)
bool32_t Abode::CausesTownEmergencyIfDamaged()
{
    return false;
}

// win1.41 00401700 mac 105756c0 Abode::GetDestructionMesh(void)
FragMesh* Abode::GetDestructionMesh()
{
    return destruction_mesh;
}

// win1.41 00401710 mac 100970f0 Abode::IsAbode(void)
bool32_t Abode::IsAbode()
{
    return true;
}

// win1.41 00401720 mac 10435a10 Abode::IsCastShadowAtNight(void)
bool32_t Abode::IsCastShadowAtNight()
{
    return true;
}

// win1.41 00401730 mac 1004fe30 Abode::GetTown(void)
Town* Abode::GetTown()
{
    return town.payload;
}

// win1.41 00401740 mac 1040f9d0 Abode::GetCreatureBeliefType(void)
uint32_t Abode::GetCreatureBeliefType()
{
    return 3;
}

// win1.41 00401750 mac 100a48c0 Abode::GetCreatureMimicType(void)
uint32_t Abode::GetCreatureMimicType()
{
    return 5;
}

// win1.41 00401760 mac 10110c50 Abode::GetOrigin(void)
uint32_t Abode::GetOrigin()
{
    return 1;
}

// win1.41 00401770 mac 1000c2b0 Abode::GetArrivePos(void)
MapCoords Abode::GetArrivePos()
{
    return GetDoorPos();
}

// win1.41 00401790 mac 10134300 Abode::IsHouse(void)
bool32_t Abode::IsHouse()
{
    return true;
}

// win1.41 004017a0 mac 103e1790 Abode::GetSaveType(void)
uint32_t Abode::GetSaveType()
{
    return 7;
}

// win1.41 004017b0 mac 10434340 Abode::GetDebugText(void)
char* Abode::GetDebugText()
{
    return "Abode:";
}

// win1.41 004017f0 mac 10437b00 GameThing::CalculateInfluence(MapCoords const &)
// Base influence weight for a game thing at a queried map position. The generic
// GameThing contributes a neutral, full-strength factor of 1.0; subclasses scale
// this by type/state. Compiles to a single fld of the 1.0 float literal.
float GameThing::CalculateInfluence(const MapCoords& param_1)
{
    return 1.0f;
}

// win1.41 00401800 mac 10494700 GameThing::RemoveDance(void)
void GameThing::RemoveDance()
{
}

// win1.41 00401820 mac 10494880 GameThing::IsCreature(Creature *)
bool32_t GameThing::IsCreature(Creature* param_1)
{
    return false;
}

// win1.41 00401840 mac 104948c0 GameThing::IsCreatureNotTooNear(Creature *)
bool32_t GameThing::IsCreatureNotTooNear(Creature* param_1)
{
    return false;
}

// win1.41 00401850 mac 10428ff0 GameThing::GetMaxAlignmentChangePerGameTurn(void)
float GameThing::GetMaxAlignmentChangePerGameTurn()
{
    return 0.0f;
}

// win1.41 00401860 mac 10425a40 GameThing::GetComputerSeen(void)
bool32_t GameThing::GetComputerSeen()
{
    return false;
}

// win1.41 00401870 mac 10389a40 GameThing::GetVillagerActivityDesire(Villager *)
// How much a villager "wants" to use/interact with this thing as an activity. The
// base game thing offers no inherent activity, so the desire is 0.0; classes like
// abodes/fields/wells override with a real desire. Emits fld of the 0.0 literal.
float GameThing::GetVillagerActivityDesire(Villager* param_1)
{
    return 0.0f;
}

// win1.41 00401880 mac 10389ac0 GameThing::SetVillagerActivity(Villager *)
uint32_t GameThing::SetVillagerActivity(Villager* param_1)
{
    return 0;
}

// win1.41 00401890 mac 1037f2e0 GameThing::UpdateVillagerActivityEffect(Villager *)
uint32_t GameThing::UpdateVillagerActivityEffect(Villager* param_1)
{
    return 0;
}

// win1.41 004018a0 mac 101664f0 GameThing::GetPlayerWhoLastPickedMeUp(void)
GPlayer* GameThing::GetPlayerWhoLastPickedMeUp()
{
    return NULL;
}

// win1.41 004018b0 mac 10381da0 GameThing::GetPlayerWhoLastDroppedMe(void)
GPlayer* GameThing::GetPlayerWhoLastDroppedMe()
{
    return NULL;
}

// win1.41 004018c0 mac 101063a0 GameThing::AddFootpathLink(GFootpath *)
uint32_t GameThing::AddFootpathLink(GFootpath* param_1)
{
    return 0;
}

// win1.41 004018d0 mac 103dd790 GameThing::CastCreature(void)
Creature* GameThing::CastCreature()
{
    return NULL;
}

// win1.41 004018e0 mac 103dd5d0 GameThing::CastPlayer(void)
GPlayer* GameThing::CastPlayer()
{
    return NULL;
}

// win1.41 004018f0 mac 104fb790 GameThing::CastOneOffSpellSeed(void)
SpellSeed* GameThing::CastOneOffSpellSeed()
{
    return NULL;
}

// win1.41 00401900 mac 100a0a70 GameThing::CastSpellIcon(void)
SpellIcon* GameThing::CastSpellIcon()
{
    return NULL;
}

// win1.41 00401910 mac 101c8320 GameThing::CastTree(void)
Tree* GameThing::CastTree()
{
    return NULL;
}

// win1.41 00401920 mac 1019e2b0 GameThing::IsDeletedOnNewMap(void)
bool32_t GameThing::IsDeletedOnNewMap()
{
    return true;
}

// win1.41 00401930 mac 1017a550 GameThing::GetShowNeedsPos(unsigned long, MapCoords *)
uint32_t GameThing::GetShowNeedsPos(uint32_t param_1, MapCoords* param_2)
{
    return 0;
}

// win1.41 00401940 mac 103e0b80 GameThingWithPos::SetPos(MapCoords const &)
// Stores a new map position by copying the three 4-byte fields (x, z, altitude)
// of the source MapCoords into this object's coords member (+0x14). Inlined
// member-wise copy; ret 4.
void GameThingWithPos::SetPos(const MapCoords& param_1)
{
    coords = param_1;
}

// win1.41 00401960 mac 103e0bd0 GameThingWithPos::GetPos(void)
// SKIPPED (header decl mismatch): the retail symbol is the *non-virtual* public
// ?GetPos@GameThingWithPos@@QAEPAUMapCoords@@XZ (returns MapCoords* into a caller
// buffer), but GameThingWithPos.h declares GetPos only as a *virtual* returning
// MapCoords by value (?...@UAE?AUMapCoords@@XZ, vtable /* 0x100 */). Defining the
// non-virtual form needs a separate `MapCoords* GetPos()` decl in the synced
// header; left out to avoid header churn. Body would be the same x/z/altitude copy.

// win1.41 00402610 mac 1005f530 Object::IsAlive(void)
// TECH: GetLife() (vtable +0x11c, returns float) is compared > 0.0f via the MSVC
// fcomp [const]/fnstsw/test ah,0x41 idiom; the && short-circuits to GameThing::
// IsAvailable() (vtable +0x2c, returns int) only when life is positive. eax = 1
// when both hold, else 0. (Both calls are virtual -> dispatched through the vptr.)
// GAME: the engine's standard "is this thing still a live, actionable object?"
// predicate -- true only if it has positive life/health AND is currently available
// (not destroyed, removed, or otherwise disabled). Used before acting on an object.
bool32_t Object::IsAlive()
{
    return GetLife() > 0.0f && IsAvailable();
}

// win1.41 00401820 GameThing::IsCreature(void)  [?IsCreature@GameThing@@UAEIXZ]
// TECH: base returns 0 (xor eax,eax; ret) -- the plain no-arg virtual form. (NB: the header's
// address comments for the two IsCreature overloads are swapped; the mangled asm() bindings are
// the authority -- UAEIXZ is the void form at 0x401820.)
// GAME: the GameThing base is NOT a creature; only the Creature subclass overrides this to return
// true. It is the default leaf of the "is this thing a creature?" type query the AI/engine uses.
bool32_t GameThing::IsCreature()
{
    return 0;
}

// win1.41 00401500 MultiMapFixed::GetPercentRepaired(void)  [?GetPercentRepaired@MultiMapFixed@@UAEMXZ]
// TECH: tail-calls the virtual GetLife() (vtable +0x11c) -> mov eax,[ecx]; jmp [eax+0x11c]. The repair
// fraction IS the life value, forwarded (not recomputed).
// GAME: a building/wall's repair progress is read straight from its life/health -- damage lowers life,
// repairing raises it, so percent-repaired == current life. (Damaged/non-functional states have their
// own overrides: GetPercentRepairedFromWhenDamaged / ...ForNonFunctional.)
// NOTE: this body is BYTE-EXACT (mov eax,[ecx]; jmp [eax+0x11c]) but the report scores it 16.7% because
// the dtk target boundary for this symbol extends to the NEXT symbol (0x401520), swallowing 8 alignment
// nops + an unlabeled orphan fn (xor eax,eax; ret 4 @0x401510). It reaches 100% once 0x401510 is split
// (needs a reconfigure -- objdiff ignores live symbols.txt size edits). Left in: the code is correct.
float MultiMapFixed::GetPercentRepaired()
{
    return GetLife();
}

// win1.41 00401980 mac 103e0c40 GameThingWithPos::PhysicsEditorCreate(int)
// Map/physics-editor placement hook. The base implementation only resets the
// object's altitude (coords.altitude, +0x1c) to ground level (0.0); the integer
// argument selects the editor mode but is unused at this level. Compiles to a
// single mov dword [ecx+0x1c],0 then ret 4.
void GameThingWithPos::PhysicsEditorCreate(int param_1)
{
    coords.altitude = 0.0f;
}

// win1.41 00401990 mac 103e0cc0 GameThingWithPos::GetCreatureBeliefListType(void)
uint32_t GameThingWithPos::GetCreatureBeliefListType()
{
    return 1;
}

// win1.41 004019a0 mac 103e0d50 GameThingWithPos::GetCitadel(void)
Citadel* GameThingWithPos::GetCitadel()
{
    return 0;
}

// win1.41 004019b0 mac 103e1140 GameThingWithPos::SetHeight(float)
void GameThingWithPos::SetHeight(float height)
{
}

// win1.41 004019c0 mac 103e3580 GameThingWithPos::SetMaxHeight(float)
void GameThingWithPos::SetMaxHeight(float height)
{
}

// win1.41 004019d0 mac 103e11c0 GameThingWithPos::GetMaxHeight(void)
float GameThingWithPos::GetMaxHeight()
{
    return 0;
}

// win1.41 004019e0 mac 103e1180 GameThingWithPos::IsAnimate(void)
bool32_t GameThingWithPos::IsAnimate()
{
    return 0;
}

// win1.41 00401a10 mac 100cb2b0 GameThingWithPos::IsCannotBePickedUp( const(void))
bool32_t GameThingWithPos::IsCannotBePickedUp() const
{
    return ((uint16_t)*(uint16_t*)((char*)this + 0x24) >> 0xd) & 1;
}

// win1.41 00401a20 mac 100cb270 GameThingWithPos::IsStompable(void)
bool32_t GameThingWithPos::IsStompable()
{
    return 0;
}

// win1.41 00401a30 mac 100cb210 GameThingWithPos::IsAvailableForStateChange(void)
bool32_t GameThingWithPos::IsAvailableForStateChange()
{
    return ((uint8_t)~*(uint8_t*)((char*)this + 0x24) >> 2) & 1;
}

// win1.41 00401a40 mac 103104e0 GameThingWithPos::GetImpressiveIntensity(IMPRESSIVE_TYPE)
float GameThingWithPos::GetImpressiveIntensity(IMPRESSIVE_TYPE type)
{
    return 0;
}

// win1.41 00401a50 mac 1002b190 GameThingWithPos::IsTown(Creature *)
bool32_t GameThingWithPos::IsTown(Creature* param_1)
{
    return 0;
}

// win1.41 00401a60 mac 103efcc0 GameThingWithPos::IsActivityObjectWhichAngerAppliesTo(Creature *)
bool32_t GameThingWithPos::IsActivityObjectWhichAngerAppliesTo(Creature* param_1)
{
    return 0;
}

// win1.41 00401a70 mac 100c8d70 GameThingWithPos::IsActivityObjectWhichCompassionAppliesTo(Creature *)
bool32_t GameThingWithPos::IsActivityObjectWhichCompassionAppliesTo(Creature* param_1)
{
    return 0;
}

// win1.41 00401a80 mac 10381cb0 GameThingWithPos::IsActivityObjectWhichPlayfulnessAppliesTo(Creature *)
bool32_t GameThingWithPos::IsActivityObjectWhichPlayfulnessAppliesTo(Creature* param_1)
{
    return 0;
}

// win1.41 00401a90 mac 1055f950 GameThingWithPos::IsTownBelongingToAnotherPlayer(Creature *)
bool32_t GameThingWithPos::IsTownBelongingToAnotherPlayer(Creature* param_1)
{
    return 0;
}

// win1.41 00401aa0 mac 10354120 GameThingWithPos::TrueFunction(void)
bool32_t GameThingWithPos::TrueFunction()
{
    return 1;
}

// win1.41 00401ab0 mac 100c53e0 GameThingWithPos::FalseFunction(void)
bool32_t GameThingWithPos::FalseFunction()
{
    return 0;
}

// win1.41 00401ac0 mac 10174ec0 GameThingWithPos::IsNotLiving(void)
bool32_t GameThingWithPos::IsNotLiving()
{
    return 1;
}

// win1.41 00401ad0 mac 100a9d40 GameThingWithPos::IsSuitableForCreatureActivity(void)
bool32_t GameThingWithPos::IsSuitableForCreatureActivity()
{
    return 0;
}

// win1.41 00401ae0 mac 100d3ed0 GameThingWithPos::IsTown(void)
bool32_t GameThingWithPos::IsTown()
{
    return 0;
}

// win1.41 00401af0 mac 10093ec0 GameThingWithPos::IsTownCentre(void)
bool32_t GameThingWithPos::IsTownCentre()
{
    return 0;
}

// win1.41 00401b00 mac 101a36a0 GameThingWithPos::IsTotemStatue(void)
bool32_t GameThingWithPos::IsTotemStatue()
{
    return 0;
}

// win1.41 00401b10 mac 103d8ae0 GameThingWithPos::IsTownDesireFlag(void)
bool32_t GameThingWithPos::IsTownDesireFlag()
{
    return 0;
}

// win1.41 00401b20 mac 10135ee0 GameThingWithPos::IsRock(void)
bool32_t GameThingWithPos::IsRock()
{
    return 0;
}

// win1.41 00401b30 mac 103d8b30 GameThingWithPos::IsSpellDispenser(void)
bool32_t GameThingWithPos::IsSpellDispenser()
{
    return 0;
}

// win1.41 00401b40 mac 100c3630 GameThingWithPos::IsMist(void)
bool32_t GameThingWithPos::IsMist()
{
    return 0;
}

// win1.41 00401b50 mac 10097020 GameThingWithPos::IsQueryIcon(void)
bool32_t GameThingWithPos::IsQueryIcon()
{
    return 0;
}

// win1.41 00401b60 mac 105e81b0 GameThingWithPos::IsStreetLight(void)
bool32_t GameThingWithPos::IsStreetLight()
{
    return 0;
}

// win1.41 00401b70 mac 104a63f0 GameThingWithPos::IsStreetLantern(void)
bool32_t GameThingWithPos::IsStreetLantern()
{
    return 0;
}

// win1.41 00401b80 mac 105e8170 GameThingWithPos::IsField(void)
bool32_t GameThingWithPos::IsField()
{
    return 0;
}

// win1.41 00401b90 mac 1009eea0 GameThingWithPos::IsMagicFireBall(void)
bool32_t GameThingWithPos::IsMagicFireBall()
{
    return 0;
}

// win1.41 00401ba0 mac 104a8310 GameThingWithPos::IsCitadelHeart(void)
bool32_t GameThingWithPos::IsCitadelHeart()
{
    return 0;
}

// win1.41 00401bd0 mac 100c7090 GameThingWithPos::CanBeHealedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeHealedByCreature(Creature* creature)
{
    return 0;
}

// win1.41 00401be0 mac 104956c0 GameThingWithPos::CanBeBefriendedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeBefriendedByCreature(Creature* creature)
{
    return 0;
}

// win1.41 00401bf0 mac 102fe080 GameThingWithPos::CanBeKissedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeKissedByCreature(Creature* creature)
{
    return 0;
}

// win1.41 00401c00 mac 10569b20 GameThingWithPos::CanBeGivenToVillager(Creature *)
bool32_t GameThingWithPos::CanBeGivenToVillager(Creature* creature)
{
    return 0;
}

// win1.41 00401c50 mac 100d4ba0 GameThingWithPos::CanBeFoughtByCreature(Creature *)
bool32_t GameThingWithPos::CanBeFoughtByCreature(Creature* creature)
{
    return 0;
}

// win1.41 00401c60 mac 1038a3e0 GameThingWithPos::CanReceiveGifts(Creature *)
bool32_t GameThingWithPos::CanReceiveGifts(Creature* creature)
{
    return 0;
}

// win1.41 00401c70 mac 103dc5a0 GameThingWithPos::CanActAsAContainer(Creature *)
bool32_t GameThingWithPos::CanActAsAContainer(Creature* creature)
{
    return 0;
}

// win1.41 00401ca0 mac 10596ca0 GameThingWithPos::CanBeUsedForBuilding(Creature *)
bool32_t GameThingWithPos::CanBeUsedForBuilding(Creature* creature)
{
    return 0;
}

// win1.41 00401cb0 mac 100a8420 GameThingWithPos::IsMushroom(Creature *)
bool32_t GameThingWithPos::IsMushroom(Creature* creature)
{
    return 0;
}

// win1.41 00401cc0 mac 100be460 GameThingWithPos::CanBeUsedForRepair(Creature *)
bool32_t GameThingWithPos::CanBeUsedForRepair(Creature* creature)
{
    return 0;
}

// win1.41 00401cd0 mac 103efed0 GameThingWithPos::CanBeGivenToTown(Creature *)
bool32_t GameThingWithPos::CanBeGivenToTown(Creature* creature)
{
    return 0;
}

// win1.41 00401ce0 mac 103efe80 GameThingWithPos::CanBeUsedToHoldWater(Creature *)
bool32_t GameThingWithPos::CanBeUsedToHoldWater(Creature* creature)
{
    return 0;
}

// win1.41 00401cf0 mac 1054aa20 GameThingWithPos::CanHaveMagicFoodCastOnMe(Creature *)
bool32_t GameThingWithPos::CanHaveMagicFoodCastOnMe(Creature* creature)
{
    return 0;
}

// win1.41 00401d00 mac 1057ace0 GameThingWithPos::CanHaveMagicWoodCastOnMe(Creature *)
bool32_t GameThingWithPos::CanHaveMagicWoodCastOnMe(Creature* creature)
{
    return 0;
}

// win1.41 00401d10 mac 10091d50 GameThingWithPos::IsVillager(Creature *)
bool32_t GameThingWithPos::IsVillager(Creature* creature)
{
    return 0;
}

// win1.41 00401d20 mac 10478860 GameThingWithPos::IsVillagerFarFromHome(Creature *)
bool32_t GameThingWithPos::IsVillagerFarFromHome(Creature* creature)
{
    return 0;
}

// win1.41 00401d30 mac 1036e6c0 GameThingWithPos::IsVillagerInTownWithoutManyBreeders(Creature *)
bool32_t GameThingWithPos::IsVillagerInTownWithoutManyBreeders(Creature* creature)
{
    return 0;
}

// win1.41 00401d40 mac 101343a0 GameThingWithPos::IsVillagerNotWorshipping(Creature *)
bool32_t GameThingWithPos::IsVillagerNotWorshipping(Creature* creature)
{
    return 0;
}

// win1.41 00401d50 mac 1036f100 GameThingWithPos::IsVillagerBelongingToOtherPlayer(Creature *)
bool32_t GameThingWithPos::IsVillagerBelongingToOtherPlayer(Creature* creature)
{
    return 0;
}

// win1.41 00401d60 mac 101107f0 GameThingWithPos::IsCow(Creature *)
bool32_t GameThingWithPos::IsCow(Creature* creature)
{
    return 0;
}

// win1.41 00401d70 mac 102aa900 GameThingWithPos::IsVillagerWhoHasNotBeenImpressedRecently(Creature *)
bool32_t GameThingWithPos::IsVillagerWhoHasNotBeenImpressedRecently(Creature* creature)
{
    return 0;
}

// win1.41 00401d80 mac 10569bf0 GameThingWithPos::IsVillagerWhoHasNotBeenDancedWithRecently(Creature *)
bool32_t GameThingWithPos::IsVillagerWhoHasNotBeenDancedWithRecently(Creature* creature)
{
    return 0;
}

// win1.41 00401d90 mac 10336360 GameThingWithPos::DoesVillagerBelongToATownWhichIsAlreadyImpressed(Creature *)
bool32_t GameThingWithPos::DoesVillagerBelongToATownWhichIsAlreadyImpressed(Creature* creature)
{
    return 0;
}

// win1.41 00401da0 mac 100fc2f0 GameThingWithPos::DoesTotemBelongToATownWhichIsVeryImpressedIndeed(Creature *)
bool32_t GameThingWithPos::DoesTotemBelongToATownWhichIsVeryImpressedIndeed(Creature* creature)
{
    return 0;
}

// win1.41 00401db0 mac 103c9640 GameThingWithPos::IsDominantCreature(Creature *)
bool32_t GameThingWithPos::IsDominantCreature(Creature* creature)
{
    return 0;
}

// win1.41 00401dc0 mac 100e9bb0 GameThingWithPos::CanBeDancedWith(Creature *)
bool32_t GameThingWithPos::CanBeDancedWith(Creature* creature)
{
    return 0;
}

// win1.41 00401dd0 mac 103c91e0 GameThingWithPos::IsAggressive(Creature *)
bool32_t GameThingWithPos::IsAggressive(Creature* creature)
{
    return 0;
}

// win1.41 00401de0 mac 100ed8f0 GameThingWithPos::IsStoragePit(Creature *)
bool32_t GameThingWithPos::IsStoragePit(Creature* creature)
{
    return 0;
}

// win1.41 00401df0 mac 103d4fd0 GameThingWithPos::IsWorshipSite(void)
bool32_t GameThingWithPos::IsWorshipSite()
{
    return 0;
}

// win1.41 00401e00 mac 10553fb0 GameThingWithPos::IsWorshipSite(Creature *)
bool32_t GameThingWithPos::IsWorshipSite(Creature* creature)
{
    return 0;
}

// win1.41 00401e10 mac 10136890 GameThingWithPos::GetWorshipSite(void)
WorshipSite* GameThingWithPos::GetWorshipSite()
{
    return 0;
}

// win1.41 00401e20 mac 1042dbb0 GameThingWithPos::IsWorkshop(Creature *)
bool32_t GameThingWithPos::IsWorkshop(Creature* creature)
{
    return 0;
}

// win1.41 00401e30 mac 104964f0 GameThingWithPos::IsStoragePitWithFoodInIt(Creature *)
bool32_t GameThingWithPos::IsStoragePitWithFoodInIt(Creature* creature)
{
    return 0;
}

// win1.41 00401e40 mac 104c28e0 GameThingWithPos::IsField(Creature *)
bool32_t GameThingWithPos::IsField(Creature* creature)
{
    return 0;
}

// win1.41 00401e50 mac 1048f2b0 GameThingWithPos::IsFieldWhichNeedsWatering(Creature *)
bool32_t GameThingWithPos::IsFieldWhichNeedsWatering(Creature* creature)
{
    return 0;
}

// win1.41 00401e60 mac 1054fb10 GameThingWithPos::IsFieldWithFoodInIt(Creature *)
bool32_t GameThingWithPos::IsFieldWithFoodInIt(Creature* creature)
{
    return 0;
}

// win1.41 00401e70 mac 1054f730 GameThingWithPos::IsFieldBelongingToAnotherPlayer(Creature *)
bool32_t GameThingWithPos::IsFieldBelongingToAnotherPlayer(Creature* creature)
{
    return 0;
}

// win1.41 00401e80 mac 100b1d40 GameThingWithPos::IsStoragePitBelongingToAnotherPlayer(Creature *)
bool32_t GameThingWithPos::IsStoragePitBelongingToAnotherPlayer(Creature* creature)
{
    return 0;
}

// win1.41 00401e90 mac 10379d10 GameThingWithPos::IsStoragePitBelongingToMyPlayer(Creature *)
bool32_t GameThingWithPos::IsStoragePitBelongingToMyPlayer(Creature* creature)
{
    return 0;
}

// win1.41 00401ea0 mac 1055e010 GameThingWithPos::BenefitsFromHavingWaterSprinkledOnIt(Creature *)
bool32_t GameThingWithPos::BenefitsFromHavingWaterSprinkledOnIt(Creature* creature)
{
    return 0;
}

// win1.41 00401eb0 mac 1055e440 GameThingWithPos::IsTree(void)
bool32_t GameThingWithPos::IsTree()
{
    return 0;
}

// win1.41 00401ec0 mac 10159e90 GameThingWithPos::IsTreeNotTooNearPlannedForest(Creature *)
bool32_t GameThingWithPos::IsTreeNotTooNearPlannedForest(Creature* creature)
{
    return 0;
}

// win1.41 00401ed0 mac 1017ac30 GameThingWithPos::IsTreeBigEnoughForCreature(Creature *)
bool32_t GameThingWithPos::IsTreeBigEnoughForCreature(Creature* creature)
{
    return 0;
}

// win1.41 00401ee0 mac 10552270 GameThingWithPos::IsAFoodPileOutsideStoragePit(Creature *)
bool32_t GameThingWithPos::IsAFoodPileOutsideStoragePit(Creature* creature)
{
    return 0;
}

// win1.41 00401ef0 mac 1055e160 GameThingWithPos::IsAWoodPileOutsideStoragePit(Creature *)
bool32_t GameThingWithPos::IsAWoodPileOutsideStoragePit(Creature* creature)
{
    return 0;
}

// win1.41 00401f00 mac 1055e800 GameThingWithPos::IsDoingSomethingInteresting(Creature *)
bool32_t GameThingWithPos::IsDoingSomethingInteresting(Creature* creature)
{
    return 0;
}

// win1.41 00401f50 mac 104a9cd0 GameThingWithPos::IsRock(Creature *)
// VTABLE-DRIFT BLOCKED (skipped): the body is `return IsRock();` (defer to the
// parameterless virtual IsRock()). That decompilation is correct, but our C++
// GameThingWithPos vtable places IsRock() at slot 0x1ec whereas the retail vtable
// has it at 0x1f0 (off by one slot). The emitted `call [eax+0x1ec]` is thus 1
// instruction-arg off (99.67%). Fixing requires reordering GameThingWithPos's
// virtual declarations to match the authoritative vtable - the same 27-virtual
// drift noted in the project docs - which risks regressing the many already-exact
// vtable-dependent functions. Left undefined here pending a verified vtable fix.

// win1.41 00401fa0 mac 1055df30 GameThingWithPos::IsCitadelPart(Creature *)
bool32_t GameThingWithPos::IsCitadelPart(Creature* creature)
{
    return 0;
}

// win1.41 00401fb0 mac 1055ddd0 GameThingWithPos::IsPlayingFootball(Creature *)
bool32_t GameThingWithPos::IsPlayingFootball(Creature* creature)
{
    return 0;
}

// win1.41 00401fc0 mac 10365210 GameThingWithPos::IsPlayingFootballAndMySideHasJustScored(Creature *)
bool32_t GameThingWithPos::IsPlayingFootballAndMySideHasJustScored(Creature* creature)
{
    return 0;
}

// win1.41 00401fd0 mac 1055f4e0 GameThingWithPos::IsPlayingFootballAndOtherSideHasJustScored(Creature *)
bool32_t GameThingWithPos::IsPlayingFootballAndOtherSideHasJustScored(Creature* creature)
{
    return 0;
}

// win1.41 00401fe0 mac 100db860 GameThingWithPos::IsAnimalBelongingToOtherPlayer(Creature *)
bool32_t GameThingWithPos::IsAnimalBelongingToOtherPlayer(Creature* creature)
{
    return 0;
}

// win1.41 00401ff0 mac 103c3e80 GameThingWithPos::IsOneOffSpellBelongingToOtherPlayer(Creature *)
bool32_t GameThingWithPos::IsOneOffSpellBelongingToOtherPlayer(Creature* creature)
{
    return 0;
}

// win1.41 00402000 mac 10167800 GameThingWithPos::IsOneOffSpellAggressive(Creature *)
bool32_t GameThingWithPos::IsOneOffSpellAggressive(Creature* creature)
{
    return 0;
}

// win1.41 00402010 mac 10565280 GameThingWithPos::IsOneOffSpellCompassionate(Creature *)
bool32_t GameThingWithPos::IsOneOffSpellCompassionate(Creature* creature)
{
    return 0;
}

// win1.41 00402020 mac 103c95f0 GameThingWithPos::IsOneOffSpellPlayful(Creature *)
bool32_t GameThingWithPos::IsOneOffSpellPlayful(Creature* creature)
{
    return 0;
}

// win1.41 00402030 mac 103c9590 GameThingWithPos::IsOneOffSpellToRestoreHealth(Creature *)
bool32_t GameThingWithPos::IsOneOffSpellToRestoreHealth(Creature* creature)
{
    return 0;
}

// win1.41 00402040 mac 1055f7f0 GameThingWithPos::CanBeStolenByCreature(Creature *)
bool32_t GameThingWithPos::CanBeStolenByCreature(Creature* creature)
{
    return 0;
}

// win1.41 00402050 mac 100e7500 GameThingWithPos::IsStealableSpell(Creature *)
bool32_t GameThingWithPos::IsStealableSpell(Creature* creature)
{
    return 0;
}

// win1.41 00402060 mac 10541f60 GameThingWithPos::IsStealableScaffold(Creature *)
bool32_t GameThingWithPos::IsStealableScaffold(Creature* creature)
{
    return 0;
}

// win1.41 00402070 mac 100dee30 GameThingWithPos::IsTownBelongingToOtherPlayer(Creature *)
bool32_t GameThingWithPos::IsTownBelongingToOtherPlayer(Creature* creature)
{
    return 0;
}

// win1.41 00402080 mac 10598e70 GameThingWithPos::IsTotemWithStealableSpell(Creature *)
bool32_t GameThingWithPos::IsTotemWithStealableSpell(Creature* creature)
{
    return 0;
}

// win1.41 00402090 mac 100bc240 GameThingWithPos::IsCreatureAvailableForJointActivity(Creature *)
bool32_t GameThingWithPos::IsCreatureAvailableForJointActivity(Creature* creature)
{
    return 0;
}

// win1.41 004020a0 mac 100bc380 GameThingWithPos::IsCreatureNotAvailableForJointActivity(Creature *)
bool32_t GameThingWithPos::IsCreatureNotAvailableForJointActivity(Creature* creature)
{
    return 0;
}

// win1.41 004020b0 mac 100b1cf0 GameThingWithPos::IsToyAwayFromHome(Creature *)
bool32_t GameThingWithPos::IsToyAwayFromHome(Creature* creature)
{
    return 0;
}

// win1.41 004020c0 mac 10378410 GameThingWithPos::IsToy(Creature *)
bool32_t GameThingWithPos::IsToy(Creature* creature)
{
    return 0;
}

// win1.41 004020d0 mac 1014d010 GameThingWithPos::IsToyBall(Creature *)
bool32_t GameThingWithPos::IsToyBall(Creature* creature)
{
    return 0;
}

// win1.41 004020e0 mac 10570d30 GameThingWithPos::IsToyDie(Creature *)
bool32_t GameThingWithPos::IsToyDie(Creature* creature)
{
    return 0;
}

// win1.41 004020f0 mac 1055e0d0 GameThingWithPos::IsToyCuddly(Creature *)
bool32_t GameThingWithPos::IsToyCuddly(Creature* creature)
{
    return 0;
}

// win1.41 00402110 mac 1007f100 GameThingWithPos::IsFence(void)
bool32_t GameThingWithPos::IsFence()
{
    return 0;
}

// win1.41 00402120 mac 1055f270 GameThingWithPos::IsSpellIcon(void)
bool32_t GameThingWithPos::IsSpellIcon()
{
    return 0;
}

// win1.41 00402130 mac 1054f090 GameThingWithPos::CanBeUsedForThrowingDamageByCreature(Creature *)
bool32_t GameThingWithPos::CanBeUsedForThrowingDamageByCreature(Creature* creature)
{
    return 0;
}

// win1.41 00402140 mac 1055f2b0 GameThingWithPos::IsCreatureWhoSeemsFriendly(Creature *)
bool32_t GameThingWithPos::IsCreatureWhoSeemsFriendly(Creature* creature)
{
    return 0;
}

// win1.41 00402150 mac 1019d0f0 GameThingWithPos::CanBeThrownInTheSeaPlayfully(Creature *)
bool32_t GameThingWithPos::CanBeThrownInTheSeaPlayfully(Creature* creature)
{
    return 0;
}

// win1.41 00402160 mac 10057640 GameThingWithPos::IsFlock( const(void))
bool32_t GameThingWithPos::IsFlock() const
{
    return 0;
}

// win1.41 00402170 mac 103dbe60 GameThingWithPos::IsDance( const(void))
bool32_t GameThingWithPos::IsDance() const
{
    return 0;
}

// win1.41 00402180 mac 100d0970 GameThingWithPos::IsReward( const(void))
bool32_t GameThingWithPos::IsReward() const
{
    return 0;
}

// win1.41 00402190 mac 10033ae0 GameThingWithPos::IsScriptContainer( const(void))
bool32_t GameThingWithPos::IsScriptContainer() const
{
    return 0;
}

// win1.41 004021a0 mac 1055f140 GameThingWithPos::IsWeather( const(void))
bool32_t GameThingWithPos::IsWeather() const
{
    return 0;
}

// win1.41 004021b0 mac 1015a0c0 GameThingWithPos::IsSpell( const(void))
bool32_t GameThingWithPos::IsSpell() const
{
    return 0;
}

// win1.41 004021c0 mac 10000790 GameThingWithPos::IsDeletedWhenReleasedFromScript(void)
bool32_t GameThingWithPos::IsDeletedWhenReleasedFromScript()
{
    return 0;
}

// win1.41 004021d0 mac 100332d0 GameThingWithPos::IsMobileWallHug( const(void))
bool32_t GameThingWithPos::IsMobileWallHug() const
{
    return 0;
}

// win1.41 004021e0 mac 10576f20 GameThingWithPos::IsActive( const(void))
bool32_t GameThingWithPos::IsActive() const
{
    return 0;
}

// win1.41 004021f0 mac 1012f070 GameThingWithPos::IsObjectTurningTooFastForCameraToFollowSmoothly(void)
bool32_t GameThingWithPos::IsObjectTurningTooFastForCameraToFollowSmoothly()
{
    return 0;
}

// win1.41 00402200 mac 100db7b0 GameThingWithPos::CalculateDesireForFood(void)
float GameThingWithPos::CalculateDesireForFood()
{
    return 0;
}

// win1.41 00402210 mac 10111950 GameThingWithPos::CalculateDesireForRest(void)
float GameThingWithPos::CalculateDesireForRest()
{
    return 0;
}

// win1.41 00402220 mac 100db800 GameThingWithPos::CalculatePeopleHidingIndicator(void)
float GameThingWithPos::CalculatePeopleHidingIndicator()
{
    return 0;
}

// win1.41 00402230 mac 10495720 GameThingWithPos::IsReadyForNewScriptAction(void)
bool32_t GameThingWithPos::IsReadyForNewScriptAction()
{
    return 0;
}

// win1.41 00402240 mac 10495760 GameThingWithPos::SetControlledByScript(int)
// Sets/clears the "controlled by script" flag, stored as bit 10 of the packed
// 16-bit flags word at +0x24. Reads the argument as a single bit and rewrites only
// that bit (mask 0xfbff clears bit 10), leaving the other flags untouched.
void GameThingWithPos::SetControlledByScript(int param_1)
{
    field_0x24 = (uint16_t)((field_0x24 & 0xfbff) | ((param_1 & 1) << 10));
}

// win1.41 00402270 mac 101a4ed0 GameThingWithPos::GetDeathReason(void)
DEATH_REASON GameThingWithPos::GetDeathReason()
{
    return DEATH_REASON_NONE;
}

// win1.41 00402280 mac 1004cf30 GameThingWithPos::IsInScript(void)
bool32_t GameThingWithPos::IsInScript()
{
    return (this->field_0x24 >> 9) & 1;
}

// win1.41 00402290 mac 1033c710 GameThingWithPos::IsMaleVillager(void)
bool32_t GameThingWithPos::IsMaleVillager()
{
    return 0;
}

// win1.41 004022a0 mac 1056d120 GameThingWithPos::IsFemaleVillager(void)
bool32_t GameThingWithPos::IsFemaleVillager()
{
    return 0;
}

// win1.41 004022b0 mac 1002a950 GameThingWithPos::IsAnimal(void)
bool32_t GameThingWithPos::IsAnimal()
{
    return 0;
}

// win1.41 004022c0 mac 10572f10 GameThingWithPos::IsAChild(void)
bool32_t GameThingWithPos::IsAChild()
{
    return 0;
}

// win1.41 004022d0 mac 100b6810 GameThingWithPos::IsFootball(void)
bool32_t GameThingWithPos::IsFootball()
{
    return 0;
}

// win1.41 004022e0 mac 10159fa0 GameThingWithPos::IsCitadel(void)
bool32_t GameThingWithPos::IsCitadel()
{
    return 0;
}

// win1.41 004022f0 mac 100fd0e0 GameThingWithPos::IsForest(void)
bool32_t GameThingWithPos::IsForest()
{
    return 0;
}

// win1.41 00402300 mac 105a2310 GameThingWithPos::IsMobileObject(void)
bool32_t GameThingWithPos::IsMobileObject()
{
    return 0;
}

// win1.41 00402310 mac 101c64c0 GameThingWithPos::IsMobileStatic(void)
bool32_t GameThingWithPos::IsMobileStatic()
{
    return 0;
}

// win1.41 00402320 mac 1055e8b0 GameThingWithPos::IsTree(Creature *)
bool32_t GameThingWithPos::IsTree(Creature* creature)
{
    return 0;
}

// win1.41 00402330 mac 100d56f0 GameThingWithPos::IsAnyKindOfTree(void)
bool32_t GameThingWithPos::IsAnyKindOfTree()
{
    return 0;
}

// win1.41 00402340 mac 1055e120 GameThingWithPos::IsDeadTree(void)
bool32_t GameThingWithPos::IsDeadTree()
{
    return 0;
}

// win1.41 00402350 mac 103d8a70 GameThingWithPos::IsLiving(void)
bool32_t GameThingWithPos::IsLiving() const
{
    return 0;
}

// win1.41 00402360 mac 1055e860 GameThingWithPos::IsCitadelPart(void)
bool32_t GameThingWithPos::IsCitadelPart()
{
    return 0;
}

// win1.41 00402370 mac 105600c0 GameThingWithPos::IsPileFood(void)
bool32_t GameThingWithPos::IsPileFood()
{
    return 0;
}

// win1.41 00402380 mac 1055f840 GameThingWithPos::IsFeature(void)
bool32_t GameThingWithPos::IsFeature()
{
    return 0;
}

// win1.41 00402390 mac 100bc020 GameThingWithPos::IsScriptMarker(void)
bool32_t GameThingWithPos::IsScriptMarker()
{
    return 0;
}

// win1.41 004023a0 mac 10000870 GameThingWithPos::IsScriptHighlight(void)
bool32_t GameThingWithPos::IsScriptHighlight()
{
    return 0;
}

// win1.41 004023b0 mac 1002c6a0 GameThingWithPos::IsWorkshop(void)
bool32_t GameThingWithPos::IsWorkshop()
{
    return 0;
}

// win1.41 004023c0 mac 10380730 GameThingWithPos::IsInfluenceRing(void)
bool32_t GameThingWithPos::IsInfluenceRing()
{
    return 0;
}

// win1.41 004023d0 mac 103809e0 GameThingWithPos::IsPuzzleGame(void)
bool32_t GameThingWithPos::IsPuzzleGame()
{
    return 0;
}

// win1.41 004023e0 mac 100a08c0 GameThingWithPos::IsScaffold(void)
bool32_t GameThingWithPos::IsScaffold()
{
    return 0;
}

// win1.41 004023f0 mac 1019d850 GameThingWithPos::IsSkeleton( const(void))
bool32_t GameThingWithPos::IsSkeleton() const
{
    return 0;
}

// win1.41 00402400 mac 100dcd70 GameThingWithPos::IsPoisoned(void)
bool32_t GameThingWithPos::IsPoisoned()
{
    __asm { xor al, al }
}

// win1.41 00402410 mac 10427300 GameThingWithPos::IsSpeedUp(void)
bool32_t GameThingWithPos::IsSpeedUp()
{
    __asm { xor al, al }
}

// win1.41 00402420 mac 10170360 GameThingWithPos::IsParticleContainer(void)
bool32_t GameThingWithPos::IsParticleContainer()
{
    return 0;
}

// win1.41 00402430 mac 103dbea0 GameThingWithPos::IsSacrificeAltar(void)
bool32_t GameThingWithPos::IsSacrificeAltar()
{
    return 0;
}

// win1.41 00402440 mac 10570ed0 GameThingWithPos::IsPot(void)
bool32_t GameThingWithPos::IsPot()
{
    return 0;
}

// win1.41 00402450 mac 104daf10 GameThingWithPos::IsComputerPlayer(void)
bool32_t GameThingWithPos::IsComputerPlayer()
{
    return 0;
}

// win1.41 00402460 mac 1035b870 GameThingWithPos::SetSkeleton(int)
void GameThingWithPos::SetSkeleton(int index)
{
}

// win1.41 00402470 mac 1007b170 GameThingWithPos::IsSpellSeed(void)
bool32_t GameThingWithPos::IsSpellSeed()
{
    return 0;
}

// win1.41 00402480 mac 10571e10 GameThingWithPos::IsSpellShield(void)
bool32_t GameThingWithPos::IsSpellShield()
{
    return 0;
}

// win1.41 00402490 mac 1054ecb0 GameThingWithPos::IsPileResource(void)
bool32_t GameThingWithPos::IsPileResource()
{
    return 0;
}

// win1.41 004024a0 mac 100bb900 GameThingWithPos::IsScriptTimer(void)
bool32_t GameThingWithPos::IsScriptTimer()
{
    return 0;
}

// win1.41 004024b0 mac 100b2190 GameThingWithPos::GetFacingDirection(void)
float GameThingWithPos::GetFacingDirection()
{
    return 0;
}

// win1.41 004024c0 mac 1055fa50 GameThingWithPos::SetAffectedByWind(int)
void GameThingWithPos::SetAffectedByWind(int param_1)
{
}

// win1.41 004024d0 mac 100188b0 GameThingWithPos::GetReactionPower(void)
float GameThingWithPos::GetReactionPower()
{
    return 0;
}

// win1.41 004024e0 mac 1015a1b0 GameThingWithPos::CleanUpBeforeReset(void)
void GameThingWithPos::CleanUpBeforeReset()
{
}

// win1.41 004024f0 mac 10055b70 Object::GetXAngle(void)
float Object::GetXAngle()
{
    return 0.0f;
}

// win1.41 00402500 mac 1004c930 Object::GetYAngle(void)
float Object::GetYAngle()
{
    return *(float*)((char*)this + 0x4c);
}

// win1.41 00402510 mac 10055b30 Object::GetZAngle(void)
float Object::GetZAngle()
{
    return 0.0f;
}

// win1.41 00402520 mac 10044cb0 Object::GetScale(void)
float Object::GetScale()
{
    return *(float*)((char*)this + 0x50);
}

// win1.41 00402540 mac 100def80 Object::UpdateFrom3DPosition(void)
void Object::UpdateFrom3DPosition()
{
}

// win1.41 00402550 mac 105890b0 Object::MoveAlongPath(void)
uint32_t Object::MoveAlongPath()
{
    return 1;
}

// win1.41 00402560 mac 1030b0c0 Object::IsReachable(void)
bool32_t Object::IsReachable()
{
    return this->IsAvailable();
}

// win1.41 00402580 mac 103dc890 Object::Get3DObjectForPSys(void)
Game3DObject* Object::Get3DObjectForPSys()
{
    return (struct Game3DObject*)*(void**)((char*)this + 0x40);
}

// win1.41 00402590 mac 1011c800 Object::GetSpotEffectPower(void)
float Object::GetSpotEffectPower()
{
    return 0.0f;
}

// win1.41 004025a0 mac 10097700 Object::GetHoldYRotate(void)
float Object::GetHoldYRotate()
{
    return 0.0f;
}

// win1.41 004025b0 mac 100a0df0 Object::HandShouldFeelWithMeshIntersect(void)
bool32_t Object::HandShouldFeelWithMeshIntersect()
{
    return 1;
}

// win1.41 004025c0 mac 10513b50 Object::SetSpecularColor(unsigned long)
void Object::SetSpecularColor(LH3DColor color)
{
}

// win1.41 004025e0 mac 10110490 Object::SetBeliefSprite(BeliefSprite *)
void Object::SetBeliefSprite(LH3DSprite* sprite)
{
}

// win1.41 004025f0 mac 1016bab0 Object::GetBeliefSprite(void)
LH3DSprite* Object::GetBeliefSprite()
{
    return 0;
}

// win1.41 00402600 mac 1004b110 Object::GetLife(void)
float Object::GetLife()
{
    return *(float*)((char*)this + 0x48);
}

// win1.41 00402640 mac 10368980 Object::ScaffoldMoved(Scaffold *)
void Object::ScaffoldMoved(Scaffold* scaffold)
{
}

// win1.41 00402650 mac 10368aa0 Object::ProcessBySpell(Spell *)
uint32_t Object::ProcessBySpell(Spell* spell)
{
    return 1;
}

// win1.41 00402670 mac 10109540 Object::IsG3DObjectDrawnInHand(void)
bool32_t Object::IsG3DObjectDrawnInHand()
{
    __asm { mov al, 1 }
}

// win1.41 00402680 mac 100a83e0 Object::GetDrawRegion(LHRegion *)
void Object::GetDrawRegion(LHRegion* param_1)
{
}

// win1.41 00402690 mac 103e4e10 Object::ProcessState(void)
uint32_t Object::ProcessState()
{
    return 0;
}

// win1.41 004026a0 mac 103e4940 Object::CanBePickedUp(void)
bool32_t Object::CanBePickedUp()
{
    return 0;
}

// win1.41 004026b0 mac 103e49a0 Object::GetVillagerHugRadius(void)
// VTABLE-DRIFT BLOCKED (skipped): body is `return GetRadius() * 1.05f + 0.0005f;`
// (collision radius padded 5% + epsilon). Correct decompilation, but our C++
// vtable places GetRadius() at slot 0x60 whereas retail has it at 0x64, so the
// emitted `call [eax+0x60]` is 1 slot off (plus the two float consts differ only
// by COMDAT-folded .rdata symbol). Same Object/GameThingWithPos vtable drift as
// IsRock; left undefined pending a verified vtable fix.

// win1.41 00402700 mac 10062630 Object::GetFoodType(void)
FOOD_TYPE Object::GetFoodType()
{
    return info->GetFoodType();
}

// win1.41 00402730 mac 1056f400 Object::IsSpellSeedReturnPoint( const(void))
bool32_t Object::IsSpellSeedReturnPoint() const
{
    return 0;
}

// win1.41 00402740 mac 104d62b0 Object::IsABeliever(void)
bool32_t Object::IsABeliever()
{
    return 0;
}

// win1.41 00402750 mac 1056ee10 Object::GetResourceType(void)
RESOURCE_TYPE Object::GetResourceType()
{
    return RESOURCE_TYPE_NONE; 
}

// win1.41 00402760 mac 1035b020 Object::GetDefaultResource(void)
int Object::GetDefaultResource()
{
    return 0;
}

// win1.41 00402770 mac 105a4d20 Object::SetPoisonedResource(RESOURCE_TYPE, int)
void Object::SetPoisonedResource(RESOURCE_TYPE type, int param_2)
{
}

// win1.41 00402780 mac 10552240 Object::SetPoisoned(int)
void Object::SetPoisoned(int param_1)
{
}

// win1.41 00402790 mac 10109690 Object::IsLockedInInteract(void)
bool32_t Object::IsLockedInInteract()
{
    return 0;
}

// win1.41 004027a0 mac 100a8120 Object::SetDying(void)
// Marks the object for deletion: forwards to the virtual ToBeDeleted(0) (vtable
// slot 0xc) to schedule destruction, then reports success (true). Compiles to
// push 0; call [eax+0xc]; mov eax,1; ret.
bool32_t Object::SetDying()
{
    ToBeDeleted(0);
    return true;
}

// win1.41 004027b0 mac 100a8170 Object::EndOnFire(void)
void Object::EndOnFire()
{
}

// win1.41 004027c0 mac 1016ed40 Object::GetDistanceFromObject(MapCoords const &)
// Convenience overload: distance from this object to a map position. Delegates to
// the base GameThingWithPos::GetDistanceFromObject implementation (a plain
// non-virtual forward; ret 0x4).
// NEAR-MISS (98.75%): instruction-identical, but the call target resolves to
// ?GetDistanceFromObject@GameThingWithPos@@UAEMABUMapCoords@@@Z instead of the
// retail ?...@UBEMPAUMapCoords@@@Z. The retail callee is a *const* member taking a
// MapCoords*, so the correct decl is `float GetDistanceFromObject(MapCoords*) const`
// in GameThingWithPos.h. That decl is correct (it matches the authoritative C
// prototype), but flipping it perturbs objdiff's vtable-slot->name resolution and
// shows IsFunctional/GetArrivePos as 1-instruction "regressions" (their bytes are
// unchanged). Left as-is to avoid that synced-header churn; only the callee's
// signature blocks 100% here.
float Object::GetDistanceFromObject(const MapCoords& target)
{
    return GameThingWithPos::GetDistanceFromObject(target);
}

// win1.41 004027d0 mac 1016eda0 Object::NetworkUnfriendlyStartLockedSelect(void)
bool32_t Object::NetworkUnfriendlyStartLockedSelect()
{
    return 1;
}

// win1.41 004027e0 mac 1056c2f0 Object::IsReadyForNetworkUnfriendlyLockedSelect(void)
bool32_t Object::IsReadyForNetworkUnfriendlyLockedSelect()
{
    return 1;
}

// win1.41 004027f0 mac 10577790 Object::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo *)
bool32_t Object::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo* param_1)
{
    return 1;
}

// win1.41 00402800 mac 1037fcb0 Object::GetReadyForNetworkUnfriendlyEndLockedSelect(void)
bool32_t Object::GetReadyForNetworkUnfriendlyEndLockedSelect()
{
    return 1;
}

// win1.41 00402810 mac 102fd0c0 Object::IsReadyForNetworkUnfriendlyEndLockedSelect(void)
bool32_t Object::IsReadyForNetworkUnfriendlyEndLockedSelect()
{
    return 1;
}

// win1.41 00402820 mac 103e2470 Object::NetworkUnfriendlyEndLockedSelect(void)
bool32_t Object::NetworkUnfriendlyEndLockedSelect()
{
    return 1;
}

// win1.41 00402830 mac 1041d9a0 Object::NetworkFriendlyEndLockedSelect(GInterfaceStatus *)
bool32_t Object::NetworkFriendlyEndLockedSelect(GInterfaceStatus* status)
{
    return 1;
}

// win1.41 00402840 mac 1017df80 Object::ValidAsInterfaceTarget(void)
bool32_t Object::ValidAsInterfaceTarget()
{
    return 1;
}

// win1.41 00402850 mac 1016daa0 Object::ValidAsInterfaceLeashTarget(void)
bool32_t Object::ValidAsInterfaceLeashTarget()
{
    return 1;
}

// win1.41 00402860 mac 103e0d10 Object::SelectOnlyAfterRecSystem(void)
bool32_t Object::SelectOnlyAfterRecSystem()
{
    return 0;
}

// win1.41 00402870 mac 105995f0 Object::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t Object::ValidForPlaceInHand(GInterfaceStatus* status)
{
    return 0;
}

// win1.41 00402880 mac 1040fc60 Object::ValidToRemoveFromHand(GInterfaceStatus *, MapCoords const &)
bool32_t Object::ValidToRemoveFromHand(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 0;
}

// win1.41 00402890 mac 100b16a0 Object::RemoveFromHand(GInterfaceStatus *, MapCoords const &)
uint32_t Object::RemoveFromHand(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 0x17;
}

// win1.41 004028a0 mac 101ca2e0 Object::InterfaceMustBeInInfluenceForInteraction(void)
bool32_t Object::InterfaceMustBeInInfluenceForInteraction()
{
    return 1;
}

// win1.41 004028b0 mac 101652d0 Object::ValidToApplyThisToObject(GInterfaceStatus *, Object *)
uint32_t Object::ValidToApplyThisToObject(GInterfaceStatus* status, Object* param_2)
{
    return 0;
}

// win1.41 004028c0 mac 10513670 Object::ApplyThisToObject(GInterfaceStatus *, Object *, GestureSystemPacketData *)
uint32_t Object::ApplyThisToObject(GInterfaceStatus* status, Object* param_2, GestureSystemPacketData* param_3)
{
    return 0;
}

// win1.41 004028d0 mac 10110bf0 Object::ValidToApplyThisToMapCoord(GInterfaceStatus *, MapCoords const &)
uint32_t Object::ValidToApplyThisToMapCoord(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 0;
}

// win1.41 004028e0 mac 10110b70 Object::ApplyThisToMapCoord(GInterfaceStatus *, MapCoords const &, GestureSystemPacketData *)
uint32_t Object::ApplyThisToMapCoord(GInterfaceStatus* status, const MapCoords& param_2, GestureSystemPacketData* param_3)
{
    return 0;
}

// win1.41 004028f0 mac 1055f210 Object::ValidForLockedApplyProcess(GInterfaceStatus *)
uint32_t Object::ValidForLockedApplyProcess(GInterfaceStatus* status)
{
    return 0;
}

// win1.41 00402900 mac 1016baf0 Object::ApplyUnlockProcess(GInterfaceStatus *)
uint32_t Object::ApplyUnlockProcess(GInterfaceStatus* status)
{
    return 1;
}

// win1.41 00402910 mac 10364e10 Object::IsInterfacePowerUpWhenInHand( const(void))
bool32_t Object::IsInterfacePowerUpWhenInHand() const
{
    return 0;
}

// win1.41 00402920 mac 103ad050 Object::ApplyOnlyAfterRecSystem(void)
uint32_t Object::ApplyOnlyAfterRecSystem()
{
    return 0;
}

// win1.41 00402930 mac 10101e60 Object::ApplyOnlyAfterReleased(void)
uint32_t Object::ApplyOnlyAfterReleased()
{
    return 0;
}

// win1.41 00402940 mac 100a0900 Object::InterfaceValidToGiveObject(GInterfaceStatus *, Object *)
uint32_t Object::InterfaceValidToGiveObject(GInterfaceStatus* status, Object* param_2)
{
    return 0;
}

// win1.41 00402950 mac 101c8d40 Object::InterfaceGiveObject(GInterfaceStatus *, Object *)
uint32_t Object::InterfaceGiveObject(GInterfaceStatus* status, Object* param_2)
{
    return 0x16;
}

// win1.41 00402960 mac 105890f0 Object::InterfaceValidToInteractAsMapCoordsObject(GInterfaceStatus *)
uint32_t Object::InterfaceValidToInteractAsMapCoordsObject(GInterfaceStatus* status)
{
    return 0;
}

// win1.41 00402970 mac 1016bbe0 Object::InterfaceInteractAsMapCoordsObject(GInterfaceStatus *)
uint32_t Object::InterfaceInteractAsMapCoordsObject(GInterfaceStatus* status)
{
    return 1;
}

// win1.41 00402980 mac 1016aaf0 Object::ValidToSelectFightThisToMapCoord(GInterfaceStatus *, MapCoords const &)
uint32_t Object::ValidToSelectFightThisToMapCoord(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 0;
}

// win1.41 00402990 mac 1056d5f0 Object::ValidToApplyFightThisToMapCoord(GInterfaceStatus *, MapCoords const &)
uint32_t Object::ValidToApplyFightThisToMapCoord(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 0;
}

// win1.41 004029a0 mac 103692a0 Object::SelectFightThisToMapCoord(GInterfaceStatus *, MapCoords const &)
uint32_t Object::SelectFightThisToMapCoord(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 1;
}

// win1.41 004029b0 mac 103690d0 Object::ApplyFightThisToMapCoord(GInterfaceStatus *, MapCoords const &)
uint32_t Object::ApplyFightThisToMapCoord(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 1;
}

// win1.41 004029c0 mac 10369240 Object::ValidToFightThisToObject(GInterfaceStatus *, MapCoords const &)
uint32_t Object::ValidToFightThisToObject(GInterfaceStatus* status, const MapCoords& param_2)
{
    return 0;
}

// win1.41 004029d0 mac 101cbb80 Object::FightThisToObject(GInterfaceStatus *, Object *)
uint32_t Object::FightThisToObject(GInterfaceStatus* status, Object* param_2)
{
    return 1;
}

// win1.41 004029e0 mac 100068d0 Object::IsEffectReceiver(EffectValues *)
bool32_t Object::IsEffectReceiver(EffectValues* param_1)
{
    return 1;
}

// win1.41 004029f0 mac 100219d0 Object::IsObject( const(void))
bool32_t Object::IsObject() const
{
    return 1;
}

// win1.41 00402a00 mac 100b06b0 Object::PhysicallyDestroysAbodes(void)
bool32_t Object::PhysicallyDestroysAbodes()
{
    __asm { xor al, al }
}

// win1.41 00402a10 mac 103db1f0 Object::GetAlwaysRemainsInPhysicsInternalSystem(void)
bool32_t Object::GetAlwaysRemainsInPhysicsInternalSystem()
{
    __asm { xor al, al }
}

// win1.41 00402a30 mac 100ba330 Object::CanBePoodOn(Creature *)
bool32_t Object::CanBePoodOn(Creature* creature)
{
    return 1;
}

// win1.41 00402a40 mac 100b9510 Object::CanBeAttackedByCreature(Creature *)
// An object can be attacked by a creature only if its type permits it
// (GObjectInfo::canCreatureAttackMe, +0xc4) AND the attacker is not the object
// itself (a creature can't attack itself). Both conditions must hold; otherwise
// false.
bool32_t Object::CanBeAttackedByCreature(Creature* creature)
{
    if (info->canCreatureAttackMe && creature != (Creature*)this)
    {
        return true;
    }
    return false;
}

// win1.41 00402a60 mac 100b95a0 Object::CanBePlayedWithByCreature(Creature *)
bool32_t Object::CanBePlayedWithByCreature(Creature* creature)
{
    return info->canCreaturePlayWithMe;
}

// win1.41 00402a70 mac 105a25d0 Object::CanBeImpressedByCreature(Creature *)
bool32_t Object::CanBeImpressedByCreature(Creature* creature)
{
    return 0;
}

// win1.41 00402a80 mac 1056cf30 Object::CanBeHelpedByCreature(Creature *)
bool32_t Object::CanBeHelpedByCreature(Creature* creature)
{
    return 1;
}

// win1.41 00402a90 mac 103e4d10 Object::CanBeExaminedByCreature(Creature *)
bool32_t Object::CanBeExaminedByCreature(Creature* creature)
{
    return 1;
}

// win1.41 00402aa0 mac 1054f410 Object::IsOnFire(Creature *)
extern "C" void jmp_addr_0x00637cc0(void);
__declspec(naked) bool32_t Object::IsOnFire(Creature* creature)
{
    __asm {
            call jmp_addr_0x00637cc0
            ret 4
        }
}

// win1.41 00402ab0 mac 103e2750 Object::GetTastiness(void)
uint32_t Object::GetTastiness()
{
    return 0;
}

// win1.41 00402ac0 mac 102fd110 Object::IsScary(void)
bool32_t Object::IsScary()
{
    return 0;
}

// win1.41 00402ad0 mac 102fd170 Object::GetObjectCollide(void)
uint32_t Object::GetObjectCollide()
{
    return 0;
}

// win1.41 00402ae0 mac 102fd140 Object::IsPushable(void)
bool32_t Object::IsPushable()
{
    return 0;
}

// win1.41 00402af0 mac 1016eb20 Object::GetCarriedTreeType(void)
uint32_t Object::GetCarriedTreeType()
{
    return 0;
}

// win1.41 00402b00 mac 105069f0 Object::GetFacingPitch(void)
float Object::GetFacingPitch()
{
    return 0.0f;
}

// win1.41 00402b10 mac 1016e7a0 Object::SetHeadPos(MapCoords *)
// Writes this object's current map position into the caller-supplied MapCoords.
// "Head" position for a plain object is just its origin coords (+0x14); animate
// subclasses (creatures/villagers) override to report their actual head joint.
// Member-wise copy of x/z/altitude into *param_1; ret 4.
void Object::SetHeadPos(MapCoords* param_1)
{
    *param_1 = coords;
}

// win1.41 00402b30 mac 1016e7f0 Object::IsAPotFromABuildingSite(void)
bool32_t Object::IsAPotFromABuildingSite()
{
    return 0;
}

// win1.41 00402b40 mac 1016dc30 Object::GetText(void)
const char* Object::GetText()
{
    return info->debugString;
}

// win1.41 00402b50 mac 10335f20 Object::StandAnimation(void)
uint32_t Object::StandAnimation()
{
    return 0xFFFFFFFF;
}

// win1.41 00402cb0 mac 10570ad0 Abode::DestroyedByBeam(void)
// Instantly destroys the abode when hit by a destructive beam (e.g. a lightning/
// meteor miracle): deals damage equal to the building's entire remaining life,
// dropping it to zero. Reads the current life (virtual Object::GetLife, slot 0x11c)
// and feeds it into ReduceLife (virtual, slot 0x5b8) with no attributing player.
// The correct EXPRESSIVE C is exactly:  ReduceLife(GetLife(), NULL);
// NEAR-MISS 92.86%: every instruction matches except one trailing `fstp st(0)`.
// Retail's ReduceLife returns a float (?ReduceLife@Object@@UAEMM... - mangled M),
// so the caller pops the x87 return with `fstp st(0)`; our headers declare
// ReduceLife as `void`, so the discard is never emitted. Reaching 100 needs the
// virtual's return type changed to float in Object.h (ripples to every overrider) -
// out of scope here (headers frozen). Kept commented (NEVER asm-wrap).
// void Abode::DestroyedByBeam() { ReduceLife(GetLife(), NULL); }

// win1.41 00402cd0 mac 1036ec90 Abode::GetInspectObjectPos(Villager *, MapCoords *)
// Where a villager should stand to "inspect" this abode. The abode has no special
// inspection spot, so it simply forwards to the base Object implementation
// (non-virtual base call), passing the villager and output MapCoords through. ret 8.
// NEAR-MISS (99.17%): instruction-identical; the only diff is the callee mangling -
// retail calls ?GetInspectObjectPos@Object@@UAE_N... (Object returns bool) but our
// Object.h declares it bool32_t (UAEI). The retail Object/Abode pair actually use
// DIFFERENT return types (Object _N=bool, Abode I=int); reconciling needs changing
// the virtual's return type in Object.h, which ripples to every overrider, so it is
// left as documented near-miss.
bool32_t Abode::GetInspectObjectPos(Villager* param_1, MapCoords* pos)
{
    return Object::GetInspectObjectPos(param_1, pos);
}

// win1.41 00402dc0 mac 103bf040 Abode::GetPhysicsConstantsType(void)
uint32_t Abode::GetPhysicsConstantsType()
{
    return 0;
}

// win1.41 00403130 mac 1033b920 Abode::Init(int, unsigned long, unsigned long)
// Stocks a freshly-created abode with its starting resources and, if the building
// is already finished, brings it online. The logic is fully decoded and the body
// below is correct EXPRESSIVE C:
//     AddResource(RESOURCE_TYPE_FOOD, food, NULL, false, NULL, 0);  // slot 0x9c
//     AddResource(RESOURCE_TYPE_WOOD, wood, NULL, false, NULL, 0);  // slot 0x9c
//     if (IsBuilt()) MakeFunctional();                              // 0x890 / 0x914
// (param_1 is unused by retail.) NEAR-MISS 99.94%, blocked ONLY by a vtable-slot
// mismatch: retail dispatches AddResource through the inherited Object slot +0x9c,
// but our Abode vftable layout places the AddResource override at +0x92c, so both
// vcalls emit `call [reg+0x92c]` instead of `[reg+0x9c]`. Fixing this requires
// re-ordering the vtable headers (AddResource must occupy the inherited slot, not be
// appended) - out of scope for this pass (vtable headers are frozen), so the body is
// kept commented rather than committed at 99.94%. NEVER asm-wrap.

// win1.41 00403ee0 mac 1036edb0 Abode::InsertMapObject(void)
void Abode::InsertMapObject()
{
    MultiMapFixed::InsertMapObject();
}

// win1.41 00403f00 mac 100e33a0 Abode::DeleteDependancys(void)
void Abode::DeleteDependancys()
{
    RemoveAllVillagersFromAbode();
}

// win1.41 00404220 mac 1033b0e0 Abode::RemoveDeletedVillagerFromAbode(Villager *)
// Bookkeeping run when a villager that lives here is being destroyed: detach it from
// this abode's occupancy state. Logic (fully decoded, verified against the asm):
//   1. If this villager was the registered "head of household" for its sex
//      (male_female_villagers[sex], sex = villager->info->sex at GVillagerInfo+0x1f8),
//      clear BOTH head-slots (a household is a male+female pair).
//   2. Population counters split by Villager::IsChild (vtable slot 0xaf8):
//        child  -> decrement child count (field_0xb7), clamped at 0
//        adult  -> decrement adult_count (clamped); if the male tally (field_0xb5) is
//                  non-zero drop it by 1 when male (Villager::IsMaleVillager, slot 0x44c).
//   3. Unlink from the abode's singly-linked occupant list (villagers head 0xa0 /
//      count 0xa4, linked through Villager::next at +0xe4); dec count; null the link.
//   4. villager->SetAbode(NULL); then if GetTown() (slot 0x48): Town::RemoveVillager +
//      TownStats::VillagerMoveOutOfAbode (town->stats at +0x610).
//
// NONMATCHING near-miss: 82.30% (report fuzzy). Semantically identical to retail; the
// body below is the faithful reconstruction (CFG + every field offset verified against
// the asm). Two real fixes were found via a /FAcs compiler-oracle investigation:
//   (1) Villager::SetAbode takes Abode*, NOT Town* (our header was wrong -> the call
//       mangled to ?...PAVTown vs retail ?...PAVAbode). Fixed in Villager.h.
//   (2) CFG: the child branch tests field_0xb7 != 0 (je), not > 0 (jbe); and count-- is
//       done ONLY when the villager is found mid-list, NOT when it is the list head
//       (retail jmps past the dec). Fixing these raised the body 79.74 -> 82.30%.
//
// The ENTIRE residual is now one MSVC6 REGISTER-ALLOCATION decision: retail materialises
// the constant 0 once (`push ebx; xor ebx,ebx`) and reuses bl/ebx for the NULL stores
// (`mov [..],ebx`), the byte tests (`cmp al,bl`) and `push ebx` (SetAbode). Our /O2 build
// rematerialises 0 as immediates instead. PROVEN irreducible at the source level by the
// oracle (tools, since removed): under the correct /O2 /G6 flags NO zero spelling tips it
// (literal, int/Villager* local, `register`, casts, saturated uses - 0/7 produce ebx),
// and ZERO of the 448 byte-exact Abode functions keep 0 in ebx under /O2. /Os (favor
// size) DOES emit the ebx form but (a) regresses Abode 448->351 globally and (b) scores
// 78.66% here (worse - it perturbs the rest), so it is not the original's flag. Likely the
// retail function carried a per-function size hint we cannot recover, or its true TU was
// size-optimised. Left LIVE as a tracked near-miss (dtk records the %); it is correct C.
void Abode::RemoveDeletedVillagerFromAbode(Villager* villager)
{
    int sex = ((GVillagerInfo*)villager->info)->sex;
    if (male_female_villagers[sex] == villager) {
        male_female_villagers[sex == 0] = NULL;          // clear whichever of the male/female slots this villager filled
        male_female_villagers[sex] = NULL;
    }
    if (villager->IsChild() != 1) {                      // adult leaving: drop the adult census
        if (adult_count > 0) adult_count--;
        if (field_0xb5 > 0) field_0xb5 -= (villager->IsMaleVillager() != 0) ? 1 : 0;
    } else if (field_0xb7 != 0) {                         // child leaving: drop the child census (tested !=0, not >0)
        field_0xb7--;
    }
    Villager* cur = villagers.head;                       // unlink from the abode's occupant list
    if (cur == villager) {
        villagers.head = villager->next;                 // removing the head does NOT decrement count (matches retail)
    } else {
        while (cur != NULL) {
            if (cur->next == villager) {                 // found: splice it out and drop the count
                cur->next = villager->next;
                villagers.count--;
                break;
            }
            cur = cur->next;
        }
    }
    villager->next = NULL;
    villager->SetAbode(NULL);                             // villager no longer belongs to this abode
    if (GetTown()) {                                      // and is removed from the owning town's rolls/stats
        GetTown()->RemoveVillager(villager);
        GetTown()->stats.VillagerMoveOutOfAbode(villager);
    }
}

// win1.41 00404660 mac 1032c3e0 Abode::GetRoomLeftForAdults(void)
int Abode::GetRoomLeftForAdults()
{
    return ((GAbodeInfo*)info)->maxVillagersInAbode - adult_count;
}

// win1.41 00404680 mac 103e40f0 Abode::GetRoomLeftForChildren(void)
int Abode::GetRoomLeftForChildren()
{
    return ((GAbodeInfo*)info)->maxChildrenInAbode - field_0xb7;
}

// win1.41 004046a0 mac inlined Abode::FUN_004046a0(int)
void Abode::FUN_004046a0(int param_1)
{
}

// win1.41 004046c0 mac 105b93c0 Abode::IsTooCrowded(void)
// True if the abode's adult occupancy has reached its "too crowded" fraction. An
// abode with no adult capacity (GAbodeInfo::maxVillagersInAbode, +0x174, == 0) is
// always reported crowded. Otherwise the adult fill ratio (adult_count / capacity,
// computed in x87 from the integer operands) is compared against the building's
// configured threshold (GAbodeInfo::percentTooCrowded, +0x1a0): crowded iff the
// ratio is at least the threshold. Used by the population/migration logic to decide
// whether villagers should move out to a roomier home. EXPRESSIVE C - no asm-wrap.
bool32_t Abode::IsTooCrowded()
{
    uint32_t capacity = ((GAbodeInfo*)info)->maxVillagersInAbode;
    if (capacity == 0)
    {
        return true;
    }
    return (float)adult_count / capacity >= ((GAbodeInfo*)info)->percentTooCrowded;
}

// win1.41 004047b0 mac 100df280 Abode::Repaired(void)
// Called when a damaged abode finishes being repaired. Runs the generic base handler
// (MultiMapFixed::Repaired, result discarded), and if the abode belongs to a town
// (virtual GetTown, slot 0x48) re-runs MakeFunctional (virtual, slot 0x914) so the
// repaired building resumes producing/serving. Always returns true. EXPRESSIVE C.
bool32_t Abode::Repaired()
{
    MultiMapFixed::Repaired();
    if (GetTown())
    {
        MakeFunctional();
    }
    return true;
}

// win1.41 00404aa0 mac 100ac700 Abode::GetMesh(void) const
// An abode has no per-instance mesh; it forwards to its static class info
// (GObjectInfo::GetMesh, no-arg overload, info-vtable slot 0x2c). The correct
// EXPRESSIVE C is exactly:  return info->GetMesh();  which compiles to the right
// 3-instruction tail-jmp (mov ecx,[ecx+0x28]; mov eax,[ecx]; jmp [eax+0x2c]) - those
// three instructions match the retail target byte-for-byte. NOT counted as exact,
// however: the retail GetMesh symbol is COMDAT-FOLDED with an unrelated 112-byte
// body (8 nops then a separate function), so the report measures our 3-instruction
// .o split against the folded 112-byte region and reads ~7%. This is a linker
// folding/sizing artifact, not a logic error; left commented (NEVER asm-wrap).
// int Abode::GetMesh() const { return info->GetMesh(); }

// win1.41 00404cc0 mac 1019cca0 Abode::ChildToAdult(Villager *)
// A child living here has grown up: move it from the child tally to the adult tally.
//   - decrement the child count (field_0xb7), clamped at 0
//   - increment adult_count
//   - if the new adult is male (Villager::IsMaleVillager, vtable slot 0x44c) bump the
//     male tally (field_0xb5)
//   - if owned by a town (virtual GetTown, slot 0x48) mirror the change at town level
//     (Town::ChildToAdult). EXPRESSIVE C - no asm-wrap.
void Abode::ChildToAdult(Villager* villager)
{
    if (field_0xb7 != 0)
    {
        field_0xb7--;
    }
    adult_count++;
    field_0xb5 += (villager->IsMaleVillager() != 0) ? 1 : 0;
    if (GetTown())
    {
        GetTown()->ChildToAdult(villager);
    }
}

// win1.41 00404d30 mac 1006d300 Abode::GetResource(RESOURCE_TYPE)
uint32_t Abode::GetResource(RESOURCE_TYPE type)
{
    return this->resources[type];
}

// win1.41 00404d40 mac 1006d340 Abode::JustAddResource(RESOURCE_TYPE, unsigned long, bool)
// Low-level resource deposit: adds param_2 units of the given resource straight
// into the abode's per-type store (resources[], +0xbc) with no capacity check or
// side effects (the bool flag is ignored at this level). Returns the amount added
// (param_2 is left in eax after the in-place add). Compiles to a single
// add [ecx+type*4+0xbc], amount.
uint32_t Abode::JustAddResource(RESOURCE_TYPE param_1, uint32_t param_2, bool param_3)
{
    resources[param_1] += param_2;
    return param_2;
}

// win1.41 00404d60 mac 1006d3a0 Abode::JustRemoveResource(RESOURCE_TYPE, unsigned long, bool *)
// Low-level resource withdrawal: removes up to param_2 units of the given resource
// from the abode's per-type store (resources[], +0xbc), clamped so the store never
// goes negative. Returns the amount actually removed (min(requested, available)).
// The bool* out-param is unused at this level. Matches the asm's clamp-then-
// subtract: load current; if current < requested, take current; store current-amt.
uint32_t Abode::JustRemoveResource(RESOURCE_TYPE param_1, uint32_t param_2, bool* param_3)
{
    uint32_t available = resources[param_1];
    if (available < param_2)
    {
        param_2 = available;
    }
    resources[param_1] = available - param_2;
    return param_2;
}

// win1.41 00405050 mac 100a3330 Abode::ConvertToPlanned(void)
PlannedMultiMapFixed* Abode::ConvertToPlanned()
{
    PlannedAbode* planned = PlannedAbode::Create(this);
    if (planned != NULL)
    {
        ToBeDeleted(0);
    }
    return planned;
}

// win1.41 004050c0 mac 1017d1b0 PlannedMultiMapFixed::GetScale(void)
float PlannedMultiMapFixed::GetScale()
{
    return scale;
}

// win1.41 004050e0 mac 10352440 PlannedAbode::GetTown(void)
Town* PlannedAbode::GetTown()
{
    return this->town;
}

// win1.41 004050f0 mac 10531c20 PlannedAbode::GetSaveType(void)
uint32_t PlannedAbode::GetSaveType()
{
    return 0x61;
}

// win1.41 00405100 mac 10179a00 PlannedAbode::GetDebugText(void)
// Debug/diagnostic label for the "planned" (not-yet-built) abode placeholder,
// shown by the engine's object inspector. Returns a pointer to the static string.
char* PlannedAbode::GetDebugText()
{
    return "Planned Abode";
}

// win1.41 00405110 mac 1017d1f0 PlannedAbode::_dt(unsigned int)
PlannedAbode::~PlannedAbode()
{
}

// win1.41 00405130 mac 10169a70 GameThing::GetDrawImportance(void)
float GameThing::GetDrawImportance()
{
    return 0.0f;
}

// win1.41 00405140 mac 104e9450 GameThing::GetRadius(void)
float GameThing::GetRadius()
{
    return 0.0f;
}

// win1.41 00405150 mac 1034f3d0 GameThing::Get2DRadius(void)
float GameThing::Get2DRadius()
{
    return 0.0f;
}

// win1.41 00405160 mac 103c36e0 GameThing::IsFootpathLink(void)
bool32_t GameThing::IsFootpathLink()
{
    return 0;
}

// win1.41 00405170 mac 1056c160 GameThing::GetFootpathLink(void)
GFootpathLink* GameThing::GetFootpathLink()
{
    return 0;
}

// win1.41 00405180 mac 104788b0 GameThing::GetNearestPathTo(MapCoords const &, float, int)
uint32_t GameThing::GetNearestPathTo(const MapCoords& param_1, float param_2, int param_3)
{
    return 0;
}

// win1.41 00405190 mac 103dffc0 GameThing::AddFootpath(GFootpath *)
uint32_t GameThing::AddFootpath(GFootpath* param_1)
{
    return 0;
}

// win1.41 004051a0 mac 103dff70 GameThing::RemoveFootpath(GFootpath *)
uint32_t GameThing::RemoveFootpath(GFootpath* param_1)
{
    return 0;
}

// win1.41 004051b0 mac 1056c950 GameThing::GetResource(RESOURCE_TYPE)
uint32_t GameThing::GetResource(RESOURCE_TYPE type)
{
    return 0;
}

// win1.41 004051c0 mac 1056c9a0 GameThing::AddResource(RESOURCE_TYPE, unsigned long, GInterfaceStatus *, bool, MapCoords const &, int)
uint32_t GameThing::AddResource(RESOURCE_TYPE type, uint32_t param_2, GInterfaceStatus* param_3, bool param_4, const MapCoords& coords, int param_6)
{
    return 0;
}

// win1.41 004051d0 mac 104f8b20 GameThing::RemoveResource(RESOURCE_TYPE, unsigned long, GInterfaceStatus *, bool *)
uint32_t GameThing::RemoveResource(RESOURCE_TYPE type, uint32_t param_2, GInterfaceStatus* param_3, bool* param_4)
{
    return 0;
}

// win1.41 004051e0 mac 1017ebc0 GameThing::CastAbode(void)
Abode* GameThing::CastAbode()
{
    return 0;
}

// win1.41 004051f0 mac 10199740 GameThing::CastMultiMapFixed(void)
MultiMapFixed* GameThing::CastMultiMapFixed()
{
    return 0;
}

// win1.41 00405200 mac 100ac9a0 GameThing::GetNumberOfInstanceForGlobalList(void)
uint16_t GameThing::GetNumberOfInstanceForGlobalList()
{
    return 1;
}

// win1.41 00405210 mac 1019aa00 GameThing::GetTownArtifactValue(void)
float GameThing::GetTownArtifactValue()
{
    return 0.0f;
}

// win1.41 00405220 mac 10199de0 GameThing::CanBecomeArtifact(void)
bool GameThing::CanBecomeArtifact()
{
    return false;
}

// win1.41 00405230 mac 10199e20 GameThing::DrawInHand(GInterfaceStatus *)
void GameThing::DrawInHand(GInterfaceStatus* param_1)
{
}

// win1.41 00405240 mac 10067860 GameThing::IsFunctional(void)
bool32_t GameThing::IsFunctional()
{
    return IsAvailable();
}

// win1.41 00405280 mac 103e5940 GameThingWithPos::GetCreatureBeliefType(void)
uint32_t GameThingWithPos::GetCreatureBeliefType()
{
    return 0x15;
}

// win1.41 00405290 mac 103efe40 GameThingWithPos::GetOrigin(void)
uint32_t GameThingWithPos::GetOrigin()
{
    return 0;
}

// win1.41 004052a0 mac 103e1210 GameThingWithPos::GetLife(void)
float GameThingWithPos::GetLife()
{
    return 0.0f;
}

// win1.41 004052b0 mac 103efb80 GameThingWithPos::IsMoving( const(void))
bool32_t GameThingWithPos::IsMoving() const
{
    return false;
}

// win1.41 004052c0 mac 103f07b0 GameThingWithPos::IsObjectInMap(void)
bool32_t GameThingWithPos::IsObjectInMap()
{
    return (bool32_t)(*(uint8_t*)((char*)this + 0x24) & 1);
}

// win1.41 004052d0 mac 103ee440 GameThingWithPos::IsDrowning(void)
bool32_t GameThingWithPos::IsDrowning()
{
    return 0;
}

// win1.41 004052e0 mac 10405890 GameThingWithPos::IsCastShadowAtNight(void)
bool32_t GameThingWithPos::IsCastShadowAtNight()
{
    return false;
}

// win1.41 004052f0 mac 1055f350 GameThingWithPos::CleanupWhenDeleted(int)
void GameThingWithPos::CleanupWhenDeleted(int param_1)
{
}

// win1.41 00405300 mac 100026f0 GameThingWithPos::GetImpressiveValue(Living *, Reaction *)
float GameThingWithPos::GetImpressiveValue(Living* param_1, Reaction* param_2)
{
    return 0.0f;
}

// win1.41 00405310 mac 1009aa60 GameThingWithPos::IsAbode(void)
bool32_t GameThingWithPos::IsAbode()
{
    return false;
}

// win1.41 00405320 mac 105e8120 GameThingWithPos::IsBuildingMaterial(void)
bool32_t GameThingWithPos::IsBuildingMaterial()
{
    return false;
}

// win1.41 00405330 mac 104a6920 GameThingWithPos::IsSuitableForCreatureAction(void)
bool32_t GameThingWithPos::IsSuitableForCreatureAction()
{
    return false;
}

// win1.41 00405340 mac 1016b460 GameThingWithPos::CanBeEatenByCreature(Creature *)
bool32_t GameThingWithPos::CanBeEatenByCreature(Creature* creature)
{
    return false;
}

// win1.41 00405350 mac 103820f0 GameThingWithPos::CanBeAttackedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeAttackedByCreature(Creature* creature)
{
    return false;
}

// win1.41 00405360 mac 101744e0 GameThingWithPos::CanBeFrighteningToCreature(Creature *)
bool32_t GameThingWithPos::CanBeFrighteningToCreature(Creature* creature)
{
    return false;
}

// win1.41 00405370 mac 10550480 GameThingWithPos::CanBeHelpedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeHelpedByCreature(Creature* creature)
{
    return false;
}

// win1.41 00405380 mac 1055da80 GameThingWithPos::CanBePlayedWithByCreature(Creature *)
bool32_t GameThingWithPos::CanBePlayedWithByCreature(Creature* creature)
{
    return false;
}

// win1.41 00405390 mac 1054f030 GameThingWithPos::CanBeImpressedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeImpressedByCreature(Creature* creature)
{
    return false;
}

// win1.41 004053a0 mac 10148420 GameThingWithPos::CanBeInspectedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeInspectedByCreature(Creature* creature)
{
    return false;
}

// win1.41 004053b0 mac 103d5780 GameThingWithPos::CanBePoodUponByCreature(Creature *)
bool32_t GameThingWithPos::CanBePoodUponByCreature(Creature* creature)
{
    return false;
}

// win1.41 004053c0 mac 102fdd30 GameThingWithPos::CanBeSleptNextToByCreature(Creature *)
bool32_t GameThingWithPos::CanBeSleptNextToByCreature(Creature* creature)
{
    return false;
}

// win1.41 004053d0 mac 102fde30 GameThingWithPos::CanBePickedUpByCreature(Creature *)
bool32_t GameThingWithPos::CanBePickedUpByCreature(Creature* creature)
{
    return false;
}

// win1.41 004053e0 mac 100cb730 GameThingWithPos::CanBeStrokedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeStrokedByCreature(Creature* creature)
{
    return false;
}

// win1.41 004053f0 mac 105609f0 GameThingWithPos::CanBeSetOnFire(Creature *)
bool32_t GameThingWithPos::CanBeSetOnFire(Creature* creature)
{
    return false;
}

// win1.41 00405400 mac 1043fa70 GameThingWithPos::CanBeStompedOnByCreature(Creature *)
bool32_t GameThingWithPos::CanBeStompedOnByCreature(Creature* creature)
{
    return false;
}

// win1.41 00405410 mac 10147ea0 GameThingWithPos::CanBeThrownByCreature(Creature *)
bool32_t GameThingWithPos::CanBeThrownByCreature(Creature* creature)
{
    return false;
}

// win1.41 00405420 mac 101660d0 GameThingWithPos::CanBePutInAStoragePit(Creature *)
bool32_t GameThingWithPos::CanBePutInAStoragePit(Creature* creature)
{
    return false;
}

// win1.41 00405430 mac 104fb730 GameThingWithPos::CanBeDestroyedByStoning(Creature *)
bool32_t GameThingWithPos::CanBeDestroyedByStoning(Creature* creature)
{
    return false;
}

// win1.41 00405440 mac 10160390 GameThingWithPos::CanBeExaminedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeExaminedByCreature(Creature* creature)
{
    return false;
}

// win1.41 00405450 mac 103e0d90 GameThingWithPos::IsBeingBuilt(Creature *)
bool32_t GameThingWithPos::IsBeingBuilt(Creature* creature)
{
    return false;
}

// win1.41 00405460 mac 104272b0 GameThingWithPos::NeedsRepair(Creature *)
bool32_t GameThingWithPos::NeedsRepair(Creature* creature)
{
    return false;
}

// win1.41 00405470 mac 1036f0b0 GameThingWithPos::IsOnFire(Creature *)
bool32_t GameThingWithPos::IsOnFire(Creature* creature)
{
    return false;
}

// win1.41 00405480 mac 100d56a0 GameThingWithPos::CanBePutInFoodPile(Creature *)
bool32_t GameThingWithPos::CanBePutInFoodPile(Creature* creature)
{
    return false;
}

// win1.41 00405490 mac 105644c0 GameThingWithPos::CanBePutInWoodPile(Creature *)
bool32_t GameThingWithPos::CanBePutInWoodPile(Creature* creature)
{
    return false;
}

// win1.41 004054a0 mac 103e1250 GameThingWithPos::CanBeBroughtBackToCitadel(Creature *)
bool32_t GameThingWithPos::CanBeBroughtBackToCitadel(Creature* creature)
{
    return false;
}

// win1.41 004054b0 mac 10560070 GameThingWithPos::CanBePoodOn(Creature *)
bool32_t GameThingWithPos::CanBePoodOn(Creature* creature)
{
    return false;
}

// win1.41 004054c0 mac 1048f310 GameThingWithPos::IsBuildingWhichIsBeingBuilt(Creature *)
bool32_t GameThingWithPos::IsBuildingWhichIsBeingBuilt(Creature* creature)
{
    return false;
}

// win1.41 004054d0 mac 100e74b0 GameThingWithPos::CanBeKickedByCreature(Creature *)
bool32_t GameThingWithPos::CanBeKickedByCreature(Creature* creature)
{
    return false;
}

// win1.41 004054e0 mac 10554000 GameThingWithPos::GetCreatureMimicType(void)
uint32_t GameThingWithPos::GetCreatureMimicType()
{
    return 0xa;
}

// win1.41 004054f0 mac 100e5cc0 GameThingWithPos::GetHowMuchCreatureWantsToLookAtMe(void)
float GameThingWithPos::GetHowMuchCreatureWantsToLookAtMe()
{
    return 0.0f;
}

// win1.41 00405500 mac 100b1980 GameThingWithPos::GetHeight(void)
float GameThingWithPos::GetHeight()
{
    return 0.0f;
}

// win1.41 00405510 mac 10495700 GameThingWithPos::SetInScript(int)
// Sets/clears the "in script" flag, stored as bit 9 of the packed 16-bit flags
// word at +0x24. Same single-bit rewrite pattern as SetControlledByScript but for
// bit 9 (mask 0xfdff clears bit 9).
void GameThingWithPos::SetInScript(int param_1)
{
    field_0x24 = (uint16_t)((field_0x24 & 0xfdff) | ((param_1 & 1) << 9));
}

// win1.41 00405540 mac 103c1df0 GameThingWithPos::IsHouse(void)
bool32_t GameThingWithPos::IsHouse()
{
    return false;
}

// win1.41 00405550 mac 103c2360 GameThingWithPos::IsObject( const(void))
bool32_t GameThingWithPos::IsObject() const
{
    return false;
}

// win1.41 00405560 mac 102ffbb0 GameThingWithPos::GetQueryFirstEnumText(void)
HELP_TEXT GameThingWithPos::GetQueryFirstEnumText()
{
    return HELP_TEXT_NONE;
}

// win1.41 00405570 mac 1055f0f0 GameThingWithPos::GetQueryLastEnumText(void)
HELP_TEXT GameThingWithPos::GetQueryLastEnumText()
{
    return HELP_TEXT_NONE;
}

// win1.41 004055a0 mac 103e5560 PlannedAbode::Init(Town *)
// Attaches this planned (not-yet-built) abode to its owning town: records the town
// pointer (+0x48) and, if non-null, registers the placeholder with the town's
// planned-structure list via Town::AddPlanned. ret 4.
void PlannedAbode::Init(Town* town)
{
    this->town = town;
    if (town)
    {
        town->AddPlanned(this);
    }
}

// win1.41 004056b0 mac 103e5400 PlannedAbode::ToBeDeleted(int)
// Tears down the planned-abode placeholder: if it is registered with a town
// (+0x48), unregister it via Town::RemovePlanned, then chain to the base
// GameThingWithPos::ToBeDeleted to finish scheduling deletion. ret 4.
void PlannedAbode::ToBeDeleted(int param_1)
{
    if (town)
    {
        town->RemovePlanned(this);
    }
    GameThingWithPos::ToBeDeleted(param_1);
}

// win1.41 00405900 mac 100cb6b0 Windmill::GetSaveType(void)
uint32_t Windmill::GetSaveType()
{
    return 0xf8;
}

// win1.41 00405910 mac 100cb6f0 Windmill::GetDebugText(void)
char* Windmill::GetDebugText()
{
    return (char*)0x009c8048;  // ??_C@_09ABCDEFGH@Windmill?$AA@
}

// win1.41 00405920 mac 100cb620 Windmill::_dt(void)
Windmill::~Windmill()
{
}

// win1.41 00405a60 mac inlined GAbodeInfo::GetDescription(void)
const char* GAbodeInfo::GetDescription()
{
    return this->description.string;
}

// win1.41 00405d80 mac inlined Abode::FUN_00405d80(void)
int Abode::FUN_00405d80()
{
    return 1;
}

// win1.41 00405f50 mac 1036ed40 Abode::GetTribe(void)
// Returns the tribe this abode belongs to, by way of its owning town. Looks up the
// town via the virtual GetTown() (vtable slot 0x48); if there is no town, reports
// no tribe (NULL). NOTE: the retail code re-invokes GetTown() for the value rather
// than caching it, so the null-check and the use are written as two separate
// GetTown() calls to reproduce the two-vcall sequence byte-for-byte.
GTribeInfo* Abode::GetTribe()
{
    if (GetTown())
    {
        return GetTown()->GetTribe();
    }
    return NULL;
}

// win1.41 00405f70 mac 1036ed90 Abode::GetPlayer(void)
// Returns the player that owns this abode. If the abode belongs to a town
// (virtual GetTown(), slot 0x48), the owning player is the town's player
// (Town::GetPlayer, virtual slot 0x1c); otherwise fall back to the base
// GameThing::GetPlayer (direct call). As with GetTribe, the retail code calls
// GetTown() twice (null-check then use), reproduced here verbatim.
// NEAR-MISS (99.72%): the three vtable calls (0x48/0x48/0x1c) match exactly; only
// the fallback resolves to ?GetPlayer@GameThing@@QAE... (a *non-virtual* Q symbol)
// in retail, whereas our header declares GameThing::GetPlayer virtual (UAE). Needs a
// separate non-virtual GameThing::GetPlayer decl; left as documented near-miss.
GPlayer* Abode::GetPlayer()
{
    if (GetTown())
    {
        return GetTown()->GetPlayer();
    }
    return GameThing::GetPlayer();
}

// win1.41 00405fb0 mac 1009fda0 Abode::LeaveHome(void)
void Abode::LeaveHome()
{
    this->field_0xb6--;
}

// win1.41 004061c0 mac 1014d0e0 Abode::IsWonder(void)
// True iff this abode is a Tribe Wonder. Reads the building's static class
// (GAbodeInfo::abodeType, +0x120) and tests it against ABODE_TYPE_WONDER (0x100).
// Wonders are the special per-tribe structures (e.g. Norse fishing Wonder) that
// grant the tribal-power bonuses. EXPRESSIVE C - no asm-wrap.
bool32_t Abode::IsWonder()
{
    return ((GAbodeInfo*)info)->abodeType == ABODE_TYPE_WONDER;
}

// win1.41 00406200 mac 1005ff20 Abode::IsFunctional(void)
bool32_t Abode::IsFunctional()
{
    if (MultiMapFixed::IsFunctional() == 1)
    {
        if (IsBuilt())
        {
            return true;
        }
    }
    return false;
}

// win1.41 00406230 mac 1014cfd0 Abode::ChecksVerticesVObjects(void)
bool32_t Abode::ChecksVerticesVObjects()
{
    __asm { xor al, al }
}

// win1.41 00406800 mac 1010ab50 Abode::CanBecomeAPhysicsObject(void)
bool32_t Abode::CanBecomeAPhysicsObject()
{
    return false;
}

// win1.41 00406810 mac 1001b380 Abode::GetScriptObjectType(void)
uint32_t Abode::GetScriptObjectType()
{
    return 2;
}

// win1.41 00406820 mac 1049b920 Abode::InterfaceValidToTap(GInterfaceStatus *)
uint32_t Abode::InterfaceValidToTap(GInterfaceStatus* status)
{
    return 1;
}

// win1.41 00406970 mac 1004c590 Abode::GetDesireToBeRepaired(void)
float Abode::GetDesireToBeRepaired()
{
    GTownInfo* townInfo = (GTownInfo*)GetTown()->info;
    if (GetPercentRepaired() > townInfo->field_0x10c ||
        ((((GAbodeInfo*)info)->abodeType & ABODE_TYPE_LIVING_QUARTERS) != 0 && villagers.count == 0))
    {
        return 0.0f;
    }
    return MultiMapFixed::GetDesireToBeRepaired();
}

// win1.41 004069c0 mac 1036ee00 Abode::FindVillager( int (*)(GameThingWithPos *, SCRIPT_OBJECT_TYPE, ulong), SCRIPT_OBJECT_TYPE, ulong)
Villager* Abode::FindVillager(int (__cdecl* search_cb)(GameThingWithPos *, SCRIPT_OBJECT_TYPE, uint32_t), SCRIPT_OBJECT_TYPE type, uint32_t param_3)
{
    for (Villager* villager = villagers.head; villager != NULL; villager = villager->next)
    {
        if ((*search_cb)(villager, type, param_3))
        {
            return villager;
        }
    }
    return NULL;
}

// win1.41 00406a10 mac 103bd750 Abode::Save(GameOSFile &)
bool32_t Abode::Save(GameOSFile& file)
{
    if (MultiMapFixed::Save(file))
    {
        GameOSFileWriteCheckSum(file, field_0x7c);
        GameOSFileWriteCheckSum(file, drinking_water);
        GameOSFileWriteCheckSum(file, field_0x94);
        file.WritePtr(town);
        if (DAT_00bec990)
        {
            int count = villagers.count;
            file.WriteIt(villagers.count);
            Villager* villager = NULL;
            int i = 0;
            while (true)
            {
                if (villager == NULL)
                    villager = villagers.head;
                else
                    villager = villager->next;
                if (villager == NULL)
                    break;
                if (++i > count)
                {
                    DAT_00bec990 = false;
                    break;
                }
                if (!DAT_00bec990) break;
                file.WritePtr(villager);
            }
        }
        GameOSFileWriteCheckSum(file, adult_count);
        GameOSFileWriteCheckSum(file, field_0xb6);
        GameOSFileWriteCheckSum(file, field_0xb7);
        GameOSFileWriteCheckSum(file, index);
        file.WriteArray(resources, 2);
        bool32_t hasDestructionMesh = (destruction_mesh != NULL);
        GameOSFileWriteCheckSum(file, hasDestructionMesh);
        if (hasDestructionMesh)
        {
            destruction_mesh->WriteToFile(file);
        }
        return true;
    }
    return false;
}

// win1.41 00407020 mac inlined Abode::FindNearestDrinkingWater(float)
void Abode::FindNearestDrinkingWater(float max_dist)
{
    uint8_t found = GUtils::FindNearestDrinkingWater(coords, drinking_water, max_dist);
    // Set or clear bit 0 based on result
    field_0x7c = (field_0x7c ^ found) & 1 ^ field_0x7c;
}

// win1.41 00407050 mac 1004d310 Abode::GetPercentAbodeFullWithAdults(void)
float Abode::GetPercentAbodeFullWithAdults()
{
    GAbodeInfo* _info = (GAbodeInfo*)info;
    if (_info->maxVillagersInAbode != 0)
    {
        return GetNumAdultsInAbode() / _info->maxVillagersInAbode;
    }
    return 1.0f;
}

// win1.41 00407090 mac 10058a60 Abode::GetPercentAbodeFullWithChildren(void)
float Abode::GetPercentAbodeFullWithChildren()
{
    int maxChildren = ((GAbodeInfo*)info)->maxChildrenInAbode;
    if (maxChildren != 0)
    {
        return (uint32_t)field_0xb7 / maxChildren;
    }
    return 1.0f;
}

// win1.41 004070d0 mac 104ed230 Abode::GetNumAdultsInAbode(void)
float Abode::GetNumAdultsInAbode()
{
    return adult_count;
}

// win1.41 004070f0 mac 101b8780 Abode::DrawPercentFull(int)
void Abode::DrawPercentFull(bool32_t only_one)
{
    LHPoint translation;
    translation.x = game_3d_object->matrix.m[9];
    translation.y = game_3d_object->matrix.m[10];
    translation.z = game_3d_object->matrix.m[11];
    float height = game_3d_object->GetMesh()->bounding_box.size.y;
    translation.y += height + height + 1.5f;
    uint32_t maxVillagers = ((GAbodeInfo*)info)->maxVillagersInAbode;
    int numAdults = GetNumAdultsInAbode();
    if (only_one)
    {
        maxVillagers = 1;
        numAdults = -1;
    }
    Draw__13HowManyPeopleFllP7LHPoint(maxVillagers, numAdults, &translation);
}

// win1.41 00407170 mac 1034ec40 Abode::GetDiscipleStateIfInteractedWith(GInterfaceStatus *, Villager *)
uint32_t Abode::GetDiscipleStateIfInteractedWith(GInterfaceStatus* status, Villager* villager)
{
    uint32_t result = MultiMapFixed::GetDiscipleStateIfInteractedWith(status, villager);
    if (result == 0 && IsFunctional() &&
        GetPlayer() == status->GetPlayer() &&
        GetPercentAbodeFullWithAdults() < 1.0f &&
        villager->GetAbode() != this &&
        GetTown() != NULL && GetTown()->field_0x5f4 == 0)
    {
        return 10;
    }
    return result;
}

// win1.41 00407200 mac 1008a7b0 Abode::IsInteractable(void)
bool32_t Abode::IsInteractable()
{
    if (GetPercentBuilt() == 0.0f)
        return false;
    return GameThingWithPos::IsInteractable();
}

// win1.41 00407280 mac 100dcdb0 Abode::CanBeHiddenIn(void)
bool32_t Abode::CanBeHiddenIn()
{
    return IsFunctional();
}

// win1.41 004072a0 mac 10053220 Abode::GetInfluence(void)
float Abode::GetInfluence()
{
    float baseInfluence = MultiMapFixed::GetInfluence();
    return (GetNumAdultsInAbode() + field_0xb7 + 1.0f) * baseInfluence;
}

// win1.41 004073c0 mac 103b5600 Abode::StopBeingFunctional(GPlayer *)
void Abode::StopBeingFunctional(GPlayer* player)
{
    if (player != NULL && this->field_0xb9 >= 200)
    {
        player->game_stats->field_0x1080++;
        FUN_004073f0(player);
    }
}

// win1.41 004073f0 mac inlined Abode::FUN_004073f0(GPlayer *)
void Abode::FUN_004073f0(GPlayer* player)
{
    if ((field_0x7c & 0x40) == 0)
    {
        if ((field_0x7c & 0x20) == 0)
        {
            player->FUN_0064da80(9, 1);
        }
        else
        {
            player->FUN_0064da80(10, 1);
        }
    }
}

// win1.41 00407420 mac 10351de0 Abode::DiscipleInHandNear(Villager &, GInterfaceStatus &)
void Abode::DiscipleInHandNear(Villager& disciple, GInterfaceStatus& status)
{
    if (((GAbodeInfo*)info)->maxVillagersInAbode > 0)
    {
        float distance = coords.GetMetresDistance(disciple.coords);
        float radius = Get2DRadius();
        if (distance < radius)
        {
            Town* town = GetTown();
            if (town != NULL && town->field_0x5f4 == 0)
            {
                if (town->GetPlayer() == status.GetPlayer())
                {
                    abode_town_00c4cc6c = town;
                    KnockKnock__13HowManyPeopleFv();

                }
            }
        }
    }
}

// win1.41 004074a0 mac 100e7ac0 Abode::CalculateDesireToGainMale(void)
float Abode::CalculateDesireToGainMale()
{
    float result = 0.0f;
    if (((GAbodeInfo*)info)->maxVillagersInAbode != 0)
    {
        Town* town = GetTown();
        if (town != NULL)
        {
            result = (town->stats.field_0x54 + 0.001f) / (town->stats.field_0x58 + 0.001f) - 
                (field_0xb5 + 0.001f) / ((adult_count - field_0xb5) + 0.001f);
        }
    }
    return result;
}

// win1.41 00407540 mac 100af0d0 Abode::CalculateDesireToGainVillager(void)
float Abode::CalculateDesireToGainVillager()
{
    float result = 0.0f;
    if (((GAbodeInfo*)info)->maxVillagersInAbode != 0)
    {
        Town* town = GetTown();
        if (town != NULL)
        {
            result = (town->stats.num_adults + 0.001f) / (town->stats.field_0x34 + 0.001f) - GetPercentAbodeFullWithAdults();
        }
    }
    return result;
}

// win1.41 004075b0 mac 10518900 Abode::TakeVillagerFrom(Abode&, int)
bool32_t Abode::TakeVillagerFrom(Abode& other, bool32_t male)
{
    for (Villager* walker = other.villagers.head; walker != NULL; walker = walker->next)
    {
        bool32_t found;
        if (male)
        {
            found = walker->IsMaleVillager();
        }
        else
        {
            found = walker->IsFemaleVillager();
        }
        if (found && (walker->field_0xe0 & 4) == 0)
        {
            walker->ForceMoveVillagerToAbode(this);
            return true;
        }
    }
    return false;
}

// win1.41 00407620 mac 10516470 Abode::SwapMaleForFemaleFrom(Abode&)
bool32_t Abode::SwapMaleForFemaleFrom(Abode& other)
{
    Villager* male = other.villagers.head;
    for (; male != NULL; male = male->next)
    {
        if (male->IsMaleVillager() && (male->field_0xe0 & 4) == 0)
        {
            break;
        }
    }

    if (male != NULL)
    {
        Villager* female = villagers.head;
        for (; female != NULL; female = female->next)
        {
            if (female->IsFemaleVillager() && (female->field_0xe0 & 4) == 0)
            {
                male->ForceMoveVillagerToAbode(this);
                female->ForceMoveVillagerToAbode(&other);
                return true;
            }
        }
    }

    return false;
}


bool32_t MultiMapFixed::IsPlaytimeStructure()
{
    return (bool32_t)0;
}

bool32_t MultiMapFixed::IsPlaytimeStarted()
{
    return (bool32_t)0;
}

float MultiMapFixed::GetPercentBuilt()
{
    return *(float *)((char *)this + 0x5c);
}

void* MultiMapFixed::GetBuildingObject()
{
    return (void*)this;
}

bool32_t MultiMapFixed::IsSolidToNewAbode()
{
    return (bool32_t)0x1;
}

bool32_t MultiMapFixed::IsFootpathLink()
{
    return (bool32_t)0x1;
}

GFootpathLink* MultiMapFixed::GetFootpathLink()
{
    return (GFootpathLink*)*(unsigned int *)((char *)this + 0x64);
}


void Object::SetJustScale(float scale)
{
    *(float *)((char *)this + 0x50) = scale;
}

void PlannedMultiMapFixed::SetScale(float scale)
{
    *(float *)((char *)this + 0x2c) = scale;
}


MultiMapFixed* MultiMapFixed::AsMultiMapFixed()
{
    return (MultiMapFixed*)this;
}

MultiMapFixed* MultiMapFixed::CastMultiMapFixed()
{
    return (MultiMapFixed*)this;
}

void MultiMapFixed::AddToPlayer()
{
    
}

void MultiMapFixed::RemoveFromPlayer()
{
    
}


uint16_t Abode::GetNumberOfInstanceForGlobalList()
{
    return (uint16_t)0x1;
}


bool32_t Object::IsSuitableForCreatureAction()
{
    return (bool32_t)*(unsigned int *)(*(char **)((char *)this + 0x28) + 0xc0);
}

TRIBE_TYPE Abode::GetTribeType() const
{
    return (TRIBE_TYPE)*(unsigned int *)(*(char **)((char *)this + 0x98) + 0x5b8);
}

ABODE_TYPE Abode::GetAbodeType()
{
    return (ABODE_TYPE)*(unsigned int *)(*(char **)((char *)this + 0x28) + 0x120);
}


int MultiMapFixed::CalulateAmountOverMaximum(RESOURCE_TYPE type)
{
    return (int)0;
}


bool32_t GameThing::IsAvailable()
{
    return (*(unsigned char *)((char *)this + 0xa) & 1) == 0;
}

bool32_t Abode::ShouldFootpathsGoRound()
{
    return (*(unsigned char *)((char *)this + 0x58) & 2) != 2;
}

// harvested via mangle_check.py (clean header-vs-symbol)
void GBaseInfo::UpdateValue(float param_1, uint32_t param_2, uint32_t param_3) {}
