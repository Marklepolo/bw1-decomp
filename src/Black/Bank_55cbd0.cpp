#include "PlayerComputer.h"
#include "PlayerComputer.h"
#include "PlayerComputer.h"
#include "PlayerComputer.h"
#include "PlayerComputer.h"
#include "PlayerComputer.h"
#include "PlayerComputer.h"
#include "PSysRenderParticle.h"
#include "PSysModifiers.h"
#include "PSysModifiers.h"
#include "PSysModifiers.h"
#include "PlayerComputer.h"
#include "PlayerComputer.h"
#include "Influence.h"
#include "Climate.h"
#include "FieldCrop.h"
#include "GameOSFile.h"
#include "GameThingWithPos.h"
#include "Graveyard.h"
#include "HanoiBlock.h"
#include "JPSysInterface.h"
#include "Mist.h"
#include "MobileObject.h"
#include "MobileStatic.h"
#include "OneOffSpellSeed.h"
#include "PSysInterface.h"
#include "Particle3DPnt.h"
#include "Particle3DSprite.h"
#include "ParticleChainJoint.h"
#include "ParticleContainer.h"
#include "PileFood.h"
#include "PileResource.h"
#include "PileWood.h"
#include "PlannedMultiMapFixed.h"
#include "PlannedTownCentre.h"
#include "Poo.h"
#include "Pot.h"
#include "PotStructure.h"
#include "PuzzleGame.h"
#include "Rock.h"
#include "Scaffold.h"
#include "ScriptMarker.h"
#include "ScriptTimer.h"
#include "ShowNeeds.h"
#include "ShowNeedsVisuals.h"
#include "SpecialVillager.h"
#include "Spell.h"
#include "SpellFlock.h"
#include "SpellFlockFlying.h"
#include "SpellFlockGround.h"
#include "SpellForest.h"
#include "SpellHeal.h"
#include "SpellIcon.h"
#include "SpellPointInf.h"
#include "SpellResource.h"
#include "SpellTeleport.h"
#include "SpellWater.h"
#include "SpellWithObjects.h"
#include "StoragePit.h"
#include "Stream.h"
#include "StreetLantern.h"
#include "StreetLight.h"
#include "Totem.h"
#include "TotemStatue.h"
#include "TownCentre.h"
#include "TownDesireFlags.h"
#include "TownSpellIcon.h"
#include "Tree.h"
#include "VortexObjectInfo.h"
#include "Waterfall.h"
#include "WeatherThing.h"
#include "Whale.h"
#include "Wonder.h"
#include "WorshipSite.h"



// win1.41 0055cbd0 mac inlined PlannedMultiMapFixed::GetSaveType(void)
uint32_t PlannedMultiMapFixed::GetSaveType()
{
    return (uint32_t)0x00000038;
}

// win1.41 0055cce0 mac 101513e0 StoragePit::CausesTownEmergencyIfDamaged(void)
bool32_t StoragePit::CausesTownEmergencyIfDamaged()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055ccf0 mac 10151430 StoragePit::IsCastShadowAtNight(void)
bool32_t StoragePit::IsCastShadowAtNight()
{
    return (bool32_t)(0);
}

// win1.41 0055cd00 mac 10151470 StoragePit::CanActAsAContainer(Creature *)
bool32_t StoragePit::CanActAsAContainer(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055cd10 mac 101514c0 StoragePit::CanBeEatenByCreature(Creature *)
bool32_t StoragePit::CanBeEatenByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055cd30 mac 10151560 StoragePit::GetSaveType(void)
uint32_t StoragePit::GetSaveType()
{
    return (uint32_t)0x00000008;
}

// win1.41 0055cd40 mac 101515a0 StoragePit::GetDebugText(void)
char* StoragePit::GetDebugText()
{
    return (char*)0x00bed1b8;
}

// win1.41 0055cd50 mac 10153360 StoragePit::_dt(void)
StoragePit::~StoragePit()
{
}

// win1.41 0055cd80 mac inlined Spell::GetSpellCastPos(MapCoords *)
__declspec(naked) void Spell::GetSpellCastPos(MapCoords* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            add ecx, 0x000000cc
            push esi
            mov esi, dword ptr [ecx]
            mov edx, eax
            mov dword ptr [edx], esi
            mov esi, dword ptr [ecx + 0x04]
            mov dword ptr [edx + 0x04], esi
            mov ecx, dword ptr [ecx + 0x08]
            mov dword ptr [edx + 0x08], ecx
            pop esi
            ret 4
        }
}

// win1.41 0055cdb0 mac 103b1c00 Spell::GetLife(void)
float Spell::GetLife()
{
    return *(float*)((char*)this + 0x38);
}

// win1.41 0055cdf0 mac 100d40a0 Spell::GetPlayer(void)
GPlayer* Spell::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x000000a4);
}

// win1.41 0055ce00 mac 103b1ce0 Spell::HasEnoughChantsAndLifeForRecast(void)
void Spell::HasEnoughChantsAndLifeForRecast()
{
    __asm { mov al, 0x01 }
}

// win1.41 0055ce10 mac 103b1d30 Spell::UpdateStruckReaction(void)
void Spell::UpdateStruckReaction()
{
}

// win1.41 0055ce20 mac 103b1d70 Spell::SetUpDestroyedReaction(void)
void Spell::SetUpDestroyedReaction()
{
}

// win1.41 0055ce30 mac 103b1db0 Spell::GetCreatureCastOn(void)
uint32_t Spell::GetCreatureCastOn()
{
    return (uint32_t)(0);
}

// win1.41 0055ce40 mac 10280a00 Spell::CloseDown(void)
extern "C" void jmp_addr_0x00720160(void);
__declspec(naked) void Spell::CloseDown()
{
    __asm {
            jmp jmp_addr_0x00720160
        }
}

// win1.41 0055ce50 mac 103b1df0 Spell::IsSpell( const(void))
bool32_t Spell::IsSpell() const
{
    return (bool32_t)0x00000001;
}

// win1.41 0055ce60 mac 103b1e20 Spell::AdjustSpellSeedPos(MapCoords *)
void Spell::AdjustSpellSeedPos(MapCoords* param_1)
{
}

// win1.41 0055ce70 mac 103b1e60 Spell::IsSpellCreature(void)
bool32_t Spell::IsSpellCreature()
{
    return (bool32_t)(0);
}

// win1.41 0055ce80 mac 103b1ea0 Spell::IsSpellStormAndTornado(void)
bool32_t Spell::IsSpellStormAndTornado()
{
    return (bool32_t)(0);
}

// win1.41 0055ce90 mac 103b1ee0 Spell::SetMaxObjectsToCreate(long)
void Spell::SetMaxObjectsToCreate(int param_1)
{
}

// win1.41 0055cea0 mac inlined SpellWithObjects::GetMaxObjectsToCreate(void)
int SpellWithObjects::GetMaxObjectsToCreate()
{
    return (int)(-1);
}

// win1.41 0055ceb0 mac 103b1f60 Spell::GetCreatureBeliefListType(void)
uint32_t Spell::GetCreatureBeliefListType()
{
    return (uint32_t)0x00000001;
}

// win1.41 0055cec0 mac 103b1fa0 Spell::GetCreatureBeliefType(void)
uint32_t Spell::GetCreatureBeliefType()
{
    return (uint32_t)0x0000000a;
}

// win1.41 0055ced0 mac 103b1fe0 Spell::CanBeFrighteningToCreature(Creature *)
bool32_t Spell::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055cee0 mac 103b2030 Spell::IsSuitableForCreatureAction(void)
bool32_t Spell::IsSuitableForCreatureAction()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055cef0 mac 103b2070 Spell::GetOrigin(void)
uint32_t Spell::GetOrigin()
{
    return (uint32_t)0x00000002;
}

// win1.41 0055cf00 mac 103b20a0 Spell::GetText(void)
const char* Spell::GetText()
{
    return (const char*)0x00bdf05c;
}

