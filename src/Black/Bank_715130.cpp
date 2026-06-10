#include "Setup.h"



// win1.41 00715130 mac 1050c350 GSetup::GetCommandAsText(SCRIPT_FEATURE_COMMANDS)
extern "C" void jmp_addr_0x007e7fb0(void);
__declspec(naked) char* GSetup::GetCommandAsText(SCRIPT_FEATURE_COMMANDS param_1)
{
    __asm {
            mov ecx, dword ptr [esp + 0x04]
            shl ecx, 4
            push 0x00d99388
            add ecx, 0x00c20f00
            call jmp_addr_0x007e7fb0
            ret
        }
}
