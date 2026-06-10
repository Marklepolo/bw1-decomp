#include "PlannedWorshipSiteUpgrade.h"
#include "WorshipSite.h"
#include "WorshipSiteUpgrade.h"
#include "WorshipSiteUpgradeInfo.h"
#include "WorshipSpellIcon.h"



// win1.41 0077daf0 mac 105acbf0 WorshipSite::ResolveLoad(void)
void WorshipSite::ResolveLoad()
{
    Object::ResolveLoad();
}

// win1.41 0077e260 mac 105aba40 WorshipSite::GetNumVillagersRequestingToGoHome(void)
int WorshipSite::GetNumVillagersRequestingToGoHome()
{
    return *(int*)((char*)this + 0x00000124);
}

// win1.41 0077e480 mac 105ab730 WorshipSite::GetRadiusMultiplierForApplyingPotToPos(void)
float WorshipSite::GetRadiusMultiplierForApplyingPotToPos()
{
    return 0;
}

// win1.41 0077eb70 mac 105b4210 GWorshipSiteUpgradeInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GWorshipSiteUpgradeInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000001;
    return (GBaseInfo*)0x00dcc9a0;
}

// win1.41 0077ebc0 mac 105b4170 GWorshipSiteUpgradeInfo::_dt(void)
GWorshipSiteUpgradeInfo::~GWorshipSiteUpgradeInfo()
{
}

// win1.41 0077ec60 mac inlined WorshipSiteUpgrade::GetWorshipSite(void)
WorshipSite* WorshipSiteUpgrade::GetWorshipSite()
{
    return *(WorshipSite**)((char*)this + 0x00000080);
}

// win1.41 0077ee70 mac inlined PlannedWorshipSiteUpgrade::_dt(void)
PlannedWorshipSiteUpgrade::~PlannedWorshipSiteUpgrade()
{
}

// win1.41 0077f0a0 mac 10381d20 WorshipSpellIcon::GetWorshipSite(void)
WorshipSite* WorshipSpellIcon::GetWorshipSite()
{
    return *(WorshipSite**)((char*)this + 0x00000118);
}

// win1.41 0077f0b0 mac 105b42c0 WorshipSpellIcon::IsEffectReceiver(EffectValues *)
bool32_t WorshipSpellIcon::IsEffectReceiver(EffectValues* param_1)
{
    return 0;
}

// win1.41 0077f0f0 mac 105b4400 WorshipSpellIcon::GetSaveType(void)
uint32_t WorshipSpellIcon::GetSaveType()
{
    return (uint32_t)0x00000078;
}

// win1.41 0077f100 mac 105b4440 WorshipSpellIcon::GetDebugText(void)
char* WorshipSpellIcon::GetDebugText()
{
    return (char*)0x00c24e08;
}

// win1.41 0077f110 mac 105b6fb0 WorshipSpellIcon::_dt(void)
WorshipSpellIcon::~WorshipSpellIcon()
{
}

// win1.41 0077f1f0 mac inlined WorshipSpellIcon::SetToZero(void)
__declspec(naked) void WorshipSpellIcon::SetToZero()
{
    __asm {
            xor eax, eax
            mov dword ptr [ecx + 0x00000134], eax
            mov byte ptr [ecx + 0x00000120], al
            mov dword ptr [ecx + 0x00000128], eax
            mov dword ptr [ecx + 0x00000124], 0xffffffff
            mov word ptr [ecx + 0x00000114], ax
            mov dword ptr [ecx + 0x0000011c], eax
            mov dword ptr [ecx + 0x00000138], eax
            mov word ptr [ecx + 0x0000013c], ax
            ret
        }
}
