#include "BWGameSpy.h"
#include "Ball.h"
#include "BallInfo.h"
#include "Base.h"
#include "BaseInfo.h"
#include "Belief.h"
#include "BeliefInfo.h"
#include "BigForest.h"
#include "BigForestInfo.h"
#include "Bonfire.h"
#include "BuildingSite.h"
#include "CitadelBuildingSite.h"
#include "MagicCreatureSpellInfo.h"
#include "MagicFlockFlyingInfo.h"
#include "MagicFlockGroundInfo.h"
#include "MagicForestInfo.h"
#include "MagicHealInfo.h"
#include "MagicInfo.h"
#include "MagicObjectInfo.h"
#include "MagicRadiusSpellInfo.h"
#include "MagicResourceInfo.h"
#include "MagicShieldInfo.h"
#include "MagicStormAndTornadoInfo.h"
#include "MagicTeleportInfo.h"
#include "MagicWaterInfo.h"
#include "MapCoords.h"
#include "MobileStatic.h"
#include "MultiMapFixed.h"
#include "Rock.h"
#include "StandardBuildingSite.h"
#include "WorkshopBuildingSite.h"
#include "lhall/released/headers/LHTimer.h"



// win1.41 00435680 mac 1018ee20 GMagicInfo::_dt(void)
GMagicInfo::~GMagicInfo()
{
}

// win1.41 004356a0 mac 103ae460 GMagicHealInfo::_dt(void)
GMagicHealInfo::~GMagicHealInfo()
{
}

// win1.41 004356c0 mac 103b2190 GMagicTeleportInfo::_dt(void)
GMagicTeleportInfo::~GMagicTeleportInfo()
{
}

// win1.41 004356e0 mac 103ac990 GMagicForestInfo::_dt(void)
GMagicForestInfo::~GMagicForestInfo()
{
}

// win1.41 00435700 mac 103ac8f0 GMagicResourceInfo::_dt(void)
GMagicResourceInfo::~GMagicResourceInfo()
{
}

// win1.41 00435740 mac 103aebf0 GMagicStormAndTornadoInfo::_dt(void)
GMagicStormAndTornadoInfo::~GMagicStormAndTornadoInfo()
{
}

// win1.41 00435780 mac 103aeca0 GMagicShieldInfo::_dt(void)
GMagicShieldInfo::~GMagicShieldInfo()
{
}

// win1.41 004357a0 mac 103ac480 GMagicWaterInfo::_dt(void)
GMagicWaterInfo::~GMagicWaterInfo()
{
}

// win1.41 004357c0 mac 1051ed80 GMagicFlockFlyingInfo::_dt(void)
GMagicFlockFlyingInfo::~GMagicFlockFlyingInfo()
{
}

// win1.41 004357e0 mac 1051ece0 GMagicFlockGroundInfo::_dt(void)
GMagicFlockGroundInfo::~GMagicFlockGroundInfo()
{
}

// win1.41 00435800 mac 103aba10 GMagicCreatureSpellInfo::_dt(void)
GMagicCreatureSpellInfo::~GMagicCreatureSpellInfo()
{
}

// win1.41 00435830 mac 1018fa30 GMagicObjectInfo::_dt(void)
GMagicObjectInfo::~GMagicObjectInfo()
{
}

// win1.41 00435850 mac 10190190 GMagicRadiusSpellInfo::_dt(void)
GMagicRadiusSpellInfo::~GMagicRadiusSpellInfo()
{
}

// win1.41 00435930 mac 100b1090 GBallInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GBallInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000001;
    return (GBaseInfo*)0x00c58498;
}

// win1.41 00435980 mac 100b0ff0 GBallInfo::_dt(void)
GBallInfo::~GBallInfo()
{
}

// win1.41 00435ab0 mac 100aff50 Ball::CanBePickedUpByCreature(Creature *)
bool32_t Ball::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00435ac0 mac 100affa0 Ball::GetSaveType(void)
uint32_t Ball::GetSaveType()
{
    return (uint32_t)0x00000044;
}

// win1.41 00435ad0 mac 100affd0 Ball::GetDebugText(void)
char* Ball::GetDebugText()
{
    return (char*)0x009cd084;
}

// win1.41 00435ae0 mac 100b0b20 Ball::_dt(void)
Ball::~Ball()
{
}

