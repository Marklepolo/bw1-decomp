#include "SpellSeed.h"



// win1.41 00728660 mac 1052b950 SpellSeed::GetHoldLoweringMultiplier(void)
float SpellSeed::GetHoldLoweringMultiplier()
{
    return *(float*)(*(char**)((char*)this + 0x28) + 0x0000014c);
}

// win1.41 00728670 mac 1052b8f0 SpellSeed::GetHoldYRotate(void)
float SpellSeed::GetHoldYRotate()
{
    return *(float*)(*(char**)((char*)this + 0x28) + 0x00000154);
}

// win1.41 007286a0 mac 1052b830 SpellSeed::IsInterfacePowerUpWhenInHand( const(void))
bool32_t SpellSeed::IsInterfacePowerUpWhenInHand() const
{
    return (bool32_t)(1);
}

// win1.41 007286b0 mac 1052b7c0 SpellSeed::ApplyOnlyAfterRecSystem(void)
extern "C" void jmp_addr_0x007290e0(void);
__declspec(naked) uint32_t SpellSeed::ApplyOnlyAfterRecSystem()
{
    __asm {
            call jmp_addr_0x007290e0
            mov edx, dword ptr [eax + 0x00000110]
            xor ecx, ecx
            cmp edx, 0x01
            sete cl
            mov eax, ecx
            ret
        }
}

// win1.41 00728f30 mac 1052a420 SpellSeed::InsertMapObject(void)
void SpellSeed::InsertMapObject()
{
}

// win1.41 00728f40 mac 1052a3e0 SpellSeed::RemoveMapObject(void)
void SpellSeed::RemoveMapObject()
{
}