// win1.41 0055cf20 mac 103b2120 Spell::GetImpressiveIntensity(IMPRESSIVE_TYPE)
extern "C" void jmp_addr_0x00720750(void);
__declspec(naked) float Spell::GetImpressiveIntensity(IMPRESSIVE_TYPE param_1)
{
    __asm {
            call jmp_addr_0x00720750
            ret 4
        }
}

// win1.41 0055cf50 mac 103b1b10 SpellWithObjects::GetSetObjectsDyingOnCloseDown(void)
bool32_t SpellWithObjects::GetSetObjectsDyingOnCloseDown()
{
    __asm { mov al, 0x01 }
}

// win1.41 0055cf60 mac 10519d90 SpellWithObjects::GetSaveType(void)
uint32_t SpellWithObjects::GetSaveType()
{
    return (uint32_t)0x00000014;
}

// win1.41 0055cf70 mac 10519dd0 SpellWithObjects::GetDebugText(void)
char* SpellWithObjects::GetDebugText()
{
    return (char*)0x00bed1c4;
}

// win1.41 0055cf80 mac 1030e320 SpellWithObjects::_dt(void)
SpellWithObjects::~SpellWithObjects()
{
}

// win1.41 0055cfb0 mac 1051fe70 SpellResource::GetSaveType(void)
uint32_t SpellResource::GetSaveType()
{
    return (uint32_t)0x0000000a;
}

// win1.41 0055cfc0 mac 1051feb0 SpellResource::GetDebugText(void)
char* SpellResource::GetDebugText()
{
    return (char*)0x00bed1d8;
}

// win1.41 0055cfd0 mac 1051fdd0 SpellResource::_dt(void)
SpellResource::~SpellResource()
{
}

// win1.41 0055d000 mac 1051ef10 SpellWater::GetSaveType(void)
uint32_t SpellWater::GetSaveType()
{
    return (uint32_t)0x0000000c;
}

// win1.41 0055d010 mac 1051ef50 SpellWater::GetDebugText(void)
char* SpellWater::GetDebugText()
{
    return (char*)0x00bed1e4;
}

// win1.41 0055d020 mac 1051ee70 SpellWater::_dt(void)
SpellWater::~SpellWater()
{
}

// win1.41 0055d080 mac 103bdd30 MobileObject::_dt(void)
MobileObject::~MobileObject()
{
}

// win1.41 0055d0a0 mac 103be1b0 Poo::GetSaveType(void)
uint32_t Poo::GetSaveType()
{
    return (uint32_t)0x0000006b;
}

// win1.41 0055d0b0 mac 103be1e0 Poo::GetDebugText(void)
char* Poo::GetDebugText()
{
    return (char*)0x00bed1f0;
}

// win1.41 0055d0c0 mac 103be130 Poo::_dt(void)
Poo::~Poo()
{
}

// win1.41 0055d0e0 mac 103baae0 FieldCrop::PhysicsEditorCreate(int)
void FieldCrop::PhysicsEditorCreate(int param_1)
{
}

// win1.41 0055d0f0 mac 103bab20 FieldCrop::GetSaveType(void)
uint32_t FieldCrop::GetSaveType()
{
    return (uint32_t)0x0000006c;
}

// win1.41 0055d100 mac 103bab60 FieldCrop::GetDebugText(void)
char* FieldCrop::GetDebugText()
{
    return (char*)0x00bed1f8;
}

// win1.41 0055d110 mac 103bb4e0 FieldCrop::_dt(void)
FieldCrop::~FieldCrop()
{
}

// win1.41 0055d130 mac 10526310 OneOffSpellSeed::CastOneOffSpellSeed(void)
SpellSeed* OneOffSpellSeed::CastOneOffSpellSeed()
{
    return (SpellSeed*)this;
}

// win1.41 0055d140 mac 10526350 OneOffSpellSeed::GetComputerSeen(void)
bool32_t OneOffSpellSeed::GetComputerSeen()
{
    return (bool32_t)(this);
}

// win1.41 0055d150 mac 10526390 OneOffSpellSeed::GetSaveType(void)
uint32_t OneOffSpellSeed::GetSaveType()
{
    return (uint32_t)0x00000025;
}

// win1.41 0055d160 mac 105263d0 OneOffSpellSeed::GetDebugText(void)
char* OneOffSpellSeed::GetDebugText()
{
    return (char*)0x00bed204;
}

// win1.41 0055d170 mac 10526280 OneOffSpellSeed::_dt(void)
OneOffSpellSeed::~OneOffSpellSeed()
{
}

// win1.41 0055d190 mac 10533dc0 SpellHeal::GetSaveType(void)
uint32_t SpellHeal::GetSaveType()
{
    return (uint32_t)0x00000012;
}

// win1.41 0055d1a0 mac 10533e00 SpellHeal::GetDebugText(void)
char* SpellHeal::GetDebugText()
{
    return (char*)0x00bed218;
}

// win1.41 0055d1b0 mac 10533d20 SpellHeal::_dt(void)
SpellHeal::~SpellHeal()
{
}

// win1.41 0055d1e0 mac 1051ff90 SpellForest::CloseDown(void)
extern "C" void jmp_addr_0x00720160(void);
__declspec(naked) void SpellForest::CloseDown()
{
    __asm {
            push esi
            mov esi, ecx
            call jmp_addr_0x00720160
            mov dword ptr [esi + 0x000000a0], 0x00000000
            pop esi
            ret
        }
}

// win1.41 0055d200 mac 10520050 SpellForest::GetSaveType(void)
uint32_t SpellForest::GetSaveType()
{
    return (uint32_t)0x0000000f;
}

// win1.41 0055d210 mac 10520090 SpellForest::GetDebugText(void)
char* SpellForest::GetDebugText()
{
    return (char*)0x00bed224;
}

// win1.41 0055d220 mac 1051fef0 SpellForest::_dt(void)
SpellForest::~SpellForest()
{
}

// win1.41 0055d280 mac 1051ec50 SpellFlockFlying::GetSaveType(void)
uint32_t SpellFlockFlying::GetSaveType()
{
    return (uint32_t)0x0000000d;
}

// win1.41 0055d290 mac 1051ec90 SpellFlockFlying::GetDebugText(void)
char* SpellFlockFlying::GetDebugText()
{
    return (char*)0x00bed234;
}

// win1.41 0055d2a0 mac 1051dac0 SpellFlockFlying::_dt(void)
SpellFlockFlying::~SpellFlockFlying()
{
}

// win1.41 0055d2d0 mac 1051bf40 SpellFlockGround::GetSaveType(void)
uint32_t SpellFlockGround::GetSaveType()
{
    return (uint32_t)0x0000000e;
}

// win1.41 0055d2e0 mac 1051bf80 SpellFlockGround::GetDebugText(void)
char* SpellFlockGround::GetDebugText()
{
    return (char*)0x00bed248;
}

// win1.41 0055d2f0 mac 1051bea0 SpellFlockGround::_dt(void)
SpellFlockGround::~SpellFlockGround()
{
}

// win1.41 0055d380 mac inlined SpellIcon::SetSpecularColor(LH3DColor)
void SpellIcon::SetSpecularColor(LH3DColor param_1)
{
    *(LH3DColor*)((char*)this + 0x0000010c) = param_1;
}

// win1.41 0055d3a0 mac 1049e650 SpellIcon::GetWorshipSite(void)
WorshipSite* SpellIcon::GetWorshipSite()
{
    return (WorshipSite*)(0);
}

// win1.41 0055d410 mac 10525e90 SpellIcon::ValidAsInterfaceLeashTarget(void)
bool32_t SpellIcon::ValidAsInterfaceLeashTarget()
{
    return (bool32_t)(0);
}

// win1.41 0055d420 mac 10525ee0 SpellIcon::GetCreatureBeliefType(void)
uint32_t SpellIcon::GetCreatureBeliefType()
{
    return (uint32_t)0x00000011;
}

