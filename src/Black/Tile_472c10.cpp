#include "Alignment.h"
#include "Creature.h"
#include "CreatureInfo.h"
#include "CreaturePlan.h"
#include "CreatureSubAction.h"
#include "DifferentCreatureInfo.h"
#include "Living.h"
#include "Mobile.h"
#include "MobileWallHug.h"
#include "Villager.h"



// win1.41 00472c10 mac 101e2980 CreatureInfo::GetBaseInfo(unsigned long &)
GBaseInfo* CreatureInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000011;
    return (GBaseInfo*)0x00c60460;
}
