#include "Arena.h"
#include "Arrow.h"
#include "ArrowInfo.h"
#include "GameThing.h"
#include "GameThingWithPos.h"
#include "Mobile.h"
#include "MobileObject.h"
#include "MobileObjectInfo.h"
#include "Object.h"



// win1.41 00424780 mac 10027dd0 GArena::GetRadius(void)
float GArena::GetRadius()
{
    return *(float*)((char*)this + 0x30);
}

// win1.41 00424790 mac 100ad3a0 GArena::GetText(void)
const char* GArena::GetText()
{
    return (const char*)(0x9c95fc);
}

// win1.41 004247a0 mac 100ad3e0 GArena::GetSaveType(void)
uint32_t GArena::GetSaveType()
{
    return (uint32_t)(0x41);
}

// win1.41 004247b0 mac 100ad420 GArena::GetDebugText(void)
char* GArena::GetDebugText()
{
    return (char*)(0x9c9604);
}

// win1.41 004247c0 mac 100ad310 GArena::_dt(void)
GArena::~GArena()
{
}

// win1.41 004247f0 mac 103e31e0 GameThingWithPos::SetScale(float)
void GameThingWithPos::SetScale(float scale)
{
}

// win1.41 00425980 mac 100ad540 GArrowInfo::_dt(void)
GArrowInfo::~GArrowInfo()
{
}

// win1.41 00425b00 mac 100adca0 Mobile::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t Mobile::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00425b10 mac 100ad890 MobileObject::GetXAngle(void)
float MobileObject::GetXAngle()
{
    return *(float*)((char*)this + 0x5c);
}

// win1.41 00425b20 mac 100ad8d0 MobileObject::GetZAngle(void)
float MobileObject::GetZAngle()
{
    return *(float*)((char*)this + 0x60);
}

// win1.41 00425b30 mac 100ad910 MobileObject::CanBePickedUp(void)
bool32_t MobileObject::CanBePickedUp()
{
    return ((uint16_t)~*(uint16_t*)((char*)this + 0x24) >> 0xd) & 1;
}

// win1.41 00425b60 mac 100ada10 MobileObject::GetCreatureMimicType(void)
uint32_t MobileObject::GetCreatureMimicType()
{
    return (uint32_t)(8);
}

// win1.41 00425b70 mac 100ada60 MobileObject::CanBeUsedToHoldWater(Creature *)
__declspec(naked) bool32_t MobileObject::CanBeUsedToHoldWater(Creature* param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x28]
            mov edx, dword ptr [eax + 0x00000104]
            xor ecx, ecx
            cmp edx, 0x06
            sete cl
            mov eax, ecx
            ret 4
        }
}

// win1.41 00425b90 mac 100adae0 MobileObject::CanBeStompedOnByCreature(Creature *)
bool32_t MobileObject::CanBeStompedOnByCreature(Creature* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00425ba0 mac 100adb30 MobileObject::CanBeThrownInTheSeaPlayfully(Creature *)
bool32_t MobileObject::CanBeThrownInTheSeaPlayfully(Creature* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00425bb0 mac 100adb90 MobileObject::CanBePlayedWithByCreature(Creature *)
bool32_t MobileObject::CanBePlayedWithByCreature(Creature* param_1)
{
    return (bool32_t)(1);
}

// win1.41 00425bc0 mac 100adbe0 MobileObject::IsMobileObject(void)
bool32_t MobileObject::IsMobileObject()
{
    return (bool32_t)(1);
}

// win1.41 00425bd0 mac 100adc20 MobileObject::GetSaveType(void)
uint32_t MobileObject::GetSaveType()
{
    return (uint32_t)(0x53);
}

// win1.41 00425be0 mac 100adc60 MobileObject::GetDebugText(void)
char* MobileObject::GetDebugText()
{
    return (char*)(0x9c96e8);
}

// win1.41 00425c50 mac 100add90 Object::CanBeCrushed(void)
bool32_t Object::CanBeCrushed()
{
    return (bool32_t)(0);
}

// win1.41 00425c60 mac 100ade90 Object::CanBeFrighteningToCreature(Creature *)
bool32_t Object::CanBeFrighteningToCreature(Creature* creature)
{
    return (bool32_t)(0);
}


uint32_t ArenaSpellIcon::GetSaveType()
{
    return (uint32_t)0x42;
}

char* ArenaSpellIcon::GetDebugText()
{
    return (char*)0x9c9648;
}

void ArenaSpellIcon::Draw()
{
    
}


bool32_t ArenaSpellIcon::IsEffectReceiver(EffectValues* param_1)
{
    return (bool32_t)0;
}
