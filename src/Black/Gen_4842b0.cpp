#include "CreatureMorph.h"

bool LH3DCreature::IsPerformingBodyAction()
{
    return *(unsigned int *)((char *)this + 0x4994) != 0;
}
