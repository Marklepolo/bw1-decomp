#include "Artifact.h"

void TownArtifact::SetPlayer(GPlayer* param_1)
{
    *(unsigned int *)((char *)this + 0x24) = (unsigned int)param_1;
}
