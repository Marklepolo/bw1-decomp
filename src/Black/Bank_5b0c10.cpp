#include "HandState.h"
#include "HandStateCamera.h"
#include "HandStateCitadel.h"
#include "HandStateCreature.h"
#include "HandStateGrain.h"
#include "HandStateHolding.h"
#include "Living.h"



// win1.41 005b0c10 mac 10337710 HandStateCitadel::Enter(void)
__declspec(naked) void HandStateCitadel::Enter()
{
    __asm {
            xor eax, eax
            mov dword ptr [ecx + 0x14], eax
            mov dword ptr [ecx + 0x10], eax
            mov dword ptr [ecx + 0x2c], eax
            mov dword ptr [ecx + 0x28], eax
            mov dword ptr [ecx + 0x24], eax
            mov dword ptr [ecx + 0x3c], eax
            mov dword ptr [ecx + 0x38], eax
            mov dword ptr [ecx + 0x20], eax
            mov dword ptr [ecx + 0x34], eax
            mov dword ptr [ecx + 0x1c], eax
            mov dword ptr [ecx + 0x30], eax
            mov dword ptr [ecx + 0x18], eax
            mov dword ptr [ecx + 0x58], eax
            mov dword ptr [ecx + 0x54], eax
            mov dword ptr [ecx + 0x6c], eax
            mov dword ptr [ecx + 0x68], eax
            mov dword ptr [ecx + 0x50], eax
            mov dword ptr [ecx + 0x64], eax
            mov dword ptr [ecx + 0x4c], eax
            mov dword ptr [ecx + 0x60], eax
            mov dword ptr [ecx + 0x48], eax
            mov edx, 0x3f800000
            mov dword ptr [ecx + 0x44], edx
            mov dword ptr [ecx + 0x40], edx
            mov dword ptr [ecx + 0x5c], edx
            mov dword ptr [ecx + 0x74], eax
            mov dword ptr [ecx + 0x70], eax
            mov dword ptr [ecx + 0x0000008c], eax
            mov dword ptr [ecx + 0x00000088], eax
            mov dword ptr [ecx + 0x00000084], eax
            mov dword ptr [ecx + 0x0000009c], eax
            mov dword ptr [ecx + 0x00000098], eax
            mov dword ptr [ecx + 0x00000080], eax
            mov dword ptr [ecx + 0x00000094], eax
            mov dword ptr [ecx + 0x7c], eax
            mov dword ptr [ecx + 0x00000090], eax
            mov dword ptr [ecx + 0x78], eax
            mov edx, dword ptr [ecx + 0x04]
            mov dword ptr [ecx + 0x08], eax
            mov dword ptr [ecx + 0x0c], eax
            fld dword ptr [edx + 0x00004854]
            fst dword ptr [ecx + 0x000000a4]
            mov dword ptr [ecx + 0x000000b8], eax
            fst dword ptr [ecx + 0x000000a0]
            mov dword ptr [ecx + 0x000000b4], eax
            fstp dword ptr [ecx + 0x000000bc]
            mov dword ptr [ecx + 0x000000cc], eax
            mov dword ptr [ecx + 0x000000c8], eax
            mov dword ptr [ecx + 0x000000b0], eax
            mov dword ptr [ecx + 0x000000c4], eax
            mov dword ptr [ecx + 0x000000ac], eax
            mov dword ptr [ecx + 0x000000c0], eax
            mov dword ptr [ecx + 0x000000a8], eax
            ret
        }
}
