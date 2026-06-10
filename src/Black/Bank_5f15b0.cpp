#include "Animal.h"
#include "Living.h"
#include "LobbyBox.h"
#include "Villager.h"

extern "C" char ReactionInfo_ARRAY_00d4f6b0[];

// win1.41 005f15b0 mac 10388550 Living::SetupReactToNewBuilding(GameThingWithPos *, Reaction *)
void Living::SetupReactToNewBuilding(GameThingWithPos* param_1, Reaction* param_2)
{
}

// win1.41 005f15c0 mac 103884e0 Living::FleeFromObjectPriority(Reaction *, Reaction *)
uint8_t Living::FleeFromObjectPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x10);
}

// win1.41 005f1610 mac 103883a0 Living::LookAtObjectPriority(Reaction *, Reaction *)
uint8_t Living::LookAtObjectPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x74);
}

// win1.41 005f1620 mac 10388330 Living::FollowObjectPriority(Reaction *, Reaction *)
uint8_t Living::FollowObjectPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0xd8);
}

// win1.41 005f1690 mac 103881e0 Living::LookAtSpellPriority(Reaction *, Reaction *)
uint8_t Living::LookAtSpellPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x1a0);
}

// win1.41 005f16e0 mac 103880b0 Living::FollowSpellPriority(Reaction *, Reaction *)
uint8_t Living::FollowSpellPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x204);
}

// win1.41 005f17f0 mac 10387d90 Living::ReactToMagicTreePriority(Reaction *, Reaction *)
uint8_t Living::ReactToMagicTreePriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x330);
}

// win1.41 005f1860 mac 10387bb0 Living::ReactToMagicShieldPriority(Reaction *, Reaction *)
uint8_t Living::ReactToMagicShieldPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x524);
}

// win1.41 005f1870 mac 10387b30 Living::ReactToCreatureGiftPriority(Reaction *, Reaction *)
uint8_t Living::ReactToCreatureGiftPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x588);
}

// win1.41 005f18a0 mac 10387a20 Living::ReactToFaintingPriority(Reaction *, Reaction *)
uint8_t Living::ReactToFaintingPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0x9d4);
}

// win1.41 005f18b0 mac 103879b0 Living::ReactToConfusedPriority(Reaction *, Reaction *)
uint8_t Living::ReactToConfusedPriority(Reaction* param_1, Reaction* param_2)
{
    return *(uint8_t*)((char*)&ReactionInfo_ARRAY_00d4f6b0 + 0xa38);
}

// win1.41 005f2710 mac 10385c50 Living::AmILikelyToMove(void)
bool32_t Living::AmILikelyToMove()
{
    return *(uint8_t*)((char*)this + 0x0000008c) == 0x1;
}
