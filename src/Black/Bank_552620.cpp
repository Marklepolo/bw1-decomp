#include "Game.h"



// win1.41 00552620 mac 1005cfb0 GGame::GetTribe(TRIBE_TYPE)
extern "C" char GTribeInfo_ARRAY_00da57a8[];
__declspec(naked) GTribeInfo* GGame::GetTribe(TRIBE_TYPE type)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            lea ecx, dword ptr [eax * 0x8 + 0x00000000]
            sub ecx, eax
            lea eax, dword ptr [ecx * 0x4 + GTribeInfo_ARRAY_00da57a8]
            ret 4
        }
}
