#include "MagicFireBall.h"
#include "MagicFireBallInfo.h"



// win1.41 00682a40 mac 103fcf30 MagicFireBall::IsTuggable(void)
bool32_t MagicFireBall::IsTuggable()
{
    return (bool32_t)(0);
}

// win1.41 00682a50 mac 103fcf70 MagicFireBall::IsMagicFireBall(void)
bool32_t MagicFireBall::IsMagicFireBall()
{
    return (bool32_t)(this);
}

// win1.41 00682a60 mac 103fcfb0 MagicFireBall::InteractsWithPhysicsObjects(void)
bool32_t MagicFireBall::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00682a70 mac 103fd000 MagicFireBall::CanBecomeAPhysicsObject(void)
bool32_t MagicFireBall::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 00682a80 mac 103fd050 MagicFireBall::CanBePickedUpByCreature(Creature *)
bool32_t MagicFireBall::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682a90 mac 103fd0a0 MagicFireBall::CanBeSetOnFire(Creature *)
bool32_t MagicFireBall::CanBeSetOnFire(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682aa0 mac 103fd0f0 MagicFireBall::CanBeStompedOnByCreature(Creature *)
bool32_t MagicFireBall::CanBeStompedOnByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682ab0 mac 103fd140 MagicFireBall::CanBeThrownByCreature(Creature *)
bool32_t MagicFireBall::CanBeThrownByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682ac0 mac 103fd190 MagicFireBall::CanBePutInAStoragePit(Creature *)
bool32_t MagicFireBall::CanBePutInAStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682ad0 mac 103fd1e0 MagicFireBall::CanBeDestroyedByStoning(Creature *)
bool32_t MagicFireBall::CanBeDestroyedByStoning(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682ae0 mac 103fd230 MagicFireBall::CanBeStonedAndEatenByCreature(Creature *)
bool32_t MagicFireBall::CanBeStonedAndEatenByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682af0 mac 103fd290 MagicFireBall::CanBeExaminedByCreature(Creature *)
bool32_t MagicFireBall::CanBeExaminedByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682b00 mac 103fd2e0 MagicFireBall::CanBeFoughtByCreature(Creature *)
bool32_t MagicFireBall::CanBeFoughtByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682b10 mac 103fd330 MagicFireBall::CanActAsAContainer(Creature *)
bool32_t MagicFireBall::CanActAsAContainer(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00682b30 mac 103fd3d0 MagicFireBall::GetSaveType(void)
uint32_t MagicFireBall::GetSaveType()
{
    return (uint32_t)(0x20);
}

// win1.41 00682b40 mac 103fd410 MagicFireBall::GetDebugText(void)
char* MagicFireBall::GetDebugText()
{
    return (char*)(0xc02424);
}

// win1.41 00682b50 mac 103fca00 MagicFireBall::_dt(void)
MagicFireBall::~MagicFireBall()
{
}

// win1.41 00682d10 mac 103fc710 MagicFireBall::InsertMapObject(void)
void MagicFireBall::InsertMapObject()
{
}

// win1.41 00682d30 mac 103fc650 MagicFireBall::GetHeight(void)
float MagicFireBall::GetHeight()
{
    return this->Get2DRadius();
}

// win1.41 00682d90 mac 103fc520 MagicFireBall::GetFireGPHXDrawn(bool *, bool *, bool *, bool *)
__declspec(naked) void MagicFireBall::GetFireGPHXDrawn(bool* param_1, bool* param_2, bool* param_3, bool* param_4)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            mov ecx, dword ptr [esp + 0x0c]
            mov edx, dword ptr [esp + 0x08]
            mov byte ptr [eax], 0x00
            mov eax, dword ptr [esp + 0x10]
            mov byte ptr [ecx], 0x01
            mov byte ptr [edx], 0x00
            mov byte ptr [eax], 0x00
            ret 16
        }
}

// win1.41 00682e40 mac 103fc2d0 MagicFireBall::InterfaceValidToTap(GInterfaceStatus *)
uint32_t MagicFireBall::InterfaceValidToTap(GInterfaceStatus* param_1)
{
    return (uint32_t)(1);
}
