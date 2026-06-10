#include "Alignment.h"
#include "Creature.h"
#include "CreatureInfo.h"
#include "CreaturePlan.h"
#include "CreatureSubAction.h"
#include "DifferentCreatureInfo.h"
#include "Living.h"
#include "Mobile.h"
#include "MobileWallHug.h"
#include "Villager.h"



// win1.41 00472c80 mac 101d2300 CreatureInfo::_dt(void)
CreatureInfo::~CreatureInfo()
{
}

// win1.41 00472cf0 mac 101e2a50 DifferentCreatureInfo::GetBaseInfo(unsigned long &)
GBaseInfo* DifferentCreatureInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000011;
    return (GBaseInfo*)0x00c5fd30;
}

// win1.41 00472d50 mac 101d2170 DifferentCreatureInfo::_dt(void)
DifferentCreatureInfo::~DifferentCreatureInfo()
{
}

// win1.41 00473b70 mac 10278860 CreaturePlan::_dt(void)
CreaturePlan::~CreaturePlan()
{
}

// win1.41 00473dd0 mac 101deb60 CreatureSubAction::_dt(void)
CreatureSubAction::~CreatureSubAction()
{
}

// win1.41 00473e50 mac 101e3470 Living::SetStateSpeed(void)
void Living::SetStateSpeed()
{
}

// win1.41 00473ea0 mac 101e35d0 Living::SetupReactToFallingTree(GameThingWithPos *, Reaction *)
void Living::SetupReactToFallingTree(GameThingWithPos* param_1, Reaction* param_2)
{
}

// win1.41 00473eb0 mac 101e3630 Living::ReactToDroppedByHandPriority(Reaction *, Reaction *)
uint8_t Living::ReactToDroppedByHandPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 00473ec0 mac 101e3690 Living::ReactToFallingTreePriority(Reaction *, Reaction *)
uint8_t Living::ReactToFallingTreePriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 00473ed0 mac 101e36f0 Living::IsChild(void)
bool32_t Living::IsChild()
{
    return (bool32_t)(0);
}

// win1.41 00473ef0 mac 101e2be0 Creature::GetAnimId(void)
ANIM_LIST Creature::GetAnimId()
{
    return (ANIM_LIST)-1;
}

// win1.41 00473f00 mac inlined Creature::CallIntoAnimationFunction(VILLAGER_STATES)
int Creature::CallIntoAnimationFunction(VILLAGER_STATES param_1)
{
    return (int)(-1);
}

// win1.41 00473f10 mac inlined Creature::CallOutofAnimationFunction(VILLAGER_STATES)
int Creature::CallOutofAnimationFunction(VILLAGER_STATES param_1)
{
    return (int)(-1);
}

// win1.41 00473f20 mac 100a0db0 Creature::GetPlayer(void)
GPlayer* Creature::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x00001070);
}

// win1.41 00473f30 mac 101e2cc0 Creature::RemoveDance(void)
void Creature::RemoveDance()
{
    *(uint32_t*)((char*)this + 0x00001074) = 0x00000000;
}

// win1.41 00473f50 mac 101e2d40 Creature::IsReachable(void)
bool32_t Creature::IsReachable()
{
    return (bool32_t)(0);
}

// Creature self-as-activity-target predicates (self-class Creature* param -> mangles PAV1@ back-ref).
// win1.41 00474020 Creature::IsActivityObjectWhichCompassionAppliesTo(Creature *)
bool32_t Creature::IsActivityObjectWhichCompassionAppliesTo(Creature* param_1) { return (bool32_t)(1); }
// win1.41 00474030 Creature::IsActivityObjectWhichPlayfulnessAppliesTo(Creature *)
bool32_t Creature::IsActivityObjectWhichPlayfulnessAppliesTo(Creature* param_1) { return (bool32_t)(1); }
// win1.41 00474040 Creature::CanBeSleptNextToByCreature(Creature *)
bool32_t Creature::CanBeSleptNextToByCreature(Creature* param_1) { return (bool32_t)(1); }
// win1.41 00474050 Creature::CanBeEatenByCreature(Creature *)
bool32_t Creature::CanBeEatenByCreature(Creature* param_1) { return (bool32_t)(0); }
// win1.41 00474060 Creature::CanBeBefriendedByCreature(Creature *)
bool32_t Creature::CanBeBefriendedByCreature(Creature* param_1) { return (bool32_t)(1); }
// win1.41 00474070 Creature::CanBePlayedWithByCreature(Creature *)
bool32_t Creature::CanBePlayedWithByCreature(Creature* param_1) { return (bool32_t)(1); }
// win1.41 00474090 Creature::IsCreature(Creature *)
bool32_t Creature::IsCreature(Creature* param_1) { return (bool32_t)(1); }