// win1.41 0055d430 mac 10525f20 SpellIcon::CanBeFrighteningToCreature(Creature *)
bool32_t SpellIcon::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0055d460 mac 10526010 SpellIcon::GetSaveType(void)
uint32_t SpellIcon::GetSaveType()
{
    return (uint32_t)0x00000081;
}

// win1.41 0055d470 mac 10526050 SpellIcon::GetDebugText(void)
char* SpellIcon::GetDebugText()
{
    return (char*)0x009c9648;
}

// win1.41 0055d480 mac 10525750 SpellIcon::_dt(void)
SpellIcon::~SpellIcon()
{
}

// win1.41 0055d4c0 mac 100d32d0 Pot::GetResourceType(void)
RESOURCE_TYPE Pot::GetResourceType()
{
    return *(RESOURCE_TYPE*)((char*)this + 0x68);
}

// win1.41 0055d4d0 mac 10116190 Pot::GetDefaultResource(void)
int Pot::GetDefaultResource()
{
    return *(int*)((char*)this + 0x70);
}

// win1.41 0055d4e0 mac 1000ea20 Pot::IsPoisoned(void)
bool32_t Pot::IsPoisoned()
{
    return *(uint8_t*)((char*)this + 0x74) & 1;
}

// win1.41 0055d4f0 mac 101161d0 Pot::IsSpeedUp(void)
bool32_t Pot::IsSpeedUp()
{
    return (*(uint8_t*)((char*)this + 0x74) >> 4) & 1;
}

// win1.41 0055d500 mac 10116210 Pot::IsPot(void)
bool32_t Pot::IsPot()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d510 mac 100011f0 Pot::SetPoisoned(int)
__declspec(naked) void Pot::SetPoisoned(int param_1)
{
    __asm {
            mov al, byte ptr [ecx + 0x74]
            push ebx
            mov bl, byte ptr [esp + 0x08]
            mov dl, al
            xor dl, bl
            and dl, 0x01
            xor dl, al
            mov byte ptr [ecx + 0x74], dl
            pop ebx
            ret 4
        }
}

// win1.41 0055d530 mac inlined PotStructure::SetSpeedUp(int)
__declspec(naked) void PotStructure::SetSpeedUp(int param_1)
{
    __asm {
            mov al, byte ptr [esp + 0x04]
            mov dl, byte ptr [ecx + 0x74]
            and al, 0x01
            shl al, 4
            and dl, -0x11
            or al, dl
            mov byte ptr [ecx + 0x74], al
            ret 4
        }
}

// win1.41 0055d580 mac 101162d0 Pot::GetCreatureBeliefType(void)
uint32_t Pot::GetCreatureBeliefType()
{
    return (uint32_t)0x00000010;
}

// win1.41 0055d590 mac 10116310 Pot::IsAPotFromABuildingSite(void)
bool32_t Pot::IsAPotFromABuildingSite()
{
    return (*(uint8_t*)((char*)this + 0x74) >> 3) & 1;
}

// win1.41 0055d5a0 mac 10116350 Pot::GetSaveType(void)
uint32_t Pot::GetSaveType()
{
    return (uint32_t)0x00000058;
}

// win1.41 0055d5b0 mac 10116380 Pot::GetDebugText(void)
char* Pot::GetDebugText()
{
    return (char*)0x00bed25c;
}

// win1.41 0055d5c0 mac 1011c9c0 Pot::_dt(void)
Pot::~Pot()
{
}

// win1.41 0055d620 mac 10115fe0 PotStructure::SetPlayer(GPlayer *)
void PotStructure::SetPlayer(GPlayer* param_1)
{
    *(uint32_t*)((char*)this + 0x7c) = (uint32_t)param_1;
}

// win1.41 0055d630 mac 10116020 PotStructure::SetMultiMapFixed(MultiMapFixed *)
void PotStructure::SetMultiMapFixed(MultiMapFixed* param_1)
{
    *(uint32_t*)((char*)this + 0x78) = (uint32_t)param_1;
}

// win1.41 0055d640 mac 101160a0 PotStructure::CanBeThrownByPlayer(void)
__declspec(naked) bool32_t PotStructure::CanBeThrownByPlayer()
{
    __asm {
            mov eax, dword ptr [ecx + 0x70]
            test eax, eax
            setne al
            and eax, 0x000000ff
            ret
        }
}

// win1.41 0055d650 mac 101160f0 PotStructure::_dt(void)
PotStructure::~PotStructure()
{
}

// win1.41 0055d680 mac 1011d530 PileResource::IsLockedInInteract(void)
bool32_t PileResource::IsLockedInInteract()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d690 mac 1011d570 PileFood::IsPileFood(void)
bool32_t PileFood::IsPileFood()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d6a0 mac 1011d4b0 PileWood::GetSaveType(void)
uint32_t PileWood::GetSaveType()
{
    return (uint32_t)0x0000005a;
}

// win1.41 0055d6b0 mac 1011d4f0 PileWood::GetDebugText(void)
char* PileWood::GetDebugText()
{
    return (char*)0x00bed264;
}

// win1.41 0055d6c0 mac 10116ea0 PileWood::_dt(void)
PileWood::~PileWood()
{
}

// win1.41 0055d710 mac 103af0f0 MobileStatic::GetCreatureMimicType(void)
uint32_t MobileStatic::GetCreatureMimicType()
{
    return (uint32_t)0x00000008;
}

// win1.41 0055d720 mac 103af140 MobileStatic::PhysicsEditorCreate(int)
void MobileStatic::PhysicsEditorCreate(int param_1)
{
    *(uint32_t*)((char*)this + 0x1c) = 0x00000000;
}

// win1.41 0055d730 mac 103c12f0 MobileStatic::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t MobileStatic::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d740 mac 103b9720 MobileStatic::GetSaveType(void)
uint32_t MobileStatic::GetSaveType()
{
    return (uint32_t)0x00000054;
}

// win1.41 0055d750 mac 103b9760 MobileStatic::GetDebugText(void)
char* MobileStatic::GetDebugText()
{
    return (char*)0x00bed270;
}

// win1.41 0055d760 mac 103c0dd0 MobileStatic::_dt(void)
MobileStatic::~MobileStatic()
{
}

// win1.41 0055d810 mac 103b2c70 VortexObjectInfo::GetSaveType(void)
uint32_t VortexObjectInfo::GetSaveType()
{
    return (uint32_t)0x000000ca;
}

// win1.41 0055d820 mac 103b2cb0 VortexObjectInfo::GetDebugText(void)
char* VortexObjectInfo::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 0055d850 mac 103b1a90 SpellTeleport::GetSaveType(void)
uint32_t SpellTeleport::GetSaveType()
{
    return (uint32_t)0x00000015;
}

// win1.41 0055d860 mac 103b1ad0 SpellTeleport::GetDebugText(void)
char* SpellTeleport::GetDebugText()
{
    return (char*)0x00bed2c8;
}

// win1.41 0055d870 mac 103b19e0 SpellTeleport::_dt(void)
SpellTeleport::~SpellTeleport()
{
}

// win1.41 0055d8a0 mac 101594d0 Tree::GetMesh( const(void))
int Tree::GetMesh() const
{
    return *(int*)(*(char**)((char*)this + 0x28) + 0x00000100);
}

// win1.41 0055d8b0 mac 10159520 Tree::CanBePickedUp(void)
bool32_t Tree::CanBePickedUp()
{
    return ((uint16_t)~*(uint16_t*)((char*)this + 0x24) >> 0xd) & 1;
}

// win1.41 0055d8c0 mac 10159560 Tree::GetPlayer(void)
GPlayer* Tree::GetPlayer()
{
    return (GPlayer*)(0);
}

// win1.41 0055d8d0 mac 10159590 Tree::GetReactionPower(void)
float Tree::GetReactionPower()
{
    return this->GetLife();
}

// win1.41 0055d900 mac 10159670 Tree::GetCarriedTreeType(void)
uint32_t Tree::GetCarriedTreeType()
{
    return *(uint32_t*)(*(char**)((char*)this + 0x28) + 0x00000138);
}

