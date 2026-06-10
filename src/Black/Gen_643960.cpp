#include "PFootball.h"

bool32_t PFootball::IsPlaytimeStarted()
{
    return *(unsigned int *)((char *)this + 0x7c) == 0x3;
}
