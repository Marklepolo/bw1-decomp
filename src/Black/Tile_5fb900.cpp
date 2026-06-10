#include "MagicInfo.h"
#include "MagicLivingInfo.h"
#include "MagicTeleport.h"
#include "MagicTree.h"
#include "MagicWood.h"
#include "Map.h"
#include "MobileObject.h"
#include "MobileStaticInfo.h"
#include "SpellTeleport.h"
#include "VortexInfo.h"
#include "VortexObjectInfo.h"



// win1.41 005fb910 mac inlined GMagicLivingInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GMagicLivingInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000002;
    return (GBaseInfo*)0x00d37dc8;
}
