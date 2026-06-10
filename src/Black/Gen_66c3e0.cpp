#include "PlaytimeDance.h"

Town* PlaytimeElement::GetTown()
{
    return (Town*)*(unsigned int *)((char *)this + 0x3c);
}
