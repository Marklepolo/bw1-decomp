#include "Artifact.h"

Town* TownArtifact::GetTown()
{
    return (Town*)*(unsigned int *)((char *)this + 0x18);
}
