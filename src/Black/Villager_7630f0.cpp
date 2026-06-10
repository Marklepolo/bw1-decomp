#include "Town.h"
#include "Villager.h"



// win1.41 007630f0 mac 1058c170 Villager::CheckPlaytimeAvailableToPlayPFootball(void)
bool32_t Villager::CheckPlaytimeAvailableToPlayPFootball()
{
    return true;
}

// win1.41 00764310 mac 10592770 Villager::FleeingAndLookingAtObjectReaction(void)
bool32_t Villager::FleeingAndLookingAtObjectReaction()
{
    return (*(bool32_t (__fastcall **)(Villager*))((char*)*(void**)this + 0x88c))(this);
}
