#include "Creature.h"



// win1.41 0047d810 mac 101cf1e0 Creature::SetSpeedInMetres(float, int)
extern "C" void jmp_addr_0x0047fa20(void);
__declspec(naked) void Creature::SetSpeedInMetres(float param_1, int param_2)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            mov ecx, dword ptr [ecx + 0x00000160]
            mov ecx, dword ptr [ecx + 0x58]
            push eax
            call jmp_addr_0x0047fa20
            ret 8
        }
}

// win1.41 0047d940 mac 101cef30 Creature::GetQueryLastEnumText(void)
HELP_TEXT Creature::GetQueryLastEnumText()
{
    return this->GetQueryFirstEnumText();
}
