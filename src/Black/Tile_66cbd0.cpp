#include "PlayerMessage.h"
#include "PlayerProfile.h"
#include "Playtime.h"
#include "PlaytimeInfo.h"
#include "PotInfo.h"



// win1.41 0066cbd0 mac 1011d400 GPotInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GPotInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000013;
    return (GBaseInfo*)0x00d4c660;
}
