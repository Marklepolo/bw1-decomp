#include "Town.h"
#include "TownSpellIcon.h"
#include "TownStats.h"
#include "Tree.h"
#include "TreeInfo.h"
#include "TribeInfo.h"
#include "Utils.h"
#include "VillagerInfo.h"



// win1.41 0074c8c0 mac 10159ef0 GTribeInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GTribeInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x9; return (GBaseInfo*)0xda57a8;
}
