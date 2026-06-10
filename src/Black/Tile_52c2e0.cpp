#include "BuildingSite.h"
#include "EditingDebugBox.h"
#include "EndGameBox.h"
#include "FireFly.h"
#include "FishFarm.h"
#include "FishFarmInfo.h"
#include "Flock.h"
#include "Football.h"
#include "FootballPositionInfo.h"
#include "Footpath.h"
#include "FootpathFinder.h"
#include "FootpathLink.h"
#include "FootpathLinkSave.h"
#include "FootpathNode.h"
#include "Forest.h"
#include "ForestInfo.h"
#include "FrontEnd.h"
#include "GameOSFile.h"
#include "LoadingBox.h"
#include "MainMenu.h"
#include "MultiMapFixed.h"
#include "MultiMapFixedInfo.h"
#include "NewProfileBox.h"
#include "Object.h"
#include "Plasma.h"
#include "ProfileEditor.h"
#include "RegisterBox.h"
#include "SingleMapFixedInfo.h"
#include "SkipBox.h"
#include "TattooEditor.h"
#include "Villager.h"



// win1.41 0052c2e0 mac 100da3d0 GFishFarmInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GFishFarmInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000001;
    return (GBaseInfo*)0x00ccfc78;
}
