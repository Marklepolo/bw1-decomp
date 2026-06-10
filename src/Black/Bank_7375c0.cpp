#include "Belief.h"
#include "MapCoords.h"
#include "Totem.h"
#include "TotemStatue.h"
#include "Utils.h"
#include "TotemStatueInfo.h"
#include "Town.h"
#include "TownInfo.h"
#include "TownStats.h"



// win1.41 007375c0 mac 10542ff0 Totem::NetworkUnfriendlyStartLockedSelect(void)
__declspec(naked) bool32_t Totem::NetworkUnfriendlyStartLockedSelect()
{
    __asm {
            lea eax, dword ptr [ecx + 0x14]
            mov edx, dword ptr [eax]
            add ecx, 0x000000c4
            mov dword ptr [ecx], edx
            mov edx, dword ptr [eax + 0x04]
            mov eax, dword ptr [eax + 0x08]
            mov dword ptr [ecx + 0x04], edx
            mov dword ptr [ecx + 0x08], eax
            mov eax, 0x00000001
            ret
        }
}

// win1.41 007375e0 mac 10542f60 Totem::NetworkUnfriendlyEndLockedSelect(void)
extern "C" void jmp_addr_0x00436a70(void);
extern "C" void jmp_addr_0x00550e40(void);
extern "C" char game[];
__declspec(naked) bool32_t Totem::NetworkUnfriendlyEndLockedSelect()
{
    __asm {
            lea eax, dword ptr [ecx + 0x000000c4]
            push eax
            call jmp_addr_0x00436a70
            mov ecx, dword ptr [game]
            push eax
            push 0x28
            call jmp_addr_0x00550e40
            mov eax, 0x00000001
            ret
        }
}

// win1.41 00737600 mac 10542f00 Totem::NetworkFriendlyEndLockedSelect(GInterfaceStatus *)
bool32_t Totem::NetworkFriendlyEndLockedSelect(GInterfaceStatus* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00737a80 mac 10545af0 GTotemStatueInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GTotemStatueInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x9; return (GBaseInfo*)0xda1d18;
}

// win1.41 00737af0 mac 10545400 GTotemStatueInfo::_dt(void)
GTotemStatueInfo::~GTotemStatueInfo()
{
}

// win1.41 00737d40 mac 105451c0 TotemStatue::InteractsWithPhysicsObjects(void)
bool32_t TotemStatue::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00737d50 mac 10545170 TotemStatue::ReactToPhysicsImpact(PhysicsObject *, bool)
void TotemStatue::ReactToPhysicsImpact(PhysicsObject* param_1, bool param_2)
{
}

// win1.41 00738260 mac 10544c70 TotemStatue::GetWorshipSpeed(void)
float TotemStatue::GetWorshipSpeed()
{
    return *(float*)((char*)this + 0x80);
}

// win1.41 00738130 mac 10544dd0 TotemStatue::AddToPlayer(void)
// On joining a player: if there's no Town, reset our own worship percentage; otherwise face the worship
// site (+pi/2), run the per-totem worship setup (Sub7381C0), and reset the Town's worship percentage.
void TotemStatue::AddToPlayer()
{
    if (GetTown() != 0) {
        if (GetTown()->GetWorshipSite() != 0) {
            float a = GUtils::Get3DAngleFromXZ(*(MapCoords*)((char*)this + 0x14),
                                               *(MapCoords*)((char*)GetTown()->GetWorshipSite() + 0x14)) + 1.5707964f;
            SetYAngle(a);
        }
        Sub7381C0();
        GetTown()->SetWorshipPercentage(0.0f);
        return;
    }
    SetWorshipPercentage(0.0f);
}

// win1.41 00738690 mac 10544520 TotemStatue::NetworkFriendlyEndLockedSelect(GInterfaceStatus *)
bool32_t TotemStatue::NetworkFriendlyEndLockedSelect(GInterfaceStatus* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00738eb0 mac 10543f70 TotemStatue::GetScriptObjectType(void)
uint32_t TotemStatue::GetScriptObjectType()
{
    return (uint32_t)(0x28);
}

// win1.41 00738f70 mac 10545ba0 GTownInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GTownInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x1; return (GBaseInfo*)0xda2780;
}

// win1.41 00738fc0 mac 10545c00 GTownInfo::_dt(void)
GTownInfo::~GTownInfo()
{
}

// win1.41 007391d0 mac 10559100 Town::GetOrigin(void)
uint32_t Town::GetOrigin()
{
    return (uint32_t)(1);
}

// win1.41 007391f0 mac 10559130 Town::GetCreatureBeliefType(void)
uint32_t Town::GetCreatureBeliefType()
{
    return (uint32_t)(0);
}

// win1.41 00739200 mac 10559170 Town::GetCreatureBeliefListType(void)
uint32_t Town::GetCreatureBeliefListType()
{
    return (uint32_t)(0);
}

// win1.41 00739220 mac inlined Town::IsTown_1(Creature *)
bool32_t Town::IsTown(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00739230 mac 105592e0 Town::IsActivityObjectWhichCompassionAppliesTo(Creature *)
bool32_t Town::IsActivityObjectWhichCompassionAppliesTo(Creature* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00739240 mac 10559340 Town::IsActivityObjectWhichPlayfulnessAppliesTo(Creature *)
bool32_t Town::IsActivityObjectWhichPlayfulnessAppliesTo(Creature* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00739250 mac inlined Town::IsTown_0(void)
bool32_t Town::IsTown()
{
    return (bool32_t)0x00000001;
}

// win1.41 00739260 mac 105593a0 Town::IsSuitableForCreatureActivity(void)
bool32_t Town::IsSuitableForCreatureActivity()
{
    return (bool32_t)(1);
}

// win1.41 00739270 mac 105593f0 Town::CanBePlayedWithByCreature(Creature *)
bool32_t Town::CanBePlayedWithByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00739280 mac 10559440 Town::GetText(void)
const char* Town::GetText()
{
    return (const char*)(0xc22bd0);
}

// win1.41 00739290 mac 10559470 Town::GetSaveType(void)
uint32_t Town::GetSaveType()
{
    return (uint32_t)(0x28);
}

// win1.41 007392a0 mac 105594a0 Town::GetDebugText(void)
char* Town::GetDebugText()
{
    return (char*)(0xc22bd8);
}

// win1.41 00739320 mac 105581c0 GBelief::_dt(void)
GBelief::~GBelief()
{
}
