#include "Creature.h"



// win1.41 00476dc0 mac 101dc510 Creature::ValidToSelectFightThisToMapCoord(GInterfaceStatus *, MapCoords const &)
extern "C" void jmp_addr_0x0047b1c0(void);
__declspec(naked) uint32_t Creature::ValidToSelectFightThisToMapCoord(GInterfaceStatus* param_1, const MapCoords* param_2)
{
    __asm {
            call jmp_addr_0x0047b1c0
            neg eax
            sbb eax, eax
            neg eax
            ret 8
        }
}

// win1.41 00476eb0 mac 101dc160 Creature::IsReadyForNetworkUnfriendlyLockedSelect(void)
bool32_t Creature::IsReadyForNetworkUnfriendlyLockedSelect()
{
    return *(int*)((char*)this + 0x3cc) == 0;
}

// win1.41 00476ec0 mac 101dc100 Creature::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo *)
bool32_t Creature::NetworkUnfriendlyLockedSelect(ControlHandUpdateInfo* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00476ed0 mac 101dc060 Creature::GetReadyForNetworkUnfriendlyEndLockedSelect(void)
extern "C" void jmp_addr_0x004806d0(void);
__declspec(naked) bool32_t Creature::GetReadyForNetworkUnfriendlyEndLockedSelect()
{
    __asm {
            mov eax, dword ptr [ecx + 0x00000160]
            mov eax, dword ptr [eax + 0x58]
            add eax, 0x000048c0
            xor edx, edx
            mov dword ptr [eax + 0x08], edx
            mov dword ptr [eax + 0x04], edx
            mov dword ptr [eax], edx
            mov ecx, dword ptr [ecx + 0x00000160]
            mov ecx, dword ptr [ecx + 0x58]
            call jmp_addr_0x004806d0
            mov eax, 0x00000001
            ret
        }
}

// win1.41 00476f60 mac 101dbf40 Creature::NetworkUnfriendlyEndLockedSelect(void)
bool32_t Creature::NetworkUnfriendlyEndLockedSelect()
{
    return (bool32_t)(1);
}

// win1.41 00477850 mac 101daef0 Creature::GetCreature3D(void)
LH3DCreature* Creature::GetCreature3D()
{
    return *(LH3DCreature**)((char*)*(void**)((char*)this + 0x160) + 0x58);
}

// win1.41 00477df0 mac 101da380 Creature::GetCreatureBeliefListType(void)
uint32_t Creature::GetCreatureBeliefListType()
{
    return (uint32_t)(0);
}

// win1.41 00477e10 mac 101da2c0 Creature::GetImpressiveType(void)
extern "C" void jmp_addr_0x00477e00(void);
__declspec(naked) IMPRESSIVE_TYPE Creature::GetImpressiveType()
{
    __asm {
            call jmp_addr_0x00477e00
            mov ecx, eax
            shl ecx, 4
            add ecx, eax
            shl ecx, 4
            mov eax, dword ptr [ecx + 0x00c6c4ac]
            ret
        }
}
