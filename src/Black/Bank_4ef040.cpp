#include "Creature.h"
#include "CreaturePen.h"
#include "CreaturePenInfo.h"
#include "CreaturePhysical.h"
#include "CreaturePlan.h"
#include "PlannedCreaturePen.h"



// win1.41 004ef040 mac 10274940 PlannedCreaturePen::GetText(void)
const char* PlannedCreaturePen::GetText()
{
    return (const char*)0x00be01b8;
}

// win1.41 004ef050 mac 102748a0 PlannedCreaturePen::_dt(void)
PlannedCreaturePen::~PlannedCreaturePen()
{
}

// win1.41 004f2a70 mac 1027d6b0 Creature::NumGameTurnsToReactToCreatureFunction(GameThingWithPos *, unsigned long, float)
uint32_t Creature::NumGameTurnsToReactToCreatureFunction(GameThingWithPos* param_1, uint32_t param_2, float param_3)
{
    return (uint32_t)Living::NumGameTurnsToReactToCreatureFunction(param_1, param_2, param_3);
}

// win1.41 004f2a90 mac 1027d620 Creature::NumGameTurnsBeforeReactingAgainToCreatureFunction(GameThingWithPos *, unsigned long, float)
uint32_t Creature::NumGameTurnsBeforeReactingAgainToCreatureFunction(GameThingWithPos* param_1, uint32_t param_2, float param_3)
{
    return (uint32_t)Living::NumGameTurnsBeforeReactingAgainToCreatureFunction(param_1, param_2, param_3);
}

// win1.41 004f3a00 mac 1027b2e0 Creature::SetupReactToFight(GameThingWithPos *, Reaction *)
void Creature::SetupReactToFight(GameThingWithPos* param_1, Reaction* param_2)
{
}
