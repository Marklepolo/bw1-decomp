#include "Data.h"
#include "DeadTree.h"
#include "Debug.h"
#include "FelledTree.h"
#include "Game.h"



// win1.41 00510610 mac 1056c340 GData::_dt(void)
GData::~GData()
{
}

// win1.41 00510630 mac 100c09f0 GGame::SetupDataTables(void)
__declspec(naked) void GGame::SetupDataTables()
{
    __asm {
            xor ecx, ecx
            mov eax, 0x00d41678
            L_00510637:
            mov dword ptr [eax], ecx
            add eax, 0x00000100
            inc ecx
            cmp eax, 0x00d44378
            jl L_00510637
            ret
        }
}

// win1.41 00510980 mac 100c0e80 DeadTree::IsAnyKindOfTree(void)
bool32_t DeadTree::IsAnyKindOfTree()
{
    return (bool32_t)(1);
}

// win1.41 00510990 mac 100c0ec0 DeadTree::IsDeadTree(void)
bool32_t DeadTree::IsDeadTree()
{
    return (bool32_t)(1);
}

// win1.41 005109a0 mac 100c0f00 DeadTree::InterfaceValidToTap(GInterfaceStatus *)
uint32_t DeadTree::InterfaceValidToTap(GInterfaceStatus* param_1)
{
    return (uint32_t)(0);
}

// win1.41 005109b0 mac 100c0f50 DeadTree::InterfaceTap(GInterfaceStatus *)
uint32_t DeadTree::InterfaceTap(GInterfaceStatus* param_1)
{
    return (uint32_t)(1);
}

// win1.41 005109c0 mac 100c0fa0 DeadTree::HandShouldFeelWithMeshIntersect(void)
bool32_t DeadTree::HandShouldFeelWithMeshIntersect()
{
    return (bool32_t)(0);
}

// win1.41 005109d0 mac inlined DeadTree::IsRock_0(void)
bool32_t DeadTree::IsRock()
{
    return 0;
}

// win1.41 005109e0 mac 100c4120 DeadTree::GetSaveType(void)
uint32_t DeadTree::GetSaveType()
{
    return (uint32_t)(0x70);
}

// win1.41 005109f0 mac 100c4160 DeadTree::GetDebugText(void)
char* DeadTree::GetDebugText()
{
    return (char*)(0xbe8a40);
}

// win1.41 00510a00 mac 100c19c0 DeadTree::_dt(void)
DeadTree::~DeadTree()
{
}

// win1.41 00510e20 mac 100c2ef0 DeadTree::StartOnFire(void)
extern "C" void jmp_addr_0x006e4750(void);
__declspec(naked) void DeadTree::StartOnFire()
{
    __asm {
            push ecx
            call jmp_addr_0x006e4750
            pop ecx
            ret
        }
}

// win1.41 005110c0 mac 100c28d0 DeadTree::GetResourceType(void)
RESOURCE_TYPE DeadTree::GetResourceType()
{
    return (RESOURCE_TYPE)1;
}

// win1.41 005110d0 mac 100c2890 DeadTree::GetHoldType(void)
HOLD_TYPE DeadTree::GetHoldType()
{
    return HOLD_TYPE_TREE;
}

// win1.41 005110f0 mac 100c27d0 DeadTree::GetHoldLoweringMultiplier(void)
float DeadTree::GetHoldLoweringMultiplier()
{
    return 0.10000000149011612f;
}

// win1.41 005111f0 mac 100c2490 DeadTree::InteractsWithPhysicsObjects(void)
bool32_t DeadTree::InteractsWithPhysicsObjects()
{
    __asm { mov al, 1 }
}

// win1.41 00511200 mac 100c2450 DeadTree::IsARootedObject(void)
bool32_t DeadTree::IsARootedObject()
{
    return (bool32_t)(0);
}

// win1.41 005115b0 mac 100c1c10 DeadTree::GetScriptObjectType(void)
uint32_t DeadTree::GetScriptObjectType()
{
    return (uint32_t)(0xd);
}

// win1.41 005118c0 mac 100c0da0 FelledTree::GetSaveType(void)
uint32_t FelledTree::GetSaveType()
{
    return (uint32_t)(0x71);
}

// win1.41 005118d0 mac 100c0de0 FelledTree::GetDebugText(void)
char* FelledTree::GetDebugText()
{
    return (char*)(0xbe8a6c);
}

// win1.41 005118e0 mac 100c0cc0 FelledTree::_dt(void)
FelledTree::~FelledTree()
{
}

// win1.41 00511a10 mac 100c1250 DeadTree::CanBecomeAPhysicsObject(void)
bool32_t DeadTree::CanBecomeAPhysicsObject()
{
    return (bool32_t)(1);
}


IMMERSION_EFFECT_TYPE DeadTree::GetInHandImmersionTexture()
{
    return Object::GetInHandImmersionTexture();
}
