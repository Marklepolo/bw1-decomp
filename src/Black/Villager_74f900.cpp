#include "TribeInfo.h"
#include "Villager.h"
#include "VillagerInfo.h"
#include <stdint.h>



// win1.41 0074f900 mac 1056bfe0 GVillagerInfo::_dt(void)
GVillagerInfo::~GVillagerInfo()
{
}

// win1.41 00750310 mac 10097630 Villager::GetHoldType(void)
HOLD_TYPE Villager::GetHoldType()
{
    return HOLD_TYPE_VILLAGER;
}

// win1.41 00750320 mac 1009a310 Villager::GetHoldLoweringMultiplier(void)
float Villager::GetHoldLoweringMultiplier()
{
    return 0;
}

// win1.41 00751040 mac 1056f5e0 Villager::Birthday(void)
void Villager::Birthday()
{
}

// win1.41 00751f00 mac 10064360 Villager::GetTown(void)
Town* Villager::GetTown()
{
    return *(Town**)((char*)this + 0x12c);
}

// win1.41 007528b0 mac 1056b830 Villager::DebugShowTime(unsigned long, unsigned char, unsigned char)
uint32_t Villager::DebugShowTime(uint32_t param_1, uint8_t param_2, uint8_t param_3)
{
    return (*(uint32_t (__fastcall **)(Villager*))((char*)*(void**)this + 0xb04))(this);
}


Football* Villager::GetFootball()
{
    return (Football*)*(unsigned int *)((char *)this + 0x11c);
}

Abode* Villager::GetAbode()
{
    return (Abode*)*(unsigned int *)((char *)this + 0x128);
}