// win1.41 0055d920 mac inlined Tree::IsTree_0(Creature *)
bool32_t Tree::IsTree(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d930 mac 10159740 Tree::CanBePlayedWithByCreature(Creature *)
bool32_t Tree::CanBePlayedWithByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d940 mac 10159790 Tree::BenefitsFromHavingWaterSprinkledOnIt(Creature *)
bool32_t Tree::BenefitsFromHavingWaterSprinkledOnIt(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d950 mac 101597f0 Tree::GetCreatureBeliefType(void)
uint32_t Tree::GetCreatureBeliefType()
{
    return (uint32_t)0x00000005;
}

// win1.41 0055d960 mac 10159830 Tree::GetCreatureMimicType(void)
uint32_t Tree::GetCreatureMimicType()
{
    return (uint32_t)0x00000006;
}

// win1.41 0055d970 mac 10159870 Tree::CanBeUsedForBuilding(Creature *)
bool32_t Tree::CanBeUsedForBuilding(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d980 mac 101598c0 Tree::CanBeUsedForRepair(Creature *)
bool32_t Tree::CanBeUsedForRepair(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d990 mac 10159900 Tree::CanBeDestroyedByStoning(Creature *)
bool32_t Tree::CanBeDestroyedByStoning(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0055d9a0 mac 10159950 Tree::CanBeAttackedByCreature(Creature *)
bool32_t Tree::CanBeAttackedByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d9b0 mac 101599a0 Tree::CanBeThrownInTheSeaPlayfully(Creature *)
bool32_t Tree::CanBeThrownInTheSeaPlayfully(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d9c0 mac 101599f0 Tree::IsAnyKindOfTree(void)
bool32_t Tree::IsAnyKindOfTree()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d9d0 mac inlined Tree::IsTree_1(void)
bool32_t Tree::IsTree()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055d9e0 mac 10159a30 Tree::HandShouldFeelWithMeshIntersect(void)
bool32_t Tree::HandShouldFeelWithMeshIntersect()
{
    return (bool32_t)(0);
}

// win1.41 0055da10 mac 10159b10 Tree::IsCastShadowAtNight(void)
bool32_t Tree::IsCastShadowAtNight()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055da20 mac 10159b50 Tree::GetSaveType(void)
uint32_t Tree::GetSaveType()
{
    return (uint32_t)0x0000004f;
}

// win1.41 0055da30 mac 10159b80 Tree::GetDebugText(void)
char* Tree::GetDebugText()
{
    return (char*)0x00bed2d8;
}

// win1.41 0055da40 mac 10159150 Tree::_dt(void)
Tree::~Tree()
{
}

// win1.41 0055da70 mac 103540e0 TownDesireFlags::GetTown(void)
Town* TownDesireFlags::GetTown()
{
    return *(Town**)((char*)this + 0x64);
}

// win1.41 0055da80 mac 1055bf60 TownDesireFlags::GetMesh( const(void))
int TownDesireFlags::GetMesh() const
{
    return *(int*)((char*)this + 0x60);
}

// win1.41 0055daa0 mac 1055bff0 TownDesireFlags::IsTownDesireFlag(void)
bool32_t TownDesireFlags::IsTownDesireFlag()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055dab0 mac 1055c030 TownDesireFlags::IsEffectReceiver(EffectValues *)
bool32_t TownDesireFlags::IsEffectReceiver(EffectValues* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0055dac0 mac 1055c080 TownDesireFlags::GetSaveType(void)
uint32_t TownDesireFlags::GetSaveType()
{
    return (uint32_t)0x0000004c;
}

// win1.41 0055dad0 mac 1055c0c0 TownDesireFlags::GetDebugText(void)
char* TownDesireFlags::GetDebugText()
{
    return (char*)0x00bed2e0;
}

// win1.41 0055dae0 mac 1055db90 TownDesireFlags::_dt(void)
TownDesireFlags::~TownDesireFlags()
{
}

// win1.41 0055db10 mac 1055bcb0 TownCentre::InterfaceValidToTap(GInterfaceStatus *)
uint32_t TownCentre::InterfaceValidToTap(GInterfaceStatus* param_1)
{
    return (uint32_t)(0);
}

// win1.41 0055db30 mac 1055bd40 TownCentre::CausesTownEmergencyIfDamaged(void)
bool32_t TownCentre::CausesTownEmergencyIfDamaged()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055db40 mac 1055bd90 TownCentre::CanActAsAContainer(Creature *)
bool32_t TownCentre::CanActAsAContainer(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0055db50 mac 1055bde0 TownCentre::IsStoragePit(Creature *)
bool32_t TownCentre::IsStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0055db60 mac 1055be20 TownCentre::IsCastShadowAtNight(void)
bool32_t TownCentre::IsCastShadowAtNight()
{
    return (bool32_t)(0);
}

// win1.41 0055db70 mac 1055be60 TownCentre::IsTownCentre(void)
bool32_t TownCentre::IsTownCentre()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055db80 mac 1055bea0 TownCentre::CanBeHiddenIn(void)
bool32_t TownCentre::CanBeHiddenIn()
{
    return (bool32_t)(0);
}

// win1.41 0055db90 mac 1055bee0 TownCentre::GetSaveType(void)
uint32_t TownCentre::GetSaveType()
{
    return (uint32_t)0x00000060;
}

// win1.41 0055dba0 mac 1055bf20 TownCentre::GetDebugText(void)
char* TownCentre::GetDebugText()
{
    return (char*)0x00bed2f4;
}

// win1.41 0055dbb0 mac 1055ba70 TownCentre::_dt(void)
TownCentre::~TownCentre()
{
}

// win1.41 0055dbf0 mac 10559920 PlannedTownCentre::GetSaveType(void)
uint32_t PlannedTownCentre::GetSaveType()
{
    return (uint32_t)0x00000062;
}

// win1.41 0055dc00 mac 10559960 PlannedTownCentre::GetDebugText(void)
char* PlannedTownCentre::GetDebugText()
{
    return (char*)0x00bed300;
}

// win1.41 0055dc10 mac 10559840 PlannedTownCentre::_dt(void)
PlannedTownCentre::~PlannedTownCentre()
{
}

// win1.41 0055dc30 mac inlined WorshipSite::GetInteractPos(LHPoint *)
extern "C" void jmp_addr_0x0077cf70(void);
__declspec(naked) void WorshipSite::GetInteractPos(LHPoint* param_1)
{
    __asm {
            push esi
            mov esi, dword ptr [esp + 0x08]
            push esi
            call jmp_addr_0x0077cf70
            mov eax, esi
            pop esi
            ret 4
        }
}

// win1.41 0055dc50 mac 105b3d80 WorshipSite::RemoveDance(void)
void WorshipSite::RemoveDance()
{
    *(uint32_t*)((char*)this + 0x000000a0) = 0x00000000;
}

// win1.41 0055dc60 mac 105b3dc0 WorshipSite::InteractsWithPhysicsObjects(void)
bool32_t WorshipSite::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 0055dc70 mac 105b3e10 WorshipSite::GetAbodeType(void)
ABODE_TYPE WorshipSite::GetAbodeType()
{
    return ABODE_TYPE_CITADEL;
}

// win1.41 0055dc80 mac 105b3e50 WorshipSite::IsSuitableForCreatureAction(void)
bool32_t WorshipSite::IsSuitableForCreatureAction()
{
    return (bool32_t)(0);
}

// win1.41 0055dc90 mac inlined WorshipSite::IsWorshipSite_0(Creature *)
bool32_t WorshipSite::IsWorshipSite(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0055dca0 mac inlined WorshipSite::IsWorshipSite_1(void)
bool32_t WorshipSite::IsWorshipSite()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055dcc0 mac 105b3f70 WorshipSite::GetMesh( const(void))
int WorshipSite::GetMesh() const
{
    return *(int*)(*(char**)((char*)this + 0x28) + 0x00000138);
}

// win1.41 0055dcd0 mac 105b3fc0 WorshipSite::GetSaveType(void)
uint32_t WorshipSite::GetSaveType()
{
    return (uint32_t)0x0000003c;
}

// win1.41 0055dce0 mac 105b4000 WorshipSite::GetDebugText(void)
char* WorshipSite::GetDebugText()
{
    return (char*)0x00bed314;
}

// win1.41 0055dcf0 mac 105b3620 WorshipSite::_dt(void)
WorshipSite::~WorshipSite()
{
}

// win1.41 0055dd20 mac 10146330 ShowNeeds::GetSaveType(void)
uint32_t ShowNeeds::GetSaveType()
{
    return (uint32_t)0x0000003e;
}

// win1.41 0055dd30 mac 10146370 ShowNeeds::GetDebugText(void)
char* ShowNeeds::GetDebugText()
{
    return (char*)0x00bed324;
}

// win1.41 0055dd40 mac 101462a0 ShowNeeds::_dt(void)
ShowNeeds::~ShowNeeds()
{
}

// win1.41 0055dd80 mac 101449e0 ShowNeedsVisuals::GetScale(void)
float ShowNeedsVisuals::GetScale()
{
    return *(float*)((char*)this + 0x58);
}

// win1.41 0055dd90 mac 10144a20 ShowNeedsVisuals::GetText(void)
const char* ShowNeedsVisuals::GetText()
{
    return (const char*)0x00bed330;
}

// win1.41 0055ddb0 mac 10144ab0 ShowNeedsVisuals::GetSaveType(void)
uint32_t ShowNeedsVisuals::GetSaveType()
{
    return (uint32_t)0x0000003d;
}

// win1.41 0055ddc0 mac 10144af0 ShowNeedsVisuals::GetDebugText(void)
char* ShowNeedsVisuals::GetDebugText()
{
    return (char*)0x00bed33c;
}

// win1.41 0055ddd0 mac 10144860 ShowNeedsVisuals::_dt(void)
ShowNeedsVisuals::~ShowNeedsVisuals()
{
}

// win1.41 0055de00 mac 101551e0 GStream::GetSaveType(void)
uint32_t GStream::GetSaveType()
{
    return (uint32_t)0x00000047;
}

// win1.41 0055de10 mac 10155220 GStream::GetDebugText(void)
char* GStream::GetDebugText()
{
    return (char*)0x00bed350;
}

// win1.41 0055de20 mac 101549b0 GStream::_dt(void)
GStream::~GStream()
{
}

// win1.41 0055de40 mac 101533f0 GWaterfall::GetSaveType(void)
uint32_t GWaterfall::GetSaveType()
{
    return (uint32_t)0x00000040;
}

// win1.41 0055de50 mac 10153430 GWaterfall::GetDebugText(void)
char* GWaterfall::GetDebugText()
{
    return (char*)0x00bed358;
}

// win1.41 0055de60 mac 10154270 GWaterfall::_dt(void)
GWaterfall::~GWaterfall()
{
}

// win1.41 0055dec0 mac 1059ef10 GClimate::GetSaveType(void)
uint32_t GClimate::GetSaveType()
{
    return (uint32_t)0x000000fc;
}

// win1.41 0055ded0 mac 1059ef50 GClimate::GetDebugText(void)
char* GClimate::GetDebugText()
{
    return (char*)0x00bed380;
}

// win1.41 0055dee0 mac 105a2870 GClimate::_dt(void)
GClimate::~GClimate()
{
}

// win1.41 0055df20 mac 105a3ee0 WeatherThing::SetAffectedByWind(int)
void WeatherThing::SetAffectedByWind(int param_1)
{
    *(uint32_t*)((char*)this + 0x7c) = (uint32_t)param_1;
}

// win1.41 0055df30 mac 105a3f20 WeatherThing::GetText(void)
const char* WeatherThing::GetText()
{
    return (const char*)0x00bed38c;
}

// win1.41 0055df40 mac 105a3f60 WeatherThing::GetSaveType(void)
uint32_t WeatherThing::GetSaveType()
{
    return (uint32_t)0x00000043;
}

// win1.41 0055df50 mac 105a3fa0 WeatherThing::GetDebugText(void)
char* WeatherThing::GetDebugText()
{
    return (char*)0x00bed39c;
}

// win1.41 0055df60 mac 105a3e00 WeatherThing::_dt(void)
WeatherThing::~WeatherThing()
{
}

// win1.41 0055df90 mac inlined Graveyard::GetArrivePos(MapCoords *)
__declspec(naked) MapCoords* Graveyard::GetArrivePos(MapCoords* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            add ecx, 0x14
            push esi
            mov esi, dword ptr [ecx]
            mov edx, eax
            mov dword ptr [edx], esi
            mov esi, dword ptr [ecx + 0x04]
            mov dword ptr [edx + 0x04], esi
            mov ecx, dword ptr [ecx + 0x08]
            mov dword ptr [edx + 0x08], ecx
            pop esi
            ret 4
        }
}

// win1.41 0055dfc0 mac 100f4440 Graveyard::CanBeHiddenIn(void)
bool32_t Graveyard::CanBeHiddenIn()
{
    return (bool32_t)(0);
}

// win1.41 0055dfd0 mac 100f4480 Graveyard::CanActAsAContainer(Creature *)
bool32_t Graveyard::CanActAsAContainer(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0055dfe0 mac 100f44d0 Graveyard::IsStoragePit(Creature *)
bool32_t Graveyard::IsStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0055dff0 mac 100f4510 Graveyard::GetSaveType(void)
uint32_t Graveyard::GetSaveType()
{
    return (uint32_t)0x00000051;
}

// win1.41 0055e000 mac 100f4550 Graveyard::GetDebugText(void)
char* Graveyard::GetDebugText()
{
    return (char*)0x00bed3ac;
}

// win1.41 0055e010 mac 100f42d0 Graveyard::_dt(void)
Graveyard::~Graveyard()
{
}

// win1.41 0055e040 mac 10560ac0 TownSpellIcon::GetTown(void)
Town* TownSpellIcon::GetTown()
{
    return *(Town**)((char*)this + 0x00000114);
}

// win1.41 0055e050 mac 10561ce0 TownSpellIcon::GetSaveType(void)
uint32_t TownSpellIcon::GetSaveType()
{
    return (uint32_t)0x00000055;
}

// win1.41 0055e060 mac 10561d20 TownSpellIcon::GetDebugText(void)
char* TownSpellIcon::GetDebugText()
{
    return (char*)0x00bed3b8;
}

// win1.41 0055e070 mac 10561b50 TownSpellIcon::_dt(void)
TownSpellIcon::~TownSpellIcon()
{
}

// win1.41 0055e0f0 mac 1013e590 Scaffold::GetResourceType(void)
RESOURCE_TYPE Scaffold::GetResourceType()
{
    return RESOURCE_TYPE_WOOD;
}

// win1.41 0055e100 mac 1013e5d0 Scaffold::IsScaffold(void)
bool32_t Scaffold::IsScaffold()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055e110 mac 1013e610 Scaffold::InteractsWithPhysicsObjects(void)
bool32_t Scaffold::InteractsWithPhysicsObjects()
{
    __asm { mov al, 0x01 }
}

// win1.41 0055e120 mac 1013e660 Scaffold::GetTown(void)
Town* Scaffold::GetTown()
{
    return *(Town**)((char*)this + 0x0000008c);
}

// win1.41 0055e130 mac 1013e690 Scaffold::GetSaveType(void)
uint32_t Scaffold::GetSaveType()
{
    return (uint32_t)0x0000005f;
}

// win1.41 0055e140 mac 1013e6d0 Scaffold::GetDebugText(void)
char* Scaffold::GetDebugText()
{
    return (char*)0x00bed3e0;
}

// win1.41 0055e150 mac 10143e00 Scaffold::_dt(void)
Scaffold::~Scaffold()
{
}

// win1.41 0055eb70 mac 10104680 Mist::GetPlayer(void)
GPlayer* Mist::GetPlayer()
{
    return (GPlayer*)(0);
}

// win1.41 0055eb80 mac 101046b0 Mist::GetText(void)
const char* Mist::GetText()
{
    return (const char*)0x00bed4d0;
}

// win1.41 0055eb90 mac 101046e0 Mist::IsMist(void)
bool32_t Mist::IsMist()
{
    return (bool32_t)0x00000001;
}

// win1.41 0055eba0 mac 10104710 Mist::GetCreatureBeliefType(void)
uint32_t Mist::GetCreatureBeliefType()
{
    return (uint32_t)0x00000012;
}

// win1.41 0055ebb0 mac 10104750 Mist::GetSaveType(void)
uint32_t Mist::GetSaveType()
{
    return (uint32_t)0x00000048;
}

// win1.41 0055ebc0 mac 10104780 Mist::GetDebugText(void)
char* Mist::GetDebugText()
{
    return (char*)0x00bed4d8;
}

// win1.41 0055ebd0 mac 101045f0 Mist::_dt(void)
Mist::~Mist()
{
}

// win1.41 0055ecb0 mac 10423d40 GJPSysInterface::GetSaveType(void)
uint32_t GJPSysInterface::GetSaveType()
{
    return (uint32_t)0x000000a5;
}

// win1.41 0055ecc0 mac 10423d80 GJPSysInterface::GetDebugText(void)
char* GJPSysInterface::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 0055ecf0 mac 100722f0 GJPSysInterface::SetOrigin(LHPoint const &)
extern "C" void jmp_addr_0x00672e10(void);
__declspec(naked) void GJPSysInterface::SetOrigin(const LHPoint* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            mov ecx, dword ptr [ecx + 0x14]
            push eax
            call jmp_addr_0x00672e10
            ret 4
        }
}

// win1.41 0055ed00 mac 10423f20 GJPSysInterface::SetOriginAndMoveAllAtoms(LHPoint const &)
extern "C" void jmp_addr_0x00672e30(void);
__declspec(naked) void GJPSysInterface::SetOriginAndMoveAllAtoms(const LHPoint* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            mov ecx, dword ptr [ecx + 0x14]
            push eax
            call jmp_addr_0x00672e30
            ret 4
        }
}

// win1.41 0055ed10 mac 10026c40 GJPSysInterface::GetOrigin(void)
extern "C" void jmp_addr_0x00672e00(void);
__declspec(naked) LHPoint* GJPSysInterface::GetOrigin()
{
    __asm {
            mov ecx, dword ptr [ecx + 0x14]
            jmp jmp_addr_0x00672e00
        }
}

// win1.41 0055ed20 mac 10001030 GJPSysInterface::SetPlayer(GPlayer *)
__declspec(naked) void GJPSysInterface::SetPlayer(GPlayer* param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x14]
            mov ecx, dword ptr [esp + 0x04]
            mov dword ptr [eax + 0x18], ecx
            ret 4
        }
}

// win1.41 0055ed30 mac 10017fc0 GJPSysInterface::SetMagnitude(float)
__declspec(naked) void GJPSysInterface::SetMagnitude(float param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x14]
            mov ecx, dword ptr [esp + 0x04]
            mov dword ptr [eax + 0x000000a0], ecx
            ret 4
        }
}

// win1.41 0055ed40 mac 10424080 GJPSysInterface::SetAge(float)
__declspec(naked) void GJPSysInterface::SetAge(float param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x14]
            mov ecx, dword ptr [esp + 0x04]
            mov dword ptr [eax + 0x70], ecx
            ret 4
        }
}

// win1.41 0055ed50 mac 104240c0 GJPSysInterface::SetAlpha(unsigned char)
__declspec(naked) void GJPSysInterface::SetAlpha(uint8_t param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x14]
            mov cl, byte ptr [esp + 0x04]
            mov byte ptr [eax + 0x6c], cl
            ret 4
        }
}

