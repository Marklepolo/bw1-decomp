#include "PuzzleGame.h"

uint32_t PuzzleTortoise::GetSaveType()
{
    return (uint32_t)0x2d;
}

char* PuzzleTortoise::GetDebugText()
{
    return (char*)0xbee238;
}

bool32_t PuzzleTortoise::CanBecomeAPhysicsObject()
{
    return (bool32_t)0;
}
