#include "PlayerMessage.h"
#include "PlayerProfile.h"
#include "Playtime.h"
#include "PlaytimeInfo.h"
#include "PotInfo.h"



// win1.41 0066c2d0 mac 10115f30 GPlaytimeInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GPlaytimeInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000005;
    return (GBaseInfo*)0x00d4c598;
}

// win1.41 0066c330 mac 10115d70 GPlaytimeInfo::_dt(void)
GPlaytimeInfo::~GPlaytimeInfo()
{
}
