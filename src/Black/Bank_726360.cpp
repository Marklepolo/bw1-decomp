#include "SpellIcon.h"
#include "SpellSeed.h"
#include "SpellSeedGraphic.h"



// win1.41 00726360 mac 10524cb0 SpellIcon::GetSpellSeedType(void)
extern "C" char GSpellSeedInfo_ARRAY_00d9d678[];
__declspec(naked) SPELL_SEED_TYPE SpellIcon::GetSpellSeedType()
{
    __asm {
            mov ecx, dword ptr [ecx + 0x00000080]
            sub ecx, offset GSpellSeedInfo_ARRAY_00d9d678
            mov eax, 0x51eb851f
            imul ecx
            mov eax, edx
            sar eax, 7
            mov ecx, eax
            shr ecx, 0x1f
            add eax, ecx
            ret
        }
}

// win1.41 00726420 mac 10524aa0 SpellIcon::GetOverwriteTapToolTip(void)
uint32_t SpellIcon::GetOverwriteTapToolTip()
{
    return *(uint32_t*)(*(char**)((char*)this + 0x00000080) + 0x00000184);
}

// win1.41 007265c0 mac 10524740 SpellIcon::Process(void)
uint32_t SpellIcon::Process()
{
    return (uint32_t)0x00000001;
}

// win1.41 00726e20 mac 10521520 SpellSeedGraphic::GetText(void)
const char* SpellSeedGraphic::GetText()
{
    return (const char*)0x00c226a8;
}

// win1.41 00726e30 mac 10521560 SpellSeedGraphic::GetSaveType(void)
uint32_t SpellSeedGraphic::GetSaveType()
{
    return (uint32_t)0x00000023;
}

// win1.41 00726e40 mac 105215a0 SpellSeedGraphic::GetDebugText(void)
char* SpellSeedGraphic::GetDebugText()
{
    return (char*)0x00c226b8;
}

// win1.41 00726e50 mac 10521480 SpellSeedGraphic::_dt(void)
SpellSeedGraphic::~SpellSeedGraphic()
{
}

// win1.41 00727340 mac 10522ce0 SpellSeedGraphic::GetScale(void)
float SpellSeedGraphic::GetScale()
{
    return *(float*)((char*)this + 0x54);
}

// win1.41 007276a0 mac 10522450 SpellSeedGraphic::GetPlayer(void)
GPlayer* SpellSeedGraphic::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x4c);
}

// win1.41 00727f50 mac 1052cc60 SpellSeed::IsSpellSeed(void)
bool32_t SpellSeed::IsSpellSeed()
{
    return (bool32_t)(this);
}

// win1.41 00727f60 mac 1052cc90 SpellSeed::HandShouldFeelWithMeshIntersect(void)
bool32_t SpellSeed::HandShouldFeelWithMeshIntersect()
{
    return (bool32_t)(0);
}

// win1.41 00727f70 mac 1052cce0 SpellSeed::GetCreatureBeliefType(void)
uint32_t SpellSeed::GetCreatureBeliefType()
{
    return (uint32_t)0x00000012;
}

// win1.41 00727f80 mac 1052cd20 SpellSeed::GetOrigin(void)
uint32_t SpellSeed::GetOrigin()
{
    return (uint32_t)0x00000002;
}

// win1.41 00727fa0 mac 1052cdb0 SpellSeed::GetSaveType(void)
uint32_t SpellSeed::GetSaveType()
{
    return (uint32_t)0x00000024;
}

// win1.41 00727fb0 mac 1052cdf0 SpellSeed::GetDebugText(void)
char* SpellSeed::GetDebugText()
{
    return (char*)0x00c22708;
}