// win1.41 0055edc0 mac 10026de0 GJPSysInterface::AddDrawing(float, LHPoint const &)
extern "C" void jmp_addr_0x006797d0(void);
__declspec(naked) void GJPSysInterface::AddDrawing(float param_1, const LHPoint* param_2)
{
    __asm {
            mov eax, dword ptr [esp + 0x08]
            mov edx, dword ptr [esp + 0x04]
            mov ecx, dword ptr [ecx + 0x14]
            push eax
            push edx
            call jmp_addr_0x006797d0
            ret 8
        }
}

// win1.41 0055eef0 mac inlined Particle3DPnt::GetSaveType(void)
uint32_t Particle3DPnt::GetSaveType()
{
    return (uint32_t)0x000000a8;
}

// win1.41 0055ef00 mac inlined Particle3DPnt::GetDebugText(void)
char* Particle3DPnt::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 0055f050 mac inlined Particle3DSprite::GetDebugText(void)
char* Particle3DSprite::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 0055f0c0 mac 10422d60 ParticleChainJoint::GetSaveType(void)
uint32_t ParticleChainJoint::GetSaveType()
{
    return (uint32_t)0x000000b3;
}

// win1.41 0055f0d0 mac 10422da0 ParticleChainJoint::GetDebugText(void)
char* ParticleChainJoint::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 0055f430 mac 1041f900 SpellPointInf::GetSaveType(void)
uint32_t SpellPointInf::GetSaveType()
{
    return (uint32_t)0x000000b8;
}

