#include "MagicVortex.h"
#include "MagicVortex.h"
#include "MagicVortex.h"
#include "MagicVortex.h"
#include "MagicVortex.h"
#include "MagicVortex.h"
#include "MagicVortex.h"
#include "MagicInfo.h"
#include "MagicLivingInfo.h"
#include "MagicTeleport.h"
#include "MagicTree.h"
#include "MagicWood.h"
#include "Map.h"
#include "MobileObject.h"
#include "MobileStaticInfo.h"
#include "SpellTeleport.h"
#include "VortexInfo.h"
#include "VortexObjectInfo.h"



// win1.41 005fb980 mac inlined GMagicLivingInfo::_dt(void)
GMagicLivingInfo::~GMagicLivingInfo()
{
}

// win1.41 005fc040 mac 103aed40 MagicTeleport::CanBePickedUpByCreature(Creature *)
bool32_t MagicTeleport::CanBePickedUpByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 005fc050 mac 103aed90 MagicTeleport::CanBeSetOnFire(Creature *)
bool32_t MagicTeleport::CanBeSetOnFire(Creature* param_1)
{
    return 0;
}

// win1.41 005fc060 mac 103aede0 MagicTeleport::CanBeStompedOnByCreature(Creature *)
bool32_t MagicTeleport::CanBeStompedOnByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 005fc070 mac 103aee30 MagicTeleport::CanBeThrownByCreature(Creature *)
bool32_t MagicTeleport::CanBeThrownByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 005fc080 mac 103aee80 MagicTeleport::CanBePutInAStoragePit(Creature *)
bool32_t MagicTeleport::CanBePutInAStoragePit(Creature* param_1)
{
    return 0;
}

// win1.41 005fc090 mac 103aeed0 MagicTeleport::CanBeDestroyedByStoning(Creature *)
bool32_t MagicTeleport::CanBeDestroyedByStoning(Creature* param_1)
{
    return 0;
}

// win1.41 005fc0a0 mac 103aef20 MagicTeleport::CanBeStonedAndEatenByCreature(Creature *)
bool32_t MagicTeleport::CanBeStonedAndEatenByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 005fc0b0 mac 103aef80 MagicTeleport::CanBeExaminedByCreature(Creature *)
bool32_t MagicTeleport::CanBeExaminedByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 005fc0c0 mac 103aefd0 MagicTeleport::CanBeFoughtByCreature(Creature *)
bool32_t MagicTeleport::CanBeFoughtByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 005fc0d0 mac 103af020 MagicTeleport::CanActAsAContainer(Creature *)
bool32_t MagicTeleport::CanActAsAContainer(Creature* param_1)
{
    return 0;
}

// win1.41 005fc0e0 mac 103af070 MagicTeleport::GetSaveType(void)
uint32_t MagicTeleport::GetSaveType()
{
    return (uint32_t)0x00000019;
}

// win1.41 005fc0f0 mac 103af0b0 MagicTeleport::GetDebugText(void)
char* MagicTeleport::GetDebugText()
{
    return (char*)0x00bf3f08;
}

// win1.41 005fc100 mac 103b0b60 MagicTeleport::_dt(void)
MagicTeleport::~MagicTeleport()
{
}

// win1.41 005fc430 mac 103b0660 MagicTeleport::GetPlayer(void)
GPlayer* MagicTeleport::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x000000a0);
}

// win1.41 005fc470 mac 103b0500 MagicTeleport::InterfaceSetInMagicHand(GInterfaceStatus *)
extern "C" void jmp_addr_0x005dc870(void);
__declspec(naked) bool32_t MagicTeleport::InterfaceSetInMagicHand(GInterfaceStatus* param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x0000009c]
            test eax, eax
            je L_005fc48e
            mov eax, dword ptr [eax + 0x000000ac]
            test eax, eax
            je L_005fc48e
            mov ecx, dword ptr [esp + 0x04]
            push eax
            call jmp_addr_0x005dc870
            L_005fc48e:
            xor eax, eax
            ret 4
        }
}

// win1.41 005fc4a0 mac 103b04c0 MagicTeleport::IsSolidToNewAbode(void)
bool32_t MagicTeleport::IsSolidToNewAbode()
{
    return (bool32_t)0x00000001;
}

