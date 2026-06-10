#include "JobInfo.h"



// win1.41 005e16c0 mac 100fe6d0 GJobInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GJobInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000010;
    return (GBaseInfo*)0x00d19cc8;
}
