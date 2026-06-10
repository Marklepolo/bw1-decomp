#include "Abode.h"
#include "Animal.h"
#include "Citadel.h"
#include "Creature.h"
#include "CreatureActionsKnownAbout.h"
#include "CreatureMimicInfo.h"
#include "CreatureObjectsInspected.h"
#include "Field.h"
#include "GameThingWithPos.h"
#include "MagicFood.h"
#include "MobileObject.h"
#include "MobileStatic.h"
#include "MultiMapFixed.h"
#include "Object.h"
#include "OneOffSpellSeed.h"
#include "Scaffold.h"
#include "StoragePit.h"
#include "Totem.h"
#include "TotemStatue.h"
#include "Town.h"
#include "Tree.h"
#include "Villager.h"
#include "WorshipSite.h"



// win1.41 004e2230 mac 10266a40 CreatureActionsKnownAbout::_dt(void)
CreatureActionsKnownAbout::~CreatureActionsKnownAbout()
{
}

// win1.41 004e3520 mac 102466c0 CreatureObjectsInspected::_dt(void)
CreatureObjectsInspected::~CreatureObjectsInspected()
{
}

// win1.41 004e3b40 mac 105e70f0 Object::CanBeInspectedByCreature(Creature *)
__declspec(naked) bool32_t Object::CanBeInspectedByCreature(Creature* creature)
{
    __asm {
            mov eax, dword ptr [ecx + 0x28]
            mov edx, dword ptr [eax + 0x000000cc]
            xor ecx, ecx
            test edx, edx
            setne cl
            mov eax, ecx
            ret 4
        }
}

// win1.41 004e48f0 mac 105e4890 OneOffSpellSeed::CanBeEatenByCreature(Creature *)
bool32_t OneOffSpellSeed::CanBeEatenByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 004e4b40 mac 105e4090 Villager::CanHaveMagicFoodCastOnMe(Creature *)
bool32_t Villager::CanHaveMagicFoodCastOnMe(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 004e4b70 mac 105e3f50 StoragePit::CanHaveMagicWoodCastOnMe(Creature *)
bool32_t StoragePit::CanHaveMagicWoodCastOnMe(Creature* param_1)
{
    return (bool32_t)(1);
}

// win1.41 004e4ce0 mac 105e3ad0 MobileObject::IsMushroom(Creature *)
__declspec(naked) bool32_t MobileObject::IsMushroom(Creature* param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x28]
            mov eax, dword ptr [eax + 0x00000104]
            cmp eax, 0x13
            je L_004e4cf8
            cmp eax, 0x12
            je L_004e4cf8
            xor eax, eax
            ret 4
            L_004e4cf8:
            mov eax, 0x00000001
            ret 4
        }
}

// win1.41 004e9cf0 mac 1026ea60 CreatureMimicInfo::_dt(void)
CreatureMimicInfo::~CreatureMimicInfo()
{
}

// ==== AUTOHARVEST ====
// AUTOHARVEST ?CanBePickedUpByCreature@Creature@@UAEIPAV1@@Z
bool32_t Creature::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)0;
}

