#include "HelpSystem.h"
#include "HelpText.h"
#include "ToolTipsInfo.h"



// win1.41 005c99e0 mac 10354720 GToolTipsInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GToolTipsInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x000000aa;
    return (GBaseInfo*)0x00d16918;
}
