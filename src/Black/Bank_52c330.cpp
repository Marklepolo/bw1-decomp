#include "BuildingSite.h"
#include "EditingDebugBox.h"
#include "EndGameBox.h"
#include "FireFly.h"
#include "FishFarm.h"
#include "FishFarmInfo.h"
#include "Flock.h"
#include "Football.h"
#include "FootballPositionInfo.h"
#include "Footpath.h"
#include "FootpathFinder.h"
#include "FootpathLink.h"
#include "FootpathLinkSave.h"
#include "FootpathNode.h"
#include "Forest.h"
#include "ForestInfo.h"
#include "FrontEnd.h"
#include "GameOSFile.h"
#include "LoadingBox.h"
#include "MainMenu.h"
#include "MultiMapFixed.h"
#include "MultiMapFixedInfo.h"
#include "NewProfileBox.h"
#include "Object.h"
#include "Plasma.h"
#include "ProfileEditor.h"
#include "RegisterBox.h"
#include "SingleMapFixedInfo.h"
#include "SkipBox.h"
#include "TattooEditor.h"
#include "Villager.h"



// win1.41 0052c330 mac 100da430 GFishFarmInfo::_dt(void)
GFishFarmInfo::~GFishFarmInfo()
{
}

// win1.41 0052c450 mac 100dac20 FishFarm::GetTown(void)
Town* FishFarm::GetTown()
{
    return *(Town**)((char*)this + 0x0000008c);
}

// win1.41 0052c470 mac 100dc730 FishFarm::Get2DRadius(void)
float FishFarm::Get2DRadius()
{
    return 5.0f;
}

// win1.41 0052c490 mac inlined FishFarm::GetArrivePos(MapCoords *)
__declspec(naked) MapCoords* FishFarm::GetArrivePos(MapCoords* param_1)
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

// win1.41 0052c4b0 mac 100dd510 FishFarm::InteractsWithPhysicsObjects(void)
bool32_t FishFarm::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 0052c4c0 mac 100dd560 FishFarm::ConvertToPlanned(void)
PlannedMultiMapFixed* FishFarm::ConvertToPlanned()
{
    return (PlannedMultiMapFixed*)(0);
}

// win1.41 0052c4d0 mac 100dd5a0 FishFarm::GetCreatureBeliefType(void)
uint32_t FishFarm::GetCreatureBeliefType()
{
    return (uint32_t)0x0000000b;
}