// win1.41 0055f440 mac 1041f940 SpellPointInf::GetDebugText(void)
char* SpellPointInf::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 00560f40 mac 1010fde0 GParticleContainer::GetText(void)
const char* GParticleContainer::GetText()
{
    return (const char*)0x00bee114;
}

// win1.41 00560f50 mac 1010fe20 GParticleContainer::IsParticleContainer(void)
bool32_t GParticleContainer::IsParticleContainer()
{
    return (bool32_t)0x00000001;
}

// win1.41 00560f60 mac 1010fe70 GParticleContainer::GetSaveType(void)
uint32_t GParticleContainer::GetSaveType()
{
    return (uint32_t)0x0000006e;
}

// win1.41 00560f70 mac 1010feb0 GParticleContainer::GetDebugText(void)
char* GParticleContainer::GetDebugText()
{
    return (char*)0x00bee128;
}

// win1.41 00560f80 mac 1010fd40 GParticleContainer::_dt(void)
GParticleContainer::~GParticleContainer()
{
}

// win1.41 00560fc0 mac 10147c80 SpecialVillager::GetSaveType(void)
uint32_t SpecialVillager::GetSaveType()
{
    return (uint32_t)0x00000076;
}

// win1.41 00560fd0 mac 10147cc0 SpecialVillager::GetDebugText(void)
char* SpecialVillager::GetDebugText()
{
    return (char*)0x00bee13c;
}

// win1.41 00560fe0 mac 10147590 SpecialVillager::_dt(void)
SpecialVillager::~SpecialVillager()
{
}

// win1.41 00561010 mac 105014d0 ScriptMarker::GetText(void)
const char* ScriptMarker::GetText()
{
    return (const char*)0x00bee150;
}

// win1.41 00561020 mac 10501510 ScriptMarker::IsScriptMarker(void)
bool32_t ScriptMarker::IsScriptMarker()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561030 mac 10501550 ScriptMarker::PhysicsEditorCreate(int)
void ScriptMarker::PhysicsEditorCreate(int param_1)
{
}

// win1.41 00561040 mac 10501590 ScriptMarker::IsDeletedWhenReleasedFromScript(void)
bool32_t ScriptMarker::IsDeletedWhenReleasedFromScript()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561050 mac 105015e0 ScriptMarker::GetSaveType(void)
uint32_t ScriptMarker::GetSaveType()
{
    return (uint32_t)0x0000007c;
}

// win1.41 00561060 mac 10501620 ScriptMarker::GetDebugText(void)
char* ScriptMarker::GetDebugText()
{
    return (char*)0x00bee160;
}

// win1.41 00561070 mac 10501430 ScriptMarker::_dt(void)
ScriptMarker::~ScriptMarker()
{
}

