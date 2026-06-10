#include "Wonder.h"

void Wonder::SetPower(float param_1)
{
    *(float *)((char *)this + 0xc4) = param_1;
}
