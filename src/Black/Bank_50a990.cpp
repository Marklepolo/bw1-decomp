#include "Creature.h"
#include "Creature.h"
#include "Creature.h"
#include "Creche.h"
#include "Dance.h"
#include "DanceGroup.h"
#include "DanceInfo.h"
#include "FootpathLink.h"
#include "GroupBehaviour.h"



// win1.41 0050a990 mac inlined Creche::GetArrivePos(MapCoords *)
__declspec(naked) MapCoords* Creche::GetArrivePos(MapCoords* param_1)
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

// win1.41 0050a9b0 mac 102a3c40 Creche::CanActAsAContainer(Creature *)
bool32_t Creche::CanActAsAContainer(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0050a9c0 mac 102a3c90 Creche::IsStoragePit(Creature *)
bool32_t Creche::IsStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0050a9e0 mac 102a3d00 Creche::GetSaveType(void)
uint32_t Creche::GetSaveType()
{
    return (uint32_t)0x00000050;
}

// win1.41 0050a9f0 mac 102a3d40 Creche::GetDebugText(void)
char* Creche::GetDebugText()
{
    return (char*)0x00be6810;
}

// win1.41 0050aa00 mac 102a3b10 Creche::_dt(void)
Creche::~Creche()
{
}

// win1.41 0050b600 mac 102aa810 GDanceInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GDanceInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x19; return (GBaseInfo*)0xcc4b80;
}

// win1.41 0050b670 mac 102a8e60 GDanceInfo::_dt(void)
GDanceInfo::~GDanceInfo()
{
}

// win1.41 0050b720 mac 102a8120 Dance::GetFootpathLink(void)
GFootpathLink* Dance::GetFootpathLink()
{
    return *(GFootpathLink**)((char*)this + 0x000000e8);
}

// win1.41 0050b740 mac 102a8190 Dance::GetText(void)
const char* Dance::GetText()
{
    return (const char*)0x009ce0f0;
}

// win1.41 0050b750 mac 102a81c0 Dance::GetSaveType(void)
uint32_t Dance::GetSaveType()
{
    return (uint32_t)0x00000027;
}

// win1.41 0050b760 mac 102a81f0 Dance::GetDebugText(void)
char* Dance::GetDebugText()
{
    return (char*)0x00be6894;
}

// win1.41 0050b770 mac 102aa200 Dance::_dt(void)
Dance::~Dance()
{
}

// win1.41 0050bb30 mac 102a9db0 Dance::CleanUpBeforeReset(void)
void Dance::CleanUpBeforeReset()
{
    *(uint32_t*)((char*)this + 0x000000fc) = 0x00000000;
}

// win1.41 0050bb40 mac 102a9d60 Dance::StartDance(void)
extern "C" char game[];
__declspec(naked) void Dance::StartDance()
{
    __asm {
            mov dword ptr [ecx + 0x00000100], 0x00000000
            mov eax, dword ptr [game]
            mov edx, dword ptr [eax + 0x00205a40]
            mov dword ptr [ecx + 0x00000108], edx
            ret
        }
}

// win1.41 0050c3c0 mac 102a9110 Dance::GetScriptObjectType(void)
uint32_t Dance::GetScriptObjectType()
{
    return (uint32_t)0x0000000a;
}

// win1.41 0050cad0 mac 100ef190 GFootpathLink::GetSaveType(void)
uint32_t GFootpathLink::GetSaveType()
{
    return (uint32_t)0x00000002;
}

// win1.41 0050cae0 mac 100ef1d0 GFootpathLink::GetDebugText(void)
char* GFootpathLink::GetDebugText()
{
    return (char*)0x00be68dc;
}

// win1.41 0050caf0 mac 100ef100 GFootpathLink::_dt(void)
GFootpathLink::~GFootpathLink()
{
}

// win1.41 0050cb40 mac inlined Dance::GetArrivePos(MapCoords *)
__declspec(naked) MapCoords* Dance::GetArrivePos(MapCoords* param_1)
{
    __asm {
            add ecx, 0x14
            mov eax, ecx
            mov ecx, dword ptr [eax]
            mov edx, dword ptr [eax + 0x04]
            push esi
            mov esi, dword ptr [eax + 0x08]
            mov eax, dword ptr [esp + 0x08]
            push edi
            add ecx, 0x00008000
            mov edi, eax
            mov dword ptr [edi], ecx
            mov dword ptr [edi + 0x04], edx
            mov dword ptr [edi + 0x08], esi
            pop edi
            pop esi
            ret 4
        }
}

// win1.41 0050cee0 mac 102aaa20 DanceGroup::GetSaveType(void)
uint32_t DanceGroup::GetSaveType()
{
    return (uint32_t)0x0000007b;
}

// win1.41 0050cef0 mac 102aaa60 DanceGroup::GetDebugText(void)
char* DanceGroup::GetDebugText()
{
    return (char*)0x00be82c0;
}

// win1.41 0050cf00 mac 102aa590 DanceGroup::_dt(void)
DanceGroup::~DanceGroup()
{
}


bool32_t Creed::CanBecomeAPhysicsObject()
{
    return (bool32_t)0;
}

uint32_t Creed::GetSaveType()
{
    return (uint32_t)0x6d;
}

char* Creed::GetDebugText()
{
    return (char*)0xbe684c;
}


bool32_t Creed::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}


bool32_t Creed::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)0x1;
}

void DanceEditState::ToBeDeleted(int param_1)
{
}
