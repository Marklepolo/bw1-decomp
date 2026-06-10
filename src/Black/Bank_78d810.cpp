#include "GameOptionsRoom.h"



// win1.41 0078d810 mac 10300060 GameOptionsRoom::Draw(void)
extern "C" void jmp_addr_0x0078f1f0(void);
__declspec(naked) void GameOptionsRoom::Draw()
{
    __asm {
            jmp jmp_addr_0x0078f1f0
        }
}

// win1.41 0078d820 mac 102fffd0 GameOptionsRoom::UpdateMouse(LHCoord, INTERFACE_MESSAGE_TYPES)
extern "C" void jmp_addr_0x0078f5e0(void);
__declspec(naked) void GameOptionsRoom::UpdateMouse(LHCoord param_1, INTERFACE_MESSAGE_TYPES param_2)
{
    __asm {
            mov eax, dword ptr [esp + 0x0c]
            mov edx, dword ptr [esp + 0x08]
            push eax
            mov eax, dword ptr [esp + 0x08]
            push edx
            push eax
            call jmp_addr_0x0078f5e0
            ret 12
        }
}

// win1.41 0078d840 mac 102fff70 GameOptionsRoom::UpdateKeyboard(LH_KEY, unsigned short)
extern "C" void jmp_addr_0x0078f600(void);
__declspec(naked) void GameOptionsRoom::UpdateKeyboard(LH_KEY param_1, uint16_t param_2)
{
    __asm {
            mov eax, dword ptr [esp + 0x08]
            mov edx, dword ptr [esp + 0x04]
            push eax
            push edx
            call jmp_addr_0x0078f600
            ret 8
        }
}
