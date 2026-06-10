#include "MagicFood.h"
#include "MagicHand.h"
#include "MagicInfo.h"



// win1.41 005fa970 mac 103abdc0 MagicFood::SetPlayer(GPlayer *)
void MagicFood::SetPlayer(GPlayer* param_1)
{
    *(uint32_t*)((char*)this + 0x000000bc) = (uint32_t)param_1;
}

// win1.41 005fa980 mac 103abe00 MagicFood::GetPlayer(void)
GPlayer* MagicFood::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x000000bc);
}

// win1.41 005fa990 mac 103abe40 MagicFood::GetImpressiveType(void)
IMPRESSIVE_TYPE MagicFood::GetImpressiveType()
{
    return IMPRESSIVE_TYPE_MAGIC_FOOD;
}

// win1.41 005fa9a0 mac 103abe80 MagicFood::GetSaveType(void)
uint32_t MagicFood::GetSaveType()
{
    return (uint32_t)0x0000001e;
}

// win1.41 005fa9b0 mac 103abec0 MagicFood::GetDebugText(void)
char* MagicFood::GetDebugText()
{
    return (char*)0x00bf3e04;
}

// win1.41 005fa9c0 mac 103ac0d0 MagicFood::_dt(void)
MagicFood::~MagicFood()
{
}

// win1.41 005faf20 mac 103acd40 GMagicHand::GetSaveType(void)
uint32_t GMagicHand::GetSaveType()
{
    return (uint32_t)0x000000fd;
}

// win1.41 005faf30 mac 103acd80 GMagicHand::GetDebugText(void)
char* GMagicHand::GetDebugText()
{
    return (char*)0x00bf3e74;
}

// win1.41 005faf40 mac 103ad580 GMagicHand::_dt(void)
GMagicHand::~GMagicHand()
{
}

// win1.41 005fb2a0 mac 103acf80 GMagicHand::CleanUpForSerialisation(void)
__declspec(naked) void GMagicHand::CleanUpForSerialisation()
{
    __asm {
            xor eax, eax
            mov al, byte ptr [ecx + 0x14]
            cmp eax, 0x01
            jge L_005fb2bb
            push edi
            lea edi, dword ptr [ecx + eax * 0x4 + 0x18]
            mov ecx, 0x00000001
            sub ecx, eax
            xor eax, eax
            rep stosd
            pop edi
            L_005fb2bb:
            ret
        }
}
