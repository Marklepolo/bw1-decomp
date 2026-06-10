#include "CreatureMorph.h"

uint32_t LH3DCreature::GetObjectActionStatus()
{
    return (uint32_t)*(unsigned int *)((char *)this + 0x4998);
}