// win1.41 00561100 mac 10543d20 TotemStatue::CanBeImpressedByCreature(Creature *)
bool32_t TotemStatue::CanBeImpressedByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00561110 mac 10543d70 TotemStatue::CanBePlayedWithByCreature(Creature *)
bool32_t TotemStatue::CanBePlayedWithByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00561120 mac 10543dc0 TotemStatue::HandShouldFeelWithMeshIntersect(void)
bool32_t TotemStatue::HandShouldFeelWithMeshIntersect()
{
    return (bool32_t)(0);
}

// win1.41 00561130 mac 10543e10 TotemStatue::IsEffectReceiver(EffectValues *)
bool32_t TotemStatue::IsEffectReceiver(EffectValues* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00561150 mac 10543eb0 TotemStatue::IsTotemStatue(void)
bool32_t TotemStatue::IsTotemStatue()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561160 mac 10543ef0 TotemStatue::GetSaveType(void)
uint32_t TotemStatue::GetSaveType()
{
    return (uint32_t)0x0000007f;
}

// win1.41 00561170 mac 10543f30 TotemStatue::GetDebugText(void)
char* TotemStatue::GetDebugText()
{
    return (char*)0x00bee170;
}

// win1.41 00561180 mac 105457d0 TotemStatue::_dt(void)
TotemStatue::~TotemStatue()
{
}

// win1.41 005611e0 mac 10161200 Wonder::CanActAsAContainer(Creature *)
bool32_t Wonder::CanActAsAContainer(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 005611f0 mac 10161250 Wonder::IsStoragePit(Creature *)
bool32_t Wonder::IsStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00561200 mac 10161290 Wonder::GetSaveType(void)
uint32_t Wonder::GetSaveType()
{
    return (uint32_t)0x00000080;
}

// win1.41 00561210 mac 101612d0 Wonder::GetDebugText(void)
char* Wonder::GetDebugText()
{
    return (char*)0x00bee180;
}

// win1.41 00561220 mac 10161090 Wonder::_dt(void)
Wonder::~Wonder()
{
}

// win1.41 00561270 mac 1015ff50 Whale::InteractsWithPhysicsObjects(void)
bool32_t Whale::InteractsWithPhysicsObjects()
{
    __asm { mov al, 0x01 }
}

// win1.41 00561280 mac 1015ff90 Whale::PhysicsEditorCreate(int)
void Whale::PhysicsEditorCreate(int param_1)
{
}

// win1.41 00561290 mac 1015ff10 Whale::CanBecomeAPhysicsObject(void)
bool32_t Whale::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 005612a0 mac 1015ffd0 Whale::GetSaveType(void)
uint32_t Whale::GetSaveType()
{
    return (uint32_t)0x00000097;
}

// win1.41 005612b0 mac 10160000 Whale::GetDebugText(void)
char* Whale::GetDebugText()
{
    return (char*)0x00bee19c;
}

// win1.41 005612c0 mac 1015fe80 Whale::_dt(void)
Whale::~Whale()
{
}

// win1.41 005612e0 mac 105061e0 ScriptTimer::GetText(void)
const char* ScriptTimer::GetText()
{
    return (const char*)0x00bee1a4;
}

// win1.41 005612f0 mac 1002b150 ScriptTimer::IsScriptTimer(void)
bool32_t ScriptTimer::IsScriptTimer()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561300 mac 105062c0 ScriptTimer::IsDeletedWhenReleasedFromScript(void)
bool32_t ScriptTimer::IsDeletedWhenReleasedFromScript()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561310 mac 10506310 ScriptTimer::GetSaveType(void)
uint32_t ScriptTimer::GetSaveType()
{
    return (uint32_t)0x0000007d;
}

// win1.41 00561320 mac 10506350 ScriptTimer::GetDebugText(void)
char* ScriptTimer::GetDebugText()
{
    return (char*)0x00bee1b4;
}

// win1.41 00561330 mac 10506140 ScriptTimer::_dt(void)
ScriptTimer::~ScriptTimer()
{
}

// win1.41 00561370 mac 100c41a0 Rock::InteractsWithPhysicsObjects(void)
bool32_t Rock::InteractsWithPhysicsObjects()
{
    __asm { mov al, 0x01 }
}

// win1.41 00561380 mac 100c41e0 Rock::GetSaveType(void)
uint32_t Rock::GetSaveType()
{
    return (uint32_t)0x0000006f;
}

// win1.41 00561390 mac 100c4210 Rock::GetDebugText(void)
char* Rock::GetDebugText()
{
    return (char*)0x00bee1c4;
}

// win1.41 005613a0 mac 100b4de0 Rock::_dt(void)
Rock::~Rock()
{
}

// win1.41 005613d0 mac 10535700 GStreetLight::GetPlayer(void)
GPlayer* GStreetLight::GetPlayer()
{
    return (GPlayer*)(0);
}

// win1.41 005613e0 mac 10535740 GStreetLight::GetText(void)
const char* GStreetLight::GetText()
{
    return (const char*)0x00bee1cc;
}

// win1.41 005613f0 mac 10535780 GStreetLight::IsStreetLight(void)
bool32_t GStreetLight::IsStreetLight()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561400 mac 105357c0 GStreetLight::GetSaveType(void)
uint32_t GStreetLight::GetSaveType()
{
    return (uint32_t)0x000000ff;
}

// win1.41 00561410 mac 10535800 GStreetLight::GetDebugText(void)
char* GStreetLight::GetDebugText()
{
    return (char*)0x00bee1d8;
}

// win1.41 00561420 mac 10535660 GStreetLight::_dt(void)
GStreetLight::~GStreetLight()
{
}

// win1.41 00561440 mac 10534740 GStreetLantern::IsStreetLantern(void)
bool32_t GStreetLantern::IsStreetLantern()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561450 mac 10534780 GStreetLantern::GetSaveType(void)
uint32_t GStreetLantern::GetSaveType()
{
    return (uint32_t)0x000000fe;
}

// win1.41 00561460 mac 105347c0 GStreetLantern::GetDebugText(void)
char* GStreetLantern::GetDebugText()
{
    return (char*)0x00bee1e8;
}

// win1.41 00561470 mac 105353e0 GStreetLantern::_dt(void)
GStreetLantern::~GStreetLantern()
{
}

// win1.41 00561500 mac 101336f0 Totem::CanBeImpressedByCreature(Creature *)
bool32_t Totem::CanBeImpressedByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00561510 mac 10133740 Totem::CanBePlayedWithByCreature(Creature *)
bool32_t Totem::CanBePlayedWithByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00561520 mac 10133790 Totem::IsEffectReceiver(EffectValues *)
bool32_t Totem::IsEffectReceiver(EffectValues* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00561530 mac 101337e0 Totem::IsCastShadowAtNight(void)
bool32_t Totem::IsCastShadowAtNight()
{
    return (bool32_t)(0);
}

// win1.41 00561560 mac 105427b0 Totem::GetSaveType(void)
uint32_t Totem::GetSaveType()
{
    return (uint32_t)0x0000002b;
}

// win1.41 00561570 mac 105427e0 Totem::GetDebugText(void)
char* Totem::GetDebugText()
{
    return (char*)0x00bee20c;
}

// win1.41 00561580 mac 10126730 Totem::_dt(void)
Totem::~Totem()
{
}

// win1.41 00561820 mac 1011ed30 HanoiBlock::GetInHandImmersionTexture(void)
IMMERSION_EFFECT_TYPE HanoiBlock::GetInHandImmersionTexture()
{
    return IMMERSION_EFFECT_TYPE_HANOI;
}

// win1.41 00561830 mac 1011ed80 HanoiBlock::GetSaveType(void)
uint32_t HanoiBlock::GetSaveType()
{
    return (uint32_t)0x00000030;
}

// win1.41 00561840 mac 1011edc0 HanoiBlock::GetDebugText(void)
char* HanoiBlock::GetDebugText()
{
    return (char*)0x00bee248;
}

// win1.41 00561850 mac 1011ebc0 HanoiBlock::_dt(void)
HanoiBlock::~HanoiBlock()
{
}

// win1.41 00561b30 mac 10133980 PuzzleGame::GetText(void)
const char* PuzzleGame::GetText()
{
    return (const char*)0x00bee2b4;
}

// win1.41 00561b40 mac 101339c0 PuzzleGame::IsPuzzleGame(void)
bool32_t PuzzleGame::IsPuzzleGame()
{
    return (bool32_t)0x00000001;
}

// win1.41 00561b50 mac 10133a00 PuzzleGame::GetSaveType(void)
uint32_t PuzzleGame::GetSaveType()
{
    return (uint32_t)0x0000002c;
}

// win1.41 00561b60 mac 10133a40 PuzzleGame::GetDebugText(void)
char* PuzzleGame::GetDebugText()
{
    return (char*)0x00bee2c0;
}

// win1.41 00561b70 mac 10133820 PuzzleGame::_dt(void)
PuzzleGame::~PuzzleGame()
{
}


void InfluenceRing::SetPlayer(GPlayer* param_1)
{
    *(unsigned int *)((char *)this + 0x34) = (unsigned int)param_1;
}


uint32_t GBaseOnly::GetSaveType()
{
    return (uint32_t)0xf6;
}

uint32_t TownCentreSpellIcon::GetSaveType()
{
    return (uint32_t)0x56;
}

uint32_t PlayerSubActionArgument::GetSaveType()
{
    return (uint32_t)0xfb;
}

uint32_t PlayerSubAction::GetSaveType()
{
    return (uint32_t)0xfa;
}

uint32_t PlayerActionState::GetSaveType()
{
    return (uint32_t)0xf9;
}

uint32_t GComputerAttitudeToPlayer::GetSaveType()
{
    return (uint32_t)0x10d;
}

uint32_t GComputerSeen::GetSaveType()
{
    return (uint32_t)0x67;
}

uint32_t GComputerPlayer::GetSaveType()
{
    return (uint32_t)0x66;
}

uint32_t GComputerPlayer::IsComputerPlayer()
{
    return (uint32_t)0x1;
}

bool32_t InfluenceRing::IsInfluenceRing()
{
    return (bool32_t)0x1;
}

const char* InfluenceRing::GetText()
{
    return (const char*)0xbed4e0;
}

GPlayer* InfluenceRing::GetPlayer()
{
    return (GPlayer*)*(unsigned int *)((char *)this + 0x34);
}

uint32_t InfluenceRing::GetSaveType()
{
    return (uint32_t)0x49;
}

char* InfluenceRing::GetDebugText()
{
    return (char*)0xbed4f0;
}

uint32_t RenderParticle::GetSaveType()
{
    return (uint32_t)0;
}

uint32_t BaseAtomModifierData::GetSaveType()
{
    return (uint32_t)0;
}

uint32_t BaseCollectionModifierData::GetSaveType()
{
    return (uint32_t)0;
}

char* BaseCollectionModifierData::GetDebugText()
{
    return (char*)0x9ceaa8;
}

uint32_t GComputerSpellCast::GetSaveType()
{
    return (uint32_t)0x68;
}

char* GComputerSpellCast::GetDebugText()
{
    return (char*)0xbee1f8;
}

uint32_t PuzzleLion::GetSaveType()
{
    return (uint32_t)0x2e;
}

char* PuzzleLion::GetDebugText()
{
    return (char*)0xbee214;
}

bool32_t PuzzleLion::CanBecomeAPhysicsObject()
{
    return (bool32_t)0;
}

uint32_t PuzzleVillager::GetSaveType()
{
    return (uint32_t)0x2f;
}

char* PuzzleVillager::GetDebugText()
{
    return (char*)0xbee224;
}

bool32_t PuzzleVillager::CanBecomeAPhysicsObject()
{
    return (bool32_t)0;
}

uint32_t PuzzleSheep::GetSaveType()
{
    return (uint32_t)0x2d;
}

char* PuzzleSheep::GetDebugText()
{
    return (char*)0xbee238;
}

bool32_t PuzzleSheep::CanBecomeAPhysicsObject()
{
    return (bool32_t)0;
}

uint32_t PuzzleTotem::GetSaveType()
{
    return (uint32_t)0x31;
}

char* PuzzleTotem::GetDebugText()
{
    return (char*)0xbee258;
}

uint32_t PuzzleGrain::GetSaveType()
{
    return (uint32_t)0x107;
}

char* PuzzleGrain::GetDebugText()
{
    return (char*)0xbee268;
}

bool32_t PuzzleGrain::NetworkUnfriendlyStartLockedSelect()
{
    return (bool32_t)0x1;
}

bool32_t PuzzleGrain::IsReadyForNetworkUnfriendlyLockedSelect()
{
    return (bool32_t)0x1;
}

bool32_t PuzzleGrain::GetReadyForNetworkUnfriendlyEndLockedSelect()
{
    return (bool32_t)0x1;
}

bool32_t PuzzleGrain::IsReadyForNetworkUnfriendlyEndLockedSelect()
{
    return (bool32_t)0x1;
}

bool32_t PuzzleGrain::NetworkUnfriendlyEndLockedSelect()
{
    return (bool32_t)0x1;
}

bool32_t PuzzleGrain::ValidAsInterfaceTarget()
{
    return (bool32_t)0x1;
}

void PuzzleGrain::Draw()
{
    MobileObject::Draw();
}

bool32_t PuzzleGrain::CanBecomeAPhysicsObject()
{
    return (bool32_t)0;
}

char* PuzzleMobileObject::GetDebugText()
{
    return (char*)0xbee29c;
}


bool32_t PuzzleGrain::CanBeEatenByCreature(Creature* param_1)
{
    return (bool32_t)0;
}

bool32_t PuzzleGrain::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)0;
}

bool32_t PuzzleGrain::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo* param_1)
{
    return (bool32_t)0x1;
}

