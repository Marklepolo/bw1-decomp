#include "Animal.h"
#include "Creature.h"
#include "Villager.h"



// win1.41 004eabd0 mac 1026e380 Animal::GetCreatureMimicType(void)
__declspec(naked) uint32_t Animal::GetCreatureMimicType()
{
    __asm {
            mov eax, dword ptr [ecx + 0x28]
            mov eax, dword ptr [eax + 0x14]
            dec eax
            neg eax
            sbb eax, eax
            add eax, 0x04
            ret
        }
}
