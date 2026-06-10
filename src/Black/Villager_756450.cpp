#include "TribeInfo.h"
#include "Villager.h"
#include "VillagerInfo.h"
#include <stdint.h>

extern const char debug_text_Villager[10];

// win1.41 00756450 mac 1005f5e0 Villager::InsertMapObject(void)
void Villager::InsertMapObject()
{
    Object::InsertMapObject();
}

// win1.41 007564c0 mac 10565140 Villager::CanBecomeAPhysicsObject(void)
bool32_t Villager::CanBecomeAPhysicsObject()
{
    return (*(bool32_t (__fastcall **)(Villager*))((char*)*(void**)this + 0x530))(this);
}

// win1.41 00756710 mac 105638f0 MissionaryControl::GetText(void)
const char* MissionaryControl::GetText()
{
    return (const char*)0xc236b8;
}

// win1.41 00756720 mac 10563930 MissionaryControl::GetSaveType(void)
uint32_t MissionaryControl::GetSaveType()
{
    return 0x9e;
}

// win1.41 00756730 mac 10563970 MissionaryControl::GetDebugText(void)
char* MissionaryControl::GetDebugText()
{
    return (char*)0xc236cc;
}

// win1.41 00756b30 mac 10563e60 Villager::IsDrowning(void)
bool32_t Villager::IsDrowning()
{
    return this->action.states[0] == VILLAGER_STATE_DROWNING;
}


void Villager::SetTown(Town* town)
{
    *(unsigned int *)((char *)this + 0x12c) = (unsigned int)town;
}
