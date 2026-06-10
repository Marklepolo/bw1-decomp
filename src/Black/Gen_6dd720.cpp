#include "PuzzleGame.h"

uint32_t PuzzlePig::GetSaveType()
{
    return (uint32_t)0x2d;
}

char* PuzzlePig::GetDebugText()
{
    return (char*)0xbee238;
}

bool32_t PuzzlePig::CanBecomeAPhysicsObject()
{
    return (bool32_t)0;
}
