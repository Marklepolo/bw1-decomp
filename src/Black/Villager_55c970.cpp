#include "Villager.h"

extern const char debug_text_Villager[10];

// win1.41 0055c970 mac 10064ef0 Villager::IsChild(void)
bool32_t Villager::IsChild()
{
    return (*((unsigned char*)this + 0xe0) >> 3) & 1;
}

// win1.41 0055c980 mac 10051310 Villager::IsFoodSpeedUp(void)
bool32_t Villager::IsFoodSpeedUp()
{
    return this->food_speed_up != 0;
}

// win1.41 0055c990 mac 10147d30 Villager::IsABeliever(void)
bool32_t Villager::IsABeliever()
{
    return true;
}

// win1.41 0055ca30 mac 10147f70 Villager::GetTastiness(void)
uint32_t Villager::GetTastiness()
{
    return 2;
}

// win1.41 0055ca40 mac 100c54f0 Villager::GetVillagerName(void)
const char* Villager::GetVillagerName()
{
    return 0;
}

// win1.41 0055ca70 mac 10148010 Villager::GetCreatureBeliefType(void)
uint32_t Villager::GetCreatureBeliefType()
{
    return 6;
}

// win1.41 0055ca90 mac 101480d0 Villager::CanReceiveGifts(Creature *)
bool32_t Villager::CanReceiveGifts(Creature* param_1)
{
    return 1;
}

// win1.41 0055cab0 mac 1006d800 Villager::IsVillager(Creature *)
bool32_t Villager::IsVillager(Creature* param_1)
{
    return 1;
}

// win1.41 0055cb10 mac 10148200 Villager::GetDeathReason(void)
DEATH_REASON Villager::GetDeathReason()
{
    return (DEATH_REASON)*(uint8_t*)((char*)this + 0x118);
}

// win1.41 0055cb30 mac 10571f80 Villager::GetDebugText(void)
char* Villager::GetDebugText()
{
    return (char*)0x00bed194;
}

// win1.41 0055cb40 mac 10571890 Villager::_dt(unsigned int)
Villager::~Villager()
{
}


int Villager::GetMesh() const
{
    return (int)*(unsigned int *)(*(char **)((char *)this + 0x28) + 0x214);
}
