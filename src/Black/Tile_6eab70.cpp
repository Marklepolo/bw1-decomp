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



// win1.41 006eab70 mac 1013f210 Scaffold::ThrowObjectFromHand(GInterfaceStatus *, int)
uint32_t Scaffold::ThrowObjectFromHand(GInterfaceStatus* param_1, int param_2)
{
    return (uint32_t)Object::ThrowObjectFromHand(param_1, param_2);
}