// win1.41 00473f60 mac 101e2d80 Creature::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t Creature::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00473f70 mac 101e2dd0 Creature::GetCreatureBeliefType(void)
uint32_t Creature::GetCreatureBeliefType()
{
    return (uint32_t)0x00000008;
}

// win1.41 00473f80 mac 101e2e10 Creature::GetCreatureMimicType(void)
uint32_t Creature::GetCreatureMimicType()
{
    return (uint32_t)0x00000009;
}

// win1.41 00473f90 mac inlined Creature::SetAnim__i(int)
void Creature::SetAnim__i(int param_1)
{
}

// win1.41 00473fa0 mac inlined Creature::CallExitStateFunction(VILLAGER_STATES)
uint32_t Creature::CallExitStateFunction(VILLAGER_STATES param_1)
{
    return (uint32_t)0x00000001;
}

// win1.41 00473fd0 mac 101e2f50 Creature::IsSuitableForCreatureActivity(void)
bool32_t Creature::IsSuitableForCreatureActivity()
{
    return (bool32_t)0x00000001;
}

// win1.41 00473fe0 mac 101e2fa0 Creature::CanBePickedUp(void)
bool32_t Creature::CanBePickedUp()
{
    return (bool32_t)0x00000001;
}

// win1.41 004740c0 mac 101e33f0 Creature::GetSaveType(void)
uint32_t Creature::GetSaveType()
{
    return (uint32_t)0x00000069;
}

// win1.41 004740d0 mac 101e3430 Creature::GetDebugText(void)
char* Creature::GetDebugText()
{
    return (char*)0x009cfa20;
}

// win1.41 004740e0 mac 101debf0 GAlignment::_dt(void)
GAlignment::~GAlignment()
{
}

// win1.41 00474100 mac 101de750 Creature::_dt(void)
Creature::~Creature()
{
}

// win1.41 00474910 mac 103c19a0 MobileWallHug::_dt(void)
MobileWallHug::~MobileWallHug()
{
}

// win1.41 00474940 mac 103838c0 Living::DecideWhatToDo(void)
bool32_t Living::DecideWhatToDo()
{
    return (bool32_t)(0);
}

// win1.41 00474950 mac 10383900 Living::SetupReactToFire(GameThingWithPos *, Reaction *)
void Living::SetupReactToFire(GameThingWithPos* param_1, Reaction* param_2)
{
}

// win1.41 00474960 mac 10383950 Living::ReactToFirePriority(Reaction *, Reaction *)
uint8_t Living::ReactToFirePriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 00474970 mac 10148240 Living::ReactToHandPickUpPriority(Reaction *, Reaction *)
uint8_t Living::ReactToHandPickUpPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 00474980 mac 101482a0 Living::ReactToHandUsingTotemPriority(Reaction *, Reaction *)
uint8_t Living::ReactToHandUsingTotemPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 00474990 mac 10148300 Living::ReactToObjectCrushedPriority(Reaction *, Reaction *)
uint8_t Living::ReactToObjectCrushedPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 004749a0 mac 103839a0 Living::ReactToFightPriority(Reaction *, Reaction *)
uint8_t Living::ReactToFightPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 004749b0 mac 103839f0 Living::ReactToTeleportPriority(Reaction *, Reaction *)
uint8_t Living::ReactToTeleportPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 004749c0 mac 10148360 Living::ReactToHandPuttingStuffInStoragePitPriority(Reaction *, Reaction *)
uint8_t Living::ReactToHandPuttingStuffInStoragePitPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 004749d0 mac 10383a40 Living::ReactToDeathPriority(Reaction *, Reaction *)
uint8_t Living::ReactToDeathPriority(Reaction* param_1, Reaction* param_2)
{
    return (uint8_t)(0);
}

// win1.41 004749f0 mac 1016c750 Living::_dt(void)
Living::~Living()
{
}

// win1.41 004753c0 mac 101de710 Creature::GetDestPos(void)
MapCoords* Creature::GetDestPos()
{
    return (MapCoords*)((char*)this + 0x1214);
}

// ==== AUTOHARVEST ====
// AUTOHARVEST ?CanBeExaminedByCreature@Creature@@UAEIPAV1@@Z
bool32_t Creature::CanBeExaminedByCreature(Creature* param_1)
{
    return (bool32_t)0;
}

// AUTOHARVEST ?CanBeFrighteningToCreature@Creature@@UAEIPAV1@@Z
bool32_t Creature::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0x1;
}

