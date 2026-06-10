#include "Climate.h"
#include "ClimateInfo.h"
#include "ClimateRainInfo.h"
#include "Fragment.h"
#include "GameThingWithPos.h"
#include "Living.h"
#include "Villager.h"
#include "VillagerStateTableInfo.h"
#include "VirtualInfluence.h"
#include "VortexSave.h"
#include "WayPoint.h"
#include "Weather.h"
#include "WeatherInfo.h"
#include "WeatherThing.h"
#include "Whale.h"
#include "Wonder.h"



// win1.41 00774360 mac 105a4b40 WeatherThing::GetScriptObjectType(void)
uint32_t WeatherThing::GetScriptObjectType()
{
    return (uint32_t)(0xf);
}