bool32_t PuzzleGrain::NetworkFriendlyEndLockedSelect(GInterfaceStatus* param_1)
{
    return (bool32_t)0x1;
}

uint32_t PuzzleGrain::ValidToApplyThisToObject(GInterfaceStatus* param_1, Object* param_2)
{
    return (uint32_t)0;
}

bool32_t PuzzleGrain::InterfaceSetInMagicHand(GInterfaceStatus* param_1)
{
    return (bool32_t)0x1;
}

bool32_t PuzzleGrain::InterfaceSetOutMagicHand(GInterfaceStatus* param_1)
{
    return (bool32_t)0x1;
}

// ==== AUTOHARVEST ====
// AUTOHARVEST ?GetDebugText@GBaseOnly@@UAEPADXZ
char* GBaseOnly::GetDebugText()
{
    return (char*)0xbed298;
}

// AUTOHARVEST ?GetDebugText@TownCentreSpellIcon@@UAEPADXZ
char* TownCentreSpellIcon::GetDebugText()
{
    return (char*)0xbed3c8;
}

// AUTOHARVEST ?GetText@PlayerActionState@@UAEPBDXZ
const char* PlayerActionState::GetText()
{
    return (const char*)0xbed458;
}

// AUTOHARVEST ?GetDebugText@GComputerAttitudeToPlayer@@UAEPADXZ
char* GComputerAttitudeToPlayer::GetDebugText()
{
    return (char*)0xbed490;
}

// AUTOHARVEST ?GetDebugText@GComputerSeen@@UAEPADXZ
char* GComputerSeen::GetDebugText()
{
    return (char*)0xbed4ac;
}

// AUTOHARVEST ?GetDebugText@GComputerPlayer@@UAEPADXZ
char* GComputerPlayer::GetDebugText()
{
    return (char*)0xbed4bc;
}

// AUTOHARVEST ?GetDebugText@RenderParticle@@UAEPADXZ
char* RenderParticle::GetDebugText()
{
    return (char*)0x9ceaa8;
}

// AUTOHARVEST ?GetDebugText@BaseAtomModifierData@@UAEPADXZ
char* BaseAtomModifierData::GetDebugText()
{
    return (char*)0x9ceaa8;
}

