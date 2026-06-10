#include "GameOSFile.h"
#include "GameStats.h"
#include "SaveLoadPtr.h"



// win1.41 00564ac0 mac 103109d0 GameStats::GetPlayer(void)
GPlayer* GameStats::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x14);
}

// win1.41 00564ad0 mac 10310a10 GameStats::SetPlayer(GPlayer *)
void GameStats::SetPlayer(GPlayer* param_1)
{
    *(uint32_t*)((char*)this + 0x14) = (uint32_t)param_1;
}

// win1.41 00564af0 mac 10310a90 GameStats::GetDebugText(void)
char* GameStats::GetDebugText()
{
    return (char*)0x00bee588;
}
