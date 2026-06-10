#include "CreatureExplorationMap.h"
#include "CreatureInitialSourceInfo.h"
#include "CreatureLearning.h"
#include "CreaturePreviousLesson.h"
#include "CreatureSourceBoundsInfo.h"



// win1.41 004dd260 mac 1025eee0 CreatureInitialSourceInfo::GetBaseInfo(unsigned long &)
GBaseInfo* CreatureInitialSourceInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x0000003d;
    return (GBaseInfo*)0x00c89958;
}
