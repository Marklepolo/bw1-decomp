#include "PlannedMultiMapFixed.h"
#include "Player.h"
#include "PlayerInfo.h"



// win1.41 00648940 mac 10115200 PlannedMultiMapFixed::GetText(void)
const char* PlannedMultiMapFixed::GetText()
{
    return (const char*)(*(uint32_t*)((char*)this + 0x40) + 0x18);
}

// win1.41 00648eb0 mac 10497380 GPlayer::_dt(void)
GPlayer::~GPlayer()
{
}

// win1.41 0064b670 mac 1002b8e0 GPlayer::GetMaxAlignmentChangePerGameTurn(void)
float GPlayer::GetMaxAlignmentChangePerGameTurn()
{
    return *(float*)(*(char**)((char*)this + 0x64) + 0x10);
}
