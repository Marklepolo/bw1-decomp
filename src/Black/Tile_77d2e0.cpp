#include "PlannedWorshipSiteUpgrade.h"
#include "WorshipSite.h"
#include "WorshipSiteUpgrade.h"
#include "WorshipSiteUpgradeInfo.h"
#include "WorshipSpellIcon.h"



// win1.41 0077d2e0 mac 105ae4e0 WorshipSite::GetScriptObjectType(void)
uint32_t WorshipSite::GetScriptObjectType()
{
    return (uint32_t)0x00000013;
}
