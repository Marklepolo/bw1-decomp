#include "PlayerComputer.h"

uint32_t GComputerPlayerQueue::GetSaveType()
{
    return (uint32_t)0x10c;
}

char* GComputerPlayerQueue::GetDebugText()
{
    return (char*)0xbee2f4;
}
