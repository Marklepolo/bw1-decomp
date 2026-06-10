#include "GameThing.h"
#include "HelpSpritesGuidance.h"
#include "Setup.h"
#include "ShowNeeds.h"
#include "ShowNeedsInfo.h"
#include "ShowNeedsVisuals.h"
#include "Spell.h"



// win1.41 00719a10 mac 101461f0 GShowNeedsInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GShowNeedsInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x4; return (GBaseInfo*)0xd99738;
}