// win1.41 0052c4e0 mac 100dd5e0 FishFarm::CanBePoodOn(Creature *)
bool32_t FishFarm::CanBePoodOn(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c4f0 mac 100dd620 FishFarm::CanBePickedUpByCreature(Creature *)
bool32_t FishFarm::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c500 mac 100dd670 FishFarm::CanBeStompedOnByCreature(Creature *)
bool32_t FishFarm::CanBeStompedOnByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c510 mac 100dd6c0 FishFarm::CanBeGivenToVillager(Creature *)
bool32_t FishFarm::CanBeGivenToVillager(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c520 mac 100dd710 FishFarm::CanBePutInAStoragePit(Creature *)
bool32_t FishFarm::CanBePutInAStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c530 mac 100dd760 FishFarm::CanBeDestroyedByStoning(Creature *)
bool32_t FishFarm::CanBeDestroyedByStoning(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c540 mac 100dd7b0 FishFarm::CanBeExaminedByCreature(Creature *)
bool32_t FishFarm::CanBeExaminedByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c550 mac 100dd800 FishFarm::CanBeEatenByCreature(Creature *)
bool32_t FishFarm::CanBeEatenByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0052c560 mac 100dd850 FishFarm::CanBeSleptNextToByCreature(Creature *)
bool32_t FishFarm::CanBeSleptNextToByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c570 mac 100dd8a0 FishFarm::IsBeingBuilt(Creature *)
bool32_t FishFarm::IsBeingBuilt(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c580 mac 100dd8e0 FishFarm::NeedsRepair(Creature *)
bool32_t FishFarm::NeedsRepair(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052c590 mac 100dd920 FishFarm::IsLockedInInteract(void)
bool32_t FishFarm::IsLockedInInteract()
{
    return (bool32_t)0x00000001;
}

// win1.41 0052c5a0 mac 100dd960 FishFarm::GetSaveType(void)
uint32_t FishFarm::GetSaveType()
{
    return (uint32_t)0x0000005b;
}

// win1.41 0052c5b0 mac 100dd9a0 FishFarm::GetDebugText(void)
char* FishFarm::GetDebugText()
{
    return (char*)0x00be9e24;
}

// win1.41 0052c5c0 mac 100dcf40 FishFarm::_dt(void)
FishFarm::~FishFarm()
{
}

// win1.41 0052c830 mac 10025a30 FishFarm::Draw(void)
void FishFarm::Draw()
{
}

// win1.41 0052c840 mac 100dc810 FishFarm::GetHeightForHandAboveInteractObject(void)
float FishFarm::GetHeightForHandAboveInteractObject()
{
    return 5.0f;
}

// win1.41 0052d760 mac 100dac50 FishFarm::GetResourceType(void)
RESOURCE_TYPE FishFarm::GetResourceType()
{
    return (RESOURCE_TYPE)0;
}

// win1.41 0052d880 mac 100da930 FishFarm::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo *)
bool32_t FishFarm::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0052d890 mac 100da8e0 FishFarm::NetworkUnfriendlyEndLockedSelect(void)
bool32_t FishFarm::NetworkUnfriendlyEndLockedSelect()
{
    return (bool32_t)(0);
}

// win1.41 0052dce0 mac 100e3150 GSingleMapFixedInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GSingleMapFixedInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000004;
    return (GBaseInfo*)0x00ccfdb8;
}

// win1.41 0052e140 mac 100e17b0 FixedObject::Save(GameOSFile &)
bool32_t Fixed::Save(GameOSFile& file)
{
    if (Object::Save(file))
    {
        file.GameOSFile::WritePtr(town_artifact);
        return true;
    }
    return false;
}

// win1.41 0052e480 mac 100e0e80 MultiMapFixed::IsObjectInMap(void)
bool32_t MultiMapFixed::IsObjectInMap()
{
    return *(uint8_t*)((char*)this + 0x24) & 1;
}

// win1.41 0052ec60 mac 100dfd40 MultiMapFixed::StartOnFire(void)
extern "C" void jmp_addr_0x006e4750(void);
__declspec(naked) void MultiMapFixed::StartOnFire()
{
    __asm {
            push ecx
            call jmp_addr_0x006e4750
            pop ecx
            ret
        }
}

// win1.41 0052efc0 mac 100dedd0 MultiMapFixed::GetPercentRepairedForNonFunctional(void)
float MultiMapFixed::GetPercentRepairedForNonFunctional()
{
    return 0.75f;
}

// win1.41 0052f0c0 mac 10040f00 MultiMapFixed::IsDrawBuilding(void)
bool32_t MultiMapFixed::IsDrawBuilding()
{
    return *(uint32_t*)((char*)this + 0x74) != 0;
}

// win1.41 0052f250 mac 100de470 MultiMapFixed::Save(GameOSFile &)
bool32_t MultiMapFixed::Save(GameOSFile& file)
{
    if (Fixed::Save(file))
    {
        GameOSFileWriteCheckSum(file, field_0x58);
        GameOSFileWriteCheckSum(file, percent_built);         
        file.WritePtr(footpath_link);
        file.WritePtr(building_site);
        return true;
    }
    return false;
}

// win1.41 0052f870 mac 100e34e0 Flock::GetTown(void)
Town* Flock::GetTown()
{
    return *(Town**)((char*)this + 0x34);
}

// win1.41 0052f890 mac 100e3550 Flock::GetText(void)
const char* Flock::GetText()
{
    return (const char*)0x00be9efc;
}

// win1.41 0052f8a0 mac 100e3580 Flock::GetCreatureBeliefType(void)
uint32_t Flock::GetCreatureBeliefType()
{
    return (uint32_t)0x00000016;
}

// win1.41 0052f8b0 mac 100e35c0 Flock::GetCreatureBeliefListType(void)
uint32_t Flock::GetCreatureBeliefListType()
{
    return (uint32_t)(0);
}

// win1.41 0052f8c0 mac 100e3600 Flock::IsSuitableForCreatureActivity(void)
bool32_t Flock::IsSuitableForCreatureActivity()
{
    return (bool32_t)0x00000001;
}

// win1.41 0052f8d0 mac 100e3650 Flock::IsActivityObjectWhichAngerAppliesTo(Creature *)
bool32_t Flock::IsActivityObjectWhichAngerAppliesTo(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0052f8e0 mac 100e36b0 Flock::IsActivityObjectWhichCompassionAppliesTo(Creature *)
bool32_t Flock::IsActivityObjectWhichCompassionAppliesTo(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0052f8f0 mac 100e3710 Flock::IsActivityObjectWhichPlayfulnessAppliesTo(Creature *)
bool32_t Flock::IsActivityObjectWhichPlayfulnessAppliesTo(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 0052f900 mac 100e3770 Flock::GetSaveType(void)
uint32_t Flock::GetSaveType()
{
    return (uint32_t)0x0000007e;
}

// win1.41 0052f910 mac 100e37a0 Flock::GetDebugText(void)
char* Flock::GetDebugText()
{
    return (char*)0x00be9f04;
}

// win1.41 0052f920 mac 100e3420 Flock::_dt(void)
Flock::~Flock()
{
}

// win1.41 00530490 mac 100e4a70 Flock::GetScriptObjectType(void)
uint32_t Flock::GetScriptObjectType()
{
    return (uint32_t)0x0000000b;
}

// win1.41 00530f00 mac 102bd7f0 GFootballPositionInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GFootballPositionInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x0000000a;
    return (GBaseInfo*)0x00cd01e0;
}

// win1.41 00530f60 mac 102bcb80 GFootballPositionInfo::_dt(void)
GFootballPositionInfo::~GFootballPositionInfo()
{
}

// win1.41 00531180 mac 102bd4d0 Football::GetCreatureBeliefType(void)
uint32_t Football::GetCreatureBeliefType()
{
    return (uint32_t)0x0000000f;
}

// win1.41 00531290 mac 102b8650 Football::IsRepaired(void)  [?IsRepaired@Football@@UAEIXZ]
// TECH: call [vptr+0x884] = the virtual GetPercentRepaired() (returns float), compared >= 1.0f via the
// fcomp [const]/fnstsw/test ah,1 idiom; eax=1 iff repaired>=100%, else 0.
// GAME: a football is "repaired" exactly when its repair fraction reaches full (1.0) -- i.e. it is never
// damaged-but-usable; the predicate gates whatever logic only acts on fully-intact balls.
bool32_t Football::IsRepaired()
{
    return GetPercentRepaired() >= 1.0f;
}

// win1.41 00531280 mac 102b8610 Football::IsFootball(void)
bool32_t Football::IsFootball()
{
    return (bool32_t)0x00000001;
}

// win1.41 00531310 mac 102b8830 Football::GetSaveType(void)
uint32_t Football::GetSaveType()
{
    return (uint32_t)0x00000045;
}

// win1.41 00531320 mac 102b8870 Football::GetDebugText(void)
char* Football::GetDebugText()
{
    return (char*)0x00be9f98;
}

// win1.41 00531330 mac 102b8570 Football::_dt(void)
Football::~Football()
{
}

// win1.41 00534d50 mac 100eeff0 GFootpathNode::GetSaveType(void)
uint32_t GFootpathNode::GetSaveType()
{
    return (uint32_t)0x00000003;
}

// win1.41 00534d60 mac 100ef030 GFootpathNode::GetDebugText(void)
char* GFootpathNode::GetDebugText()
{
    return (char*)0x00bea15c;
}

// win1.41 00534d70 mac 100eef60 GFootpathNode::_dt(void)
GFootpathNode::~GFootpathNode()
{
}

// win1.41 00534de0 mac 100ef210 GFootpath::GetSaveType(void)
uint32_t GFootpath::GetSaveType()
{
    return (uint32_t)0x00000001;
}

// win1.41 00534df0 mac 100ef250 GFootpath::GetDebugText(void)
char* GFootpath::GetDebugText()
{
    return (char*)0x00bea188;
}

// win1.41 00534e00 mac 100eeb80 GFootpath::_dt(void)
GFootpath::~GFootpath()
{
}

// win1.41 005371e0 mac 100ef0b0 GFootpathLinkSave::GetDebugText(void)
char* GFootpathLinkSave::GetDebugText()
{
    return (char*)0x00bea1e0;
}

// win1.41 005371f0 mac 100eb6b0 GFootpathLinkSave::_dt(void)
GFootpathLinkSave::~GFootpathLinkSave()
{
}

// win1.41 00538ea0 mac 100e83b0 GFootpathNode::ResolveLoad(void)
void GFootpathNode::ResolveLoad()
{
}

// win1.41 00538fd0 mac 100e70d0 GFootpathFinder::GetSaveType(void)
uint32_t GFootpathFinder::GetSaveType()
{
    return (uint32_t)0x00000005;
}

// win1.41 00538fe0 mac 100e7110 GFootpathFinder::GetDebugText(void)
char* GFootpathFinder::GetDebugText()
{
    return (char*)0x00bea220;
}

// win1.41 00538ff0 mac 100e7f30 GFootpathFinder::_dt(void)
GFootpathFinder::~GFootpathFinder()
{
}

// win1.41 00539a80 mac 100ef580 Forest::GetCreatureBeliefType(void)
uint32_t Forest::GetCreatureBeliefType()
{
    return (uint32_t)0x00000001;
}

// win1.41 00539a90 mac 100ef5c0 Forest::GetCreatureBeliefListType(void)
uint32_t Forest::GetCreatureBeliefListType()
{
    return (uint32_t)(0);
}

// win1.41 00539aa0 mac 100ef600 Forest::IsSuitableForCreatureActivity(void)
bool32_t Forest::IsSuitableForCreatureActivity()
{
    return (bool32_t)0x00000001;
}

// win1.41 00539ab0 mac 100ef650 Forest::IsActivityObjectWhichAngerAppliesTo(Creature *)
bool32_t Forest::IsActivityObjectWhichAngerAppliesTo(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00539ac0 mac 100ef6b0 Forest::GetText(void)
const char* Forest::GetText()
{
    return (const char*)0x00bea25c;
}

// win1.41 00539ad0 mac 100ef6e0 Forest::IsForest(void)
bool32_t Forest::IsForest()
{
    return (bool32_t)0x00000001;
}

// win1.41 00539ae0 mac 100ef710 Forest::IsFootpathLink(void)
bool32_t Forest::IsFootpathLink()
{
    return (bool32_t)0x00000001;
}

// win1.41 00539af0 mac 100ef750 Forest::GetFootpathLink(void)
GFootpathLink* Forest::GetFootpathLink()
{
    return *(GFootpathLink**)((char*)this + 0x30);
}

// win1.41 00539b00 mac 100ef790 Forest::GetSaveType(void)
uint32_t Forest::GetSaveType()
{
    return (uint32_t)0x0000004e;
}

// win1.41 00539b10 mac 100ef7d0 Forest::GetDebugText(void)
char* Forest::GetDebugText()
{
    return (char*)0x00bea264;
}

// win1.41 0053acf0 mac 100f07e0 Forest::GetNearestPathTo(MapCoords const &, float, int)
uint32_t Forest::GetNearestPathTo(const MapCoords& param_1, float param_2, int param_3)
{
    return (uint32_t)(0);
}

// win1.41 0053bd10 mac 105c5f90 NewProfileBox::CanESCOut(void)
bool32_t NewProfileBox::CanESCOut()
{
    __asm { xor al, al }
}

// win1.41 0053bd20 mac 105c5eb0 TattooEditor::CanESCOut(void)
bool32_t TattooEditor::CanESCOut()
{
    __asm { xor al, al }
}

// win1.41 0053bd50 mac 105c5ef0 MainMenu::CanESCOut(void)
bool32_t MainMenu::CanESCOut()
{
    __asm { xor al, al }
}


void Football::Draw()
{
    MultiMapFixed::Draw();
}


bool32_t Football::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}
