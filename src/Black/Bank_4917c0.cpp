#include "CreatureActionInfo.h"
#include "CreatureAgenda.h"
#include "CreatureInitialDesireInfo.h"



// win1.41 004917c0 mac 1022eaa0 CreatureActionInfo::_dt(void)
CreatureActionInfo::~CreatureActionInfo()
{
}

// win1.41 00491830 mac 1022ec70 CreatureInitialDesireInfo::GetBaseInfo(unsigned long &)
GBaseInfo* CreatureInitialDesireInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000028;
    return (GBaseInfo*)0x00c67e90;
}

// win1.41 004918a0 mac 1022e850 CreatureInitialDesireInfo::_dt(void)
CreatureInitialDesireInfo::~CreatureInitialDesireInfo()
{
}
