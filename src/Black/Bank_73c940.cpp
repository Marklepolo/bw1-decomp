#include "PlannedTownCentre.h"
#include "Town.h"
#include "TownCentre.h"
#include "TownCreatureInfo.h"
#include "TownDesire.h"
#include "TownDesireFlags.h"
#include "TownDesireInfo.h"
#include "TownInfo.h"



// win1.41 0073c940 mac 1006fa90 Town::GetWorshipSite(void)
WorshipSite* Town::GetWorshipSite()
{
    return *(WorshipSite**)((char*)this + 0x0000098c);
}

// win1.41 0073d150 mac 105514f0 Town::AllVillagersCheckNeedNewAbode(void)
void Town::AllVillagersCheckNeedNewAbode()
{
}

// win1.41 0073e1d0 mac 1054f6b0 Town::GetTotemStatue(void)
__declspec(naked) TotemStatue* Town::GetTotemStatue()
{
    __asm {
            mov eax, dword ptr [ecx + 0x000009a4]
            test eax, eax
            je L_0073e1e1
            mov eax, dword ptr [eax + 0x000000cc]
            ret
            L_0073e1e1:
            xor eax, eax
            ret
        }
}

// win1.41 0073e200 mac 1054f630 Town::GetScriptObjectType(void)
uint32_t Town::GetScriptObjectType()
{
    return (uint32_t)0x00000009;
}

// win1.41 0073e400 mac 10060840 Town::GetDesire(TOWN_DESIRE_INFO)
float Town::GetDesire(TOWN_DESIRE_INFO param_1)
{
    return *(float*)((char*)this + param_1 * 4 + 0x14c) + *(float*)((char*)this + param_1 * 4 + 0x108) + *(float*)((char*)this + param_1 * 4 + 0xc4);
}

// win1.41 0073e420 mac 10055140 Town::GetRawDesire(TOWN_DESIRE_INFO)
float Town::GetRawDesire(TOWN_DESIRE_INFO param_1)
{
    return *(float*)((char*)this + param_1 * 4 + 0x19c) + *(float*)((char*)this + param_1 * 4 + 0x108) + *(float*)((char*)this + param_1 * 4 + 0xc4);
}

// win1.41 0073ff00 mac 1054a490 Town::GetVillagerActivityDesire(Villager *)
float Town::GetVillagerActivityDesire(Villager* param_1)
{
    return Town::GetRawDesire((TOWN_DESIRE_INFO)0xf);
}

// win1.41 007412e0 mac 10547990 Town::ResolveLoad(void)
void Town::ResolveLoad()
{
}

// win1.41 007437c0 mac 10558ea0 TownCreatureInfo::GetBaseInfo(unsigned long &)
GBaseInfo* TownCreatureInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0;
        return (GBaseInfo*)0;
}

// win1.41 007437d0 mac 10557190 TownCreatureInfo::_dt(void)
TownCreatureInfo::~TownCreatureInfo()
{
}

// win1.41 00743bc0 mac 1055b860 TownCentre::InteractsWithPhysicsObjects(void)
bool32_t TownCentre::InteractsWithPhysicsObjects()
{
    __asm { mov al, 0x01 }
}

// win1.41 007449e0 mac inlined TownCentre::GetArrivePos(MapCoords *)
__declspec(naked) MapCoords* TownCentre::GetArrivePos(MapCoords* param_1)
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

// win1.41 00744b20 mac 1055ef20 GTownDesireInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GTownDesireInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x11; return (GBaseInfo*)0xda2930;
}

// win1.41 00744b90 mac 1055d6c0 GTownDesireInfo::_dt(void)
GTownDesireInfo::~GTownDesireInfo()
{
}

// win1.41 00745730 mac 1055ea40 TownDesire::_dt(void)
TownDesire::~TownDesire()
{
}

// win1.41 00746a10 mac 1055dae0 TownDesireFlags::InteractsWithPhysicsObjects(void)
bool32_t TownDesireFlags::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00746a20 mac 100550f0 TownDesireFlags::Process(void)
uint32_t TownDesireFlags::Process()
{
    *(uint32_t*)((char*)this + 0x58) = 0;
        return 1;
}
