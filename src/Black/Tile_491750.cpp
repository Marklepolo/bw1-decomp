#include "CreatureActionInfo.h"
#include "CreatureAgenda.h"
#include "CreatureInitialDesireInfo.h"



// win1.41 00491750 mac 1022ebc0 CreatureActionInfo::GetBaseInfo(unsigned long &)
GBaseInfo* CreatureActionInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000148;
    return (GBaseInfo*)0x00c6c490;
}
