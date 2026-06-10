#include "Creature.h"
#include "CreaturePen.h"
#include "CreaturePenInfo.h"
#include "CreaturePhysical.h"
#include "CreaturePlan.h"
#include "PlannedCreaturePen.h"



// win1.41 004eedc0 mac 102755a0 GCreaturePenInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GCreaturePenInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000005;
    return (GBaseInfo*)0x00cad428;
}

// win1.41 004eee30 mac 10274c20 GCreaturePenInfo::_dt(void)
GCreaturePenInfo::~GCreaturePenInfo()
{
}
