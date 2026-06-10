#include "CreatureExplorationMap.h"
#include "CreatureInitialSourceInfo.h"
#include "CreatureLearning.h"
#include "CreaturePreviousLesson.h"
#include "CreatureSourceBoundsInfo.h"



// win1.41 004dd2c0 mac 1025d520 CreatureInitialSourceInfo::_dt(void)
CreatureInitialSourceInfo::~CreatureInitialSourceInfo()
{
}

// win1.41 004dd3a0 mac 1025ee20 CreatureSourceBoundsInfo::GetBaseInfo(unsigned long &)
GBaseInfo* CreatureSourceBoundsInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x0000003d;
    return (GBaseInfo*)0x00c892a8;
}

// win1.41 004dd400 mac 1025eab0 CreatureSourceBoundsInfo::_dt(void)
CreatureSourceBoundsInfo::~CreatureSourceBoundsInfo()
{
}

// win1.41 004e03a0 mac 10245f80 CreaturePreviousLesson::_dt(void)
CreaturePreviousLesson::~CreaturePreviousLesson()
{
}


void CreatureGlobalExplorationMap::Dump()
{
    
}
