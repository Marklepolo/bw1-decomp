#include "DialogBoxBase.h"
#include "DialogBoxOptions.h"



// win1.41 00513810 mac 102b5740 DialogBoxOptions::DialogBoxOptions(void)
DialogBoxOptions::DialogBoxOptions()
{
}

// win1.41 00513830 mac 102b5900 DialogBoxOptions::CanESCOut(void)
extern "C" char game[];
__declspec(naked) bool32_t DialogBoxOptions::CanESCOut()
{
    __asm {
            mov eax, dword ptr [game]
            mov ecx, dword ptr [eax + 0x00250304]
            mov eax, dword ptr [ecx + 0x5c]
            sub eax, dword ptr [ecx + 0x54]
            neg eax
            sbb eax, eax
            inc eax
            ret
        }
}
