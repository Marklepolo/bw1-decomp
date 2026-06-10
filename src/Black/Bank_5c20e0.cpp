#include "HelpDude.h"
#include "HelpProfile.h"
#include "HelpSpirit.h"
#include "HelpSpiritInfo.h"
#include "HelpSystem.h"
#include "HelpSystemInfo.h"
#include "LocalBase.h"



// win1.41 005c20e0 mac 10348c40 HelpDude::Get3DSoundPos(LHPoint *)
__declspec(naked) int HelpDude::Get3DSoundPos(LHPoint* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            add ecx, 0x00003374
            mov edx, dword ptr [ecx]
            mov dword ptr [eax], edx
            mov edx, dword ptr [ecx + 0x04]
            mov dword ptr [eax + 0x04], edx
            mov ecx, dword ptr [ecx + 0x08]
            mov dword ptr [eax + 0x08], ecx
            mov eax, 0x00000001
            ret 4
        }
}

// win1.41 005c2150 mac 1033f600 LocalBase::_dt(void)
LocalBase::~LocalBase()
{
}

// win1.41 005c4560 mac 1034b480 HelpProfile::_dt(void)
HelpProfile::~HelpProfile()
{
}

// win1.41 005c4a70 mac 1034c8b0 HelpSpiritInfo::_dt(void)
HelpSpiritInfo::~HelpSpiritInfo()
{
}

// win1.41 005c4af0 mac 1034b5f0 HelpSpirit::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t HelpSpirit::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return 0;
}

// win1.41 005c53f0 mac 10351af0 HelpSystemInfo::_dt(void)
HelpSystemInfo::~HelpSystemInfo()
{
}

// win1.41 005c5430 mac 10351450 HelpSystem::_dt(void)
HelpSystem::~HelpSystem()
{
}

// win1.41 005c8280 mac 10351b90 HelpSystem::TriggerCategory(HELP_SET_CATEGORY)
extern "C" char game[];
__declspec(naked) void HelpSystem::TriggerCategory(HELP_SET_CATEGORY param_1)
{
    __asm {
            mov eax, dword ptr [game]
            mov edx, dword ptr [eax + 0x00205a40]
            mov eax, dword ptr [esp + 0x04]
            mov dword ptr [ecx + eax * 0x4 + 0x000002d8], edx
            ret 4
        }
}
