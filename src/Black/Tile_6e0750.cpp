#include "HanoiBlock.h"
#include "Living.h"
#include "Rand.h"
#include "Rank.h"
#include "RankInfo.h"
#include "Reaction.h"
#include "ReactionInfo.h"
#include "Reward.h"
#include "RewardInfo.h"
#include "Rock.h"
#include "Scaffold.h"
#include "ScaffoldInfo.h"
#include "Script.h"
#include "SquadInfo.h"



// win1.41 006e0750 mac 10133ff0 GSquadInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GSquadInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000002;
    return (GBaseInfo*)0x00d4f658;
}
