#include "HanoiBlock.h"
#include "Living.h"
#include "Rand.h"
#include "Rank.h"
#include "RankInfo.h"
#include "Reaction.h"
#include "ReactionInfo.h"
#include "Reward.h"
#include "RewardInfo.h"
#include "Rock.h"
#include "Scaffold.h"
#include "ScaffoldInfo.h"
#include "Script.h"
#include "SquadInfo.h"



// win1.41 006e07b0 mac 10133d90 GSquadInfo::_dt(void)
GSquadInfo::~GSquadInfo()
{
}

// win1.41 006e0810 mac 101340a0 GRankInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GRankInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000005;
    return (GBaseInfo*)0x00d4f5c8;
}

// win1.41 006e0870 mac 10133c10 GRankInfo::_dt(void)
GRankInfo::~GRankInfo()
{
}

// win1.41 006e0e00 mac 101368d0 ReactionInfo::GetBaseInfo(unsigned long &)
GBaseInfo* ReactionInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x29; return (GBaseInfo*)0xd4f6b0;
}

// win1.41 006e0e60 mac 10135410 ReactionInfo::_dt(void)
ReactionInfo::~ReactionInfo()
{
}

// win1.41 006e5440 mac 1013c260 GRewardInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GRewardInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x0000003d;
    return (GBaseInfo*)0x00d50bf8;
}

// win1.41 006e54b0 mac 1013b160 GRewardInfo::_dt(void)
GRewardInfo::~GRewardInfo()
{
}

// win1.41 006e5650 mac 10138ed0 Reward::IsReward( const(void))
bool32_t Reward::IsReward() const
{
    return (bool32_t)0x00000001;
}

// win1.41 006e5660 mac 10138f00 Reward::IsActive( const(void))
bool32_t Reward::IsActive() const
{
    return *(bool32_t*)((char*)this + 0x7c);
}

// win1.41 006e5670 mac 10138f30 Reward::GetSaveType(void)
uint32_t Reward::GetSaveType()
{
    return (uint32_t)0x00000046;
}

// win1.41 006e5680 mac 10138f70 Reward::GetDebugText(void)
char* Reward::GetDebugText()
{
    return (char*)0x00c0bf00;
}

// win1.41 006e5690 mac 1013bef0 Reward::_dt(void)
Reward::~Reward()
{
}

// win1.41 006e5ca0 mac 1013b370 Reward::GetScriptObjectType(void)
uint32_t Reward::GetScriptObjectType()
{
    return (uint32_t)0x00000007;
}

// win1.41 006e5cb0 mac 1013b340 Reward::GetPlayer(void)
GPlayer* Reward::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x6c);
}

// win1.41 006e6880 mac 10139bc0 Reward::GetWeight(void)
float Reward::GetWeight()
{
    return 789.0f;
}

// win1.41 006e6990 mac 101397c0 Reward::PhysicsEditorCreate(int)
void Reward::PhysicsEditorCreate(int param_1)
{
}

// win1.41 006e69a0 mac 10139770 Reward::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t Reward::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return (bool32_t)(0);
}

// win1.41 006e69b0 mac 10139730 Reward::GetOverwriteTapToolTip(void)
uint32_t Reward::GetOverwriteTapToolTip()
{
    return (uint32_t)0x00000ef8;
}

// win1.41 006e6f00 mac 10138fb0 Reward::ResolveLoad(void)
void Reward::ResolveLoad()
{
    Object::ResolveLoad();
}

// win1.41 006e6ff0 mac 1013dd60 Rock::GetPhysicsConstantsType(void)
uint32_t Rock::GetPhysicsConstantsType()
{
    return (uint32_t)0x00000003;
}

// win1.41 006e70c0 mac 1013dad0 Rock::GetResourceType(void)
RESOURCE_TYPE Rock::GetResourceType()
{
    return RESOURCE_TYPE_WOOD;
}

// win1.41 006e77a0 mac 1013d1f0 Rock::GetPlayer(void)
GPlayer* Rock::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x00000090);
}

// win1.41 006e79e0 mac 1000ef30 Rock::GetScriptObjectType(void)
uint32_t Rock::GetScriptObjectType()
{
    return (uint32_t)0x00000021;
}

// win1.41 006e7a60 mac 1013c420 Rock::GetOverwriteTapToolTip(void)
uint32_t Rock::GetOverwriteTapToolTip()
{
    return (uint32_t)0x00000ef7;
}

// win1.41 006e7a70 mac 1013c3c0 Rock::CanBePickedUpByCreature(Creature *)
bool32_t Rock::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)Object::CanBePickedUpByCreature(param_1);
}

// win1.41 006e8360 mac 10144060 GScaffoldInfo::_dt(void)
GScaffoldInfo::~GScaffoldInfo()
{
}

// win1.41 006e8770 mac 10143680 Scaffold::GetPhysicsConstantsType(void)
uint32_t Scaffold::GetPhysicsConstantsType()
{
    return (uint32_t)0x00000011;
}

// win1.41 006e9d30 mac 10140dd0 Scaffold::GetDefaultResource(void)
extern "C" void jmp_addr_0x006e9d10(void);
__declspec(naked) int Scaffold::GetDefaultResource()
{
    __asm {
            push esi
            mov esi, dword ptr [ecx + 0x28]
            call jmp_addr_0x006e9d10
            imul eax, dword ptr [esi + 0x6c]
            pop esi
            ret
        }
}

// win1.41 006ea940 mac 1013f890 Scaffold::ReactToPhysicsImpact(PhysicsObject *, bool)
void Scaffold::ReactToPhysicsImpact(PhysicsObject* param_1, bool param_2)
{
}

// win1.41 006ea9d0 mac 1013f6d0 Scaffold::GetOverwritePickUpToolTip(void)
uint32_t Scaffold::GetOverwritePickUpToolTip()
{
    return (uint32_t)0x00000ee7;
}

// win1.41 006ea9e0 mac 1013f670 Scaffold::GetUpdateOfBoredomValue(Reaction *, GameThingWithPos *)
float Scaffold::GetUpdateOfBoredomValue(Reaction* param_1, GameThingWithPos* param_2)
{
    return -1.0f;
}

// win1.41 006eab60 mac 1013f280 Scaffold::GetScriptObjectType(void)
uint32_t Scaffold::GetScriptObjectType()
{
    return (uint32_t)0x00000027;
}