// win1.41 00435c30 mac 100b0970 Ball::Process(void)
uint32_t Ball::Process()
{
    return (uint32_t)0x00000001;
}

// win1.41 004360f0 mac 100b0490 Ball::GetPhysicsConstantsType(void)
uint32_t Ball::GetPhysicsConstantsType()
{
    return (uint32_t)0x00000002;
}

// win1.41 00436100 mac 100b0450 Ball::GetScriptObjectType(void)
uint32_t Ball::GetScriptObjectType()
{
    return (uint32_t)0x0000001c;
}

// win1.41 004363b0 mac 100b0040 Ball::IsToy(Creature *)
bool32_t Ball::IsToy(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 004363c0 mac 100b0000 Ball::IsToyBall(Creature *)
bool32_t Ball::IsToyBall(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00436bd0 mac 1035b720 GBaseInfo::SetInfoID(void)
extern "C" char UINT_00c58604[];
extern "C" char game[];
__declspec(naked) void GBaseInfo::SetInfoID()
{
    __asm {
            mov eax, dword ptr [UINT_00c58604]
            mov dword ptr [ecx + 0x0c], eax
            inc dword ptr [UINT_00c58604]
            mov edx, dword ptr [game]
            lea eax, dword ptr [edx + 0x00205cec]
            mov edx, dword ptr [eax]
            mov dword ptr [ecx + 0x08], edx
            mov dword ptr [eax], ecx
            inc dword ptr [eax + 0x04]
            ret
        }
}

// win1.41 00437d60 mac 100b2260 GBeliefInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GBeliefInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000001;
    return (GBaseInfo*)0x00c58640;
}

// win1.41 00437db0 mac 100b22b0 GBeliefInfo::_dt(void)
GBeliefInfo::~GBeliefInfo()
{
}

// win1.41 00437e70 mac 00437e70 GBelief::GetBeliefInPlayer(unsigned long)
float GBelief::GetBeliefInPlayer(unsigned long param_1)
{
    return *(float*)((char*)this + param_1 * 4 + 0x8);
}

// win1.41 00438cb0 mac 100b33d0 GBigForestInfo::_dt(void)
GBigForestInfo::~GBigForestInfo()
{
}

// win1.41 00438d70 mac 10368f30 MultiMapFixed::IsRepaired(void)
bool32_t MultiMapFixed::IsRepaired()
{
    return (bool32_t)0x00000001;
}

// win1.41 00438d80 mac 10570e90 MultiMapFixed::IsBuilt(void)
bool32_t MultiMapFixed::IsBuilt()
{
    return (bool32_t)0x00000001;
}

// win1.41 00438d90 mac 100b25f0 MultiMapFixed::ConvertToPlanned(void)
PlannedMultiMapFixed* MultiMapFixed::ConvertToPlanned()
{
    return (PlannedMultiMapFixed*)(0);
}

// win1.41 00438db0 mac 100b2390 BigForest::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t BigForest::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00438dc0 mac 100b23e0 BigForest::IsTuggable(void)
bool32_t BigForest::IsTuggable()
{
    return (bool32_t)(0);
}

// win1.41 00438dd0 mac 100b2420 BigForest::VillagerMustAvoid(Villager *)
bool32_t BigForest::VillagerMustAvoid(Villager* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00438de0 mac 100b2470 BigForest::GetCarriedTreeType(void)
uint32_t BigForest::GetCarriedTreeType()
{
    return *(uint32_t*)(*(char**)((char*)this + 0x28) + 0x00000124);
}

// win1.41 00438e10 mac 100b25b0 BigForest::GetDebugText(void)
char* BigForest::GetDebugText()
{
    return (char*)0x009cd2f8;
}

// win1.41 00438e20 mac 100b3990 BigForest::_dt(void)
BigForest::~BigForest()
{
}

// win1.41 00438f60 mac 10020e40 BigForest::Draw(void)
void BigForest::Draw()
{
    MultiMapFixed::Draw();
}

// win1.41 004390a0 mac 100b3050 BigForest::InteractsWithPhysicsObjects(void)
bool32_t BigForest::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00439610 mac 100b40c0 MobileStatic::GetXAngle(void)
float MobileStatic::GetXAngle()
{
    return *(float*)((char*)this + 0x00000080);
}

// win1.41 00439620 mac 100b4100 MobileStatic::GetZAngle(void)
float MobileStatic::GetZAngle()
{
    return *(float*)((char*)this + 0x00000084);
}

// win1.41 00439630 mac 100b4140 MobileStatic::CanBeStompedOnByCreature(Creature *)
bool32_t MobileStatic::CanBeStompedOnByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00439640 mac 100b4190 MobileStatic::CanBePlayedWithByCreature(Creature *)
bool32_t MobileStatic::CanBePlayedWithByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00439650 mac 100b41e0 MobileStatic::CanBeThrownInTheSeaPlayfully(Creature *)
bool32_t MobileStatic::CanBeThrownInTheSeaPlayfully(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00439660 mac 100b4240 MobileStatic::GetTastiness(void)
uint32_t MobileStatic::GetTastiness()
{
    return (uint32_t)(0);
}

// win1.41 00439670 mac 100b4280 MobileStatic::CanBePickedUp(void)
bool32_t MobileStatic::CanBePickedUp()
{
    return ((uint16_t)~*(uint16_t*)((char*)this + 0x24) >> 0xd) & 1;
}

// win1.41 004396a0 mac 100b4460 MobileStatic::IsFunctional(void)
bool32_t MobileStatic::IsFunctional()
{
    return this->IsAvailable();
}

// win1.41 004396f0 mac 100b4610 MobileStatic::IsMobileStatic(void)
bool32_t MobileStatic::IsMobileStatic()
{
    return (bool32_t)0x00000001;
}

// win1.41 00439700 mac 100b4650 MobileStatic::IsCastShadowAtNight(void)
bool32_t MobileStatic::IsCastShadowAtNight()
{
    return (bool32_t)0x00000001;
}

// win1.41 00439720 mac 100b3f50 Rock::SetPlayer(GPlayer *)
void Rock::SetPlayer(GPlayer* param_1)
{
    *(uint32_t*)((char*)this + 0x00000090) = (uint32_t)param_1;
}

// win1.41 00439730 mac inlined Rock::IsRock_0(void)
bool32_t Rock::IsRock()
{
    return (bool32_t)0x00000001;
}

// win1.41 00439740 mac 100b3fc0 Rock::IsMovable(void)
bool32_t Rock::IsMovable()
{
    return (bool32_t)0x00000001;
}

// win1.41 00439750 mac 100b3ff0 Rock::GetCreatureMimicType(void)
uint32_t Rock::GetCreatureMimicType()
{
    return (uint32_t)0x00000007;
}

// win1.41 00439760 mac 100b4030 Rock::CanBeAttackedByCreature(Creature *)
bool32_t Rock::CanBeAttackedByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00439770 mac 100b4080 Rock::ShouldFootpathsGoRound(void)
bool32_t Rock::ShouldFootpathsGoRound()
{
    return (bool32_t)0x00000001;
}

// win1.41 00439780 mac 100b3ca0 Bonfire::InterfaceValidToTap(GInterfaceStatus *)
uint32_t Bonfire::InterfaceValidToTap(GInterfaceStatus* param_1)
{
    return (uint32_t)(0);
}

// win1.41 00439790 mac 100b3cf0 Bonfire::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t Bonfire::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return (bool32_t)(0);
}

// win1.41 004397a0 mac 100b3d40 Bonfire::CanBecomeAPhysicsObject(void)
bool32_t Bonfire::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 004397b0 mac 100b3d80 Bonfire::InteractsWithPhysicsObjects(void)
bool32_t Bonfire::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 004397c0 mac 100b3dd0 Bonfire::PhysicsEditorCreate(int)
void Bonfire::PhysicsEditorCreate(int param_1)
{
    *(uint32_t*)((char*)this + 0x1c) = 0x00000000;
}

// win1.41 004397e0 mac 100b3e80 Bonfire::GetSaveType(void)
uint32_t Bonfire::GetSaveType()
{
    return (uint32_t)0x00000072;
}

// win1.41 004397f0 mac 100b3ec0 Bonfire::GetDebugText(void)
char* Bonfire::GetDebugText()
{
    return (char*)0x009cd358;
}

// win1.41 00439800 mac 100b3c10 Bonfire::_dt(void)
Bonfire::~Bonfire()
{
}

// win1.41 00439a80 mac 100b4750 Bonfire::ReactToPhysicsImpact(PhysicsObject *, bool)
void Bonfire::ReactToPhysicsImpact(PhysicsObject* param_1, bool param_2)
{
}

// win1.41 00439a90 mac 1001a450 Bonfire::Draw(void)
void Bonfire::Draw()
{
    Rock::Draw();
}

// win1.41 0043b7a0 mac 100be420 BuildingSite::GetSaveType(void)
uint32_t BuildingSite::GetSaveType()
{
    return (uint32_t)(0);
}

// win1.41 0043b7b0 mac 100bcd40 BuildingSite::_dt(void)
BuildingSite::~BuildingSite()
{
}

// win1.41 0043b950 mac 100bcd10 BuildingSite::Init(void)
void BuildingSite::Init()
{
}

// win1.41 0043bca0 mac 1006caf0 BuildingSite::GetRootBuilding(void)
MultiMapFixed* BuildingSite::GetRootBuilding()
{
    return *(MultiMapFixed**)((char*)this + 0x14);
}

// win1.41 0043d180 mac 100b9190 CitadelBuildingSite::SetPileWood(Pot *)
void CitadelBuildingSite::SetPileWood(Pot* param_1)
{
}

// win1.41 0043d190 mac 100be340 CitadelBuildingSite::GetSaveType(void)
uint32_t CitadelBuildingSite::GetSaveType()
{
    return (uint32_t)0x0000005d;
}

// win1.41 0043d1a0 mac 100be380 CitadelBuildingSite::GetDebugText(void)
char* CitadelBuildingSite::GetDebugText()
{
    return (char*)0x009cd454;
}

// win1.41 0043d460 mac 100b8b60 CitadelBuildingSite::CreatePileWood(void)
void CitadelBuildingSite::CreatePileWood()
{
}

// win1.41 0043d5b0 mac 100b86c0 CitadelBuildingSite::RemovePotFromStructure(PotStructure *)
__declspec(naked) void CitadelBuildingSite::RemovePotFromStructure(PotStructure* param_1)
{
    __asm {
            _emit 0x8b
            _emit 0x54
            _emit 0x24
            _emit 0x04
            _emit 0x8d
            _emit 0x81
            _emit 0x44
            _emit 0x06
            _emit 0x00
            _emit 0x00
            _emit 0xb9
            _emit 0x06
            _emit 0x00
            _emit 0x00
            _emit 0x00
            _emit 0x39
            _emit 0x10
            _emit 0x75
            _emit 0x06
            _emit 0xc7
            _emit 0x00
            _emit 0x00
            _emit 0x00
            _emit 0x00
            _emit 0x00
            _emit 0x83
            _emit 0xc0
            _emit 0x04
            _emit 0x49
            _emit 0x75
            _emit 0xf0
            _emit 0xc2
            _emit 0x04
            _emit 0x00
        }
}

// win1.41 0043d6f0 mac 100b8130 StandardBuildingSite::SetPileWood(Pot *)
void StandardBuildingSite::SetPileWood(Pot* param_1)
{
    *(uint32_t*)((char*)this + 0x00000644) = (uint32_t)param_1;
}

// win1.41 0043d700 mac 100be220 StandardBuildingSite::GetSaveType(void)
uint32_t StandardBuildingSite::GetSaveType()
{
    return (uint32_t)0x0000005c;
}

// win1.41 0043d710 mac 100be260 StandardBuildingSite::GetDebugText(void)
char* StandardBuildingSite::GetDebugText()
{
    return (char*)0x009cd494;
}

// win1.41 0043d720 mac 100b8360 StandardBuildingSite::_dt(void)
StandardBuildingSite::~StandardBuildingSite()
{
}

// win1.41 0043d970 mac 100b7a40 WorkshopBuildingSite::_dt(void)
WorkshopBuildingSite::~WorkshopBuildingSite()
{
}


bool Ball::IsBallFree()
{
    return *(unsigned int *)((char *)this + 0x90) == 0;
}


IMMERSION_EFFECT_TYPE Bonfire::GetInHandImmersionTexture()
{
    return Object::GetInHandImmersionTexture();
}

uint32_t Bonfire::GetScriptObjectType()
{
    return MobileStatic::GetScriptObjectType();
}