// win1.41 005fcde0 mac 103af230 MagicTeleport::InteractsWithPhysicsObjects(void)
bool32_t MagicTeleport::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 005fcdf0 mac 103af1e0 MagicTeleport::CanBecomeAPhysicsObject(void)
bool32_t MagicTeleport::CanBecomeAPhysicsObject()
{
    return 0;
}

// win1.41 005fce00 mac 103af190 MagicTeleport::IsEffectReceiver(EffectValues *)
bool32_t MagicTeleport::IsEffectReceiver(EffectValues* param_1)
{
    return 0;
}

// win1.41 005fcf00 mac 103b2330 MagicTree::GetImpressiveType(void)
IMPRESSIVE_TYPE MagicTree::GetImpressiveType()
{
    return IMPRESSIVE_TYPE_MAGIC_TREE;
}

// win1.41 005fcf10 mac 103b2370 MagicTree::GetSaveType(void)
uint32_t MagicTree::GetSaveType()
{
    return (uint32_t)0x0000001d;
}

// win1.41 005fcf20 mac 103b23b0 MagicTree::GetDebugText(void)
char* MagicTree::GetDebugText()
{
    return (char*)0x00bf3f30;
}

// win1.41 005fcf30 mac 103b22a0 MagicTree::_dt(void)
MagicTree::~MagicTree()
{
}

// win1.41 005fd0d0 mac 103b26d0 MagicTree::StartOnFire(void)
extern "C" void jmp_addr_0x006e4780(void);
__declspec(naked) void MagicTree::StartOnFire()
{
    __asm {
            push 0x8
            push ecx
            call jmp_addr_0x006e4780
            add esp, 0x08
            ret
        }
}

// win1.41 005fd390 mac 103b9150 GVortexInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GVortexInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000003;
    return (GBaseInfo*)0x00d38248;
}

// win1.41 005fd3f0 mac 103b8d80 GVortexInfo::_dt(void)
GVortexInfo::~GVortexInfo()
{
}

// win1.41 00600da0 mac 103b9ed0 MagicWood::GetPlayer(void)
GPlayer* MagicWood::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x000000b4);
}

// win1.41 00600db0 mac 103b9f10 MagicWood::GetImpressiveType(void)
IMPRESSIVE_TYPE MagicWood::GetImpressiveType()
{
    return IMPRESSIVE_TYPE_MAGIC_WOOD;
}

// win1.41 00600dc0 mac 103b9f50 MagicWood::IsAWoodPileOutsideStoragePit(Creature *)
bool32_t MagicWood::IsAWoodPileOutsideStoragePit(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00600dd0 mac 103b9fa0 MagicWood::GetSaveType(void)
uint32_t MagicWood::GetSaveType()
{
    return (uint32_t)0x0000001f;
}

// win1.41 00600de0 mac 103b9fe0 MagicWood::GetDebugText(void)
char* MagicWood::GetDebugText()
{
    return (char*)0x00bf4128;
}

// win1.41 00600df0 mac 103ba240 MagicWood::_dt(void)
MagicWood::~MagicWood()
{
}

// win1.41 006010c0 mac 1055f620 GMap::_dt(void)
GMap::~GMap()
{
}


uint32_t LandscapeVortexVolc::GetSaveType()
{
    return (uint32_t)0x1a;
}

char* LandscapeVortexVolc::GetDebugText()
{
    return (char*)0xbf4084;
}

uint32_t LandscapeVortexIn::GetSaveType()
{
    return (uint32_t)0x1b;
}

char* LandscapeVortexIn::GetDebugText()
{
    return (char*)0xbf40b8;
}

uint32_t LandscapeVortexIn::GetPhysicsConstantsType()
{
    return (uint32_t)0xd;
}

uint32_t LandscapeVortexOut::GetSaveType()
{
    return (uint32_t)0x1c;
}

char* LandscapeVortexOut::GetDebugText()
{
    return (char*)0xbf40fc;
}


bool32_t LandscapeVortexIn::InteractsWithPhysicsObjects()
{
    __asm { mov al, 0x1 }
}

// win1.41 005fd8d0 mac 10531620 LandscapeVortexIn::ShouldPhysicsRaiseObjectUntilNotIntersectingThis(Object *)
bool LandscapeVortexIn::ShouldPhysicsRaiseObjectUntilNotIntersectingThis(Object* param_1)
{
    return false;
}
