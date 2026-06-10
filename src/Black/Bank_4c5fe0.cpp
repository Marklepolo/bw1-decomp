#include "Creature.h"
#include "CreatureAttitudeToPlayer.h"



// win1.41 004c5fe0 mac 102345e0 Creature::FightThisToObject(GInterfaceStatus *, Object *)
extern "C" void jmp_addr_0x004c5ff0(void);
__declspec(naked) uint32_t Creature::FightThisToObject(GInterfaceStatus* param_1, Object* param_2)
{
    __asm {
            mov eax, dword ptr [esp + 0x08]
            push eax
            call jmp_addr_0x004c5ff0
            ret 8
        }
}

// win1.41 004c81a0 mac 10235cc0 CreatureAttitudeToPlayer::_dt(void)
CreatureAttitudeToPlayer::~CreatureAttitudeToPlayer()
{
}
