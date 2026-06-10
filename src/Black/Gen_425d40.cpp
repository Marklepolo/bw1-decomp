#include "Artifact.h"

GPlayer* TownArtifact::GetPlayer()
{
    return (GPlayer*)*(unsigned int *)((char *)this + 0x24);
}
