#include "PSysPCreator.h"
#include "PSysPCreator.h"
#include "Chain.h"
#include "DefensiveShield.h"
#include "DefensiveSphere.h"
#include "FireGraphic.h"
#include "JPSysInterface.h"
#include "PSysManager.h"
#include "PSysSound.h"
#include "Particle3DAnim.h"
#include "Particle3DAnimWithCamera.h"
#include "Particle3DObjAnimTextured.h"
#include "Particle3DPnt.h"
#include "ParticleChainJoint.h"
#include "ParticleLightMap.h"
#include "ParticlePlayerSymbol.h"
#include "SpellPointInf.h"



// win1.41 006c87f0 mac 10422ad0 Chain::GetSaveType(void)
uint32_t Chain::GetSaveType()
{
    return (uint32_t)(0xb6);
}

// win1.41 006c8800 mac 10422b00 Chain::GetDebugText(void)
char* Chain::GetDebugText()
{
    return (char*)(0x9ceaa8);
}

// win1.41 006ca440 mac 10423650 ParticleLightMap::GetDebugText(void)
char* ParticleLightMap::GetDebugText()
{
    return (char*)(0x9ceaa8);
}

// win1.41 006d0ab0 mac 1041dbe0 DefensiveShield::GetSaveType(void)
uint32_t DefensiveShield::GetSaveType()
{
    return (uint32_t)(0);
}

// win1.41 006d0ac0 mac 1041dc20 DefensiveShield::GetDebugText(void)
char* DefensiveShield::GetDebugText()
{
    return (char*)(0x9ceaa8);
}

// win1.41 006d0ce0 mac 10417610 DefensiveSphere::GetSaveType(void)
uint32_t DefensiveSphere::GetSaveType()
{
    return (uint32_t)(0xb7);
}

// win1.41 006d0cf0 mac 10417650 DefensiveSphere::GetDebugText(void)
char* DefensiveSphere::GetDebugText()
{
    return (char*)(0x9ceaa8);
}

// win1.41 006d0f30 mac 10486940 PSysSound::GetSaveType(void)
uint32_t PSysSound::GetSaveType()
{
    return (uint32_t)(0x16);
}

// win1.41 006d0f40 mac 10486980 PSysSound::GetDebugText(void)
char* PSysSound::GetDebugText()
{
    return (char*)(0xc09778);
}


char* RenderParticleMist::GetDebugText()
{
    return (char*)0x9ceaa8;
}

char* RenderParticleGameObject::GetDebugText()
{
    return (char*)0x9ceaa8;
}
