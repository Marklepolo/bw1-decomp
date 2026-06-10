#include "EditorHug.h"
#include "EditorIconBase.h"
#include "EffectInfo.h"
#include "EffectValues.h"
#include "Feature.h"
#include "FeatureInfo.h"
#include "Field.h"
#include "FieldInfo.h"
#include "FieldTypeInfo.h"
#include "FireFly.h"
#include "Flowers.h"
#include "FlowersInfo.h"
#include "MagicEffectInfo.h"
#include "PlannedFeature.h"
#include "WorshipSiteUpgrade.h"



// win1.41 00524d70 mac 100ccc90 GEffectInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GEffectInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x0000000c;
    return (GBaseInfo*)0x00cc94c8;
}
