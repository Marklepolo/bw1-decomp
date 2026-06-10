#include "PileFood.h"
#include "PileResource.h"
#include "PileWood.h"
#include "Pot.h"
#include "PotStructure.h"
#include "PrayerIconInfo.h"
#include "PrayerSite.h"
#include "PrayerSiteInfo.h"



// win1.41 0066cec0 mac 1011ceb0 Pot::SetToZero(void)
__declspec(naked) void Pot::SetToZero()
{
    __asm {
            xor eax, eax
            mov dword ptr [ecx + 0x70], eax
            mov byte ptr [ecx + 0x74], al
            ret
        }
}

// win1.41 0066d650 mac 1011bcb0 Pot::IsEffectReceiver(EffectValues *)
bool32_t Pot::IsEffectReceiver(EffectValues* param_1)
{
    return *(uint32_t*)((char*)this + 0x70) != 0;
}

// win1.41 0066d6c0 mac 1011bb10 Pot::StartOnFire(void)
extern "C" void jmp_addr_0x0066d6a0(void);
__declspec(naked) void Pot::StartOnFire()
{
    __asm {
            jmp jmp_addr_0x0066d6a0
        }
}

// win1.41 0066e020 mac 1011d5b0 PileFood::GetSaveType(void)
uint32_t PileFood::GetSaveType()
{
    return (uint32_t)(0x59);
}

// win1.41 0066e030 mac 1011d5f0 PileFood::GetDebugText(void)
char* PileFood::GetDebugText()
{
    return (char*)(0xc02058);
}

// win1.41 0066e040 mac 1011a220 PileFood::_dt(void)
PileFood::~PileFood()
{
}

// win1.41 0066e3b0 mac 10119960 PileResource::IsTuggable(void)
bool32_t PileResource::IsTuggable()
{
    return (bool32_t)(0);
}

// win1.41 0066e3c0 mac inlined PileResource::IsField(Creature *)
bool32_t PileResource::IsField(Creature* param_1)
{
    return 0;
}

// win1.41 0066e3d0 mac 10119880 PileResource::GetLife(void)
__declspec(naked) float PileResource::GetLife()
{
    __asm {
            _emit 0x83
            _emit 0xec
            _emit 0x08
            _emit 0x8b
            _emit 0x41
            _emit 0x70
            _emit 0x8b
            _emit 0x49
            _emit 0x28
            _emit 0x8b
            _emit 0x91
            _emit 0x1c
            _emit 0x01
            _emit 0x00
            _emit 0x00
            _emit 0x89
            _emit 0x44
            _emit 0x24
            _emit 0x00
            _emit 0x33
            _emit 0xc0
            _emit 0x89
            _emit 0x44
            _emit 0x24
            _emit 0x04
            _emit 0xdf
            _emit 0x6c
            _emit 0x24
            _emit 0x00
            _emit 0x89
            _emit 0x54
            _emit 0x24
            _emit 0x00
            _emit 0x89
            _emit 0x44
            _emit 0x24
            _emit 0x04
            _emit 0xda
            _emit 0x74
            _emit 0x24
            _emit 0x00
            _emit 0x83
            _emit 0xc4
            _emit 0x08
            _emit 0xc3
        }
}

// win1.41 0066e830 mac 10118ff0 PileResource::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo *)
bool32_t PileResource::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo* param_1)
{
    return (bool32_t)(1);
}

// win1.41 0066e840 mac 10118fa0 PileResource::NetworkUnfriendlyEndLockedSelect(void)
bool32_t PileResource::NetworkUnfriendlyEndLockedSelect()
{
    return (bool32_t)(1);
}

// win1.41 0066e8f0 mac 10118e10 Pot::CanBecomeAPhysicsObject(void)
bool32_t Pot::CanBecomeAPhysicsObject()
{
    return *(bool32_t*)((char*)*(void**)((char*)this + 0x28) + 0x12c);
}

// win1.41 0066ec50 mac 10117fe0 PileFood::GetResourceType(void)
RESOURCE_TYPE PileFood::GetResourceType()
{
    return (RESOURCE_TYPE)0;
}

// win1.41 0066ec60 mac 10077d70 PileWood::GetResourceType(void)
RESOURCE_TYPE PileWood::GetResourceType()
{
    return RESOURCE_TYPE_WOOD;
}

// win1.41 0066ecb0 mac 1011a3b0 PileResource::_dt(void)
PileResource::~PileResource()
{
}

// win1.41 0066ed60 mac 10117ce0 PileResource::IsPileResource(void)
bool32_t PileResource::IsPileResource()
{
    return (bool32_t)(this);
}

// win1.41 0066f520 mac 10116810 Pot::GetRadiusMultiplierForApplyingPotToPos(void)
float Pot::GetRadiusMultiplierForApplyingPotToPos()
{
    return 2.0f;
}

// win1.41 0066f530 mac 101167d0 Pot::GetScriptObjectType(void)
uint32_t Pot::GetScriptObjectType()
{
    return (uint32_t)(0x10);
}

// win1.41 006706c0 mac 1011ea20 GPrayerSiteInfo::_dt(void)
GPrayerSiteInfo::~GPrayerSiteInfo()
{
}

// win1.41 00670770 mac 1011e8e0 GPrayerIconInfo::_dt(void)
GPrayerIconInfo::~GPrayerIconInfo()
{
}

// win1.41 00670830 mac inlined PrayerSite::ToBeDeleted(int)
void PrayerSite::ToBeDeleted(int param_1)
{
}

// win1.41 006708b0 mac inlined PrayerSite::Process(void)
uint32_t PrayerSite::Process()
{
    return (uint32_t)(3);
}
