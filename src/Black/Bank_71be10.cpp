#include "Animal.h"
#include "DeadTree.h"
#include "GameThing.h"
#include "HelpSpritesGuidance.h"
#include "Pot.h"
#include "SoundInfo.h"
#include "SoundMap.h"
#include "SoundTag.h"
#include "SpecialVillager.h"
#include "SpecialVillagerInfo.h"
#include "Spell.h"
#include "SpellCreature.h"
#include "SpellDispenser.h"
#include "SpellFlock.h"
#include "SpellFlockFlying.h"
#include "SpellFlockGround.h"
#include "SpellForest.h"
#include "SpellIcon.h"
#include "SpellIconInfo.h"
#include "SpellResource.h"
#include "SpellSeedGraphic.h"
#include "SpellWater.h"
#include "SpellWithObjects.h"
#include "Tree.h"



// win1.41 0071be10 mac 1050fbb0 Animal::GetGuidanceResourceType(void)
uint32_t Animal::GetGuidanceResourceType()
{
    return (uint32_t)0x00000001;
}

// win1.41 0071be20 mac 1050fb70 Tree::GetGuidanceResourceType(void)
uint32_t Tree::GetGuidanceResourceType()
{
    return (uint32_t)0x00000002;
}

// win1.41 0071be30 mac 1050fb30 DeadTree::GetGuidanceResourceType(void)
uint32_t DeadTree::GetGuidanceResourceType()
{
    return (uint32_t)0x00000002;
}

// win1.41 0071d660 mac 10513590 GSoundInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GSoundInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000001;
    return (GBaseInfo*)0x00d9a8f8;
}

// win1.41 0071d6b0 mac 105135d0 GSoundInfo::_dt(void)
GSoundInfo::~GSoundInfo()
{
}

// win1.41 0071e3c0 mac 10514730 SoundTag::_dt(void)
SoundTag::~SoundTag()
{
}

// win1.41 0071ee80 mac 101463b0 GSpecialVillagerInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GSpecialVillagerInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000030;
    return (GBaseInfo*)0x00d9b168;
}

// win1.41 0071f490 mac 10147040 SpecialVillager::GetVillagerName(void)
const char* SpecialVillager::GetVillagerName()
{
    return (const char*)(*(uint32_t*)((char*)this + 0x130) * 0x60 + *(uint32_t*)0xd9b154 + 0x10);
}

// win1.41 0071faf0 mac 10514e40 Spell::GetSaveType(void)
uint32_t Spell::GetSaveType()
{
    return (uint32_t)0x00000009;
}

// win1.41 00721370 mac 1051a4f0 Spell::ProcessSpellSeed(void)
// Each tick: if the spell's seed object still exists and is available, run its per-frame update and
// return that result; otherwise drop the dead seed (clear the pointer) and report 1 (handled).
bool32_t Spell::ProcessSpellSeed()
{
    if (field_0xac != 0 && field_0xac->IsAvailable()) {
        return field_0xac->Func728F70();
    }
    field_0xac = 0;
    return 1;
}

// win1.41 0071fb00 mac 10514e70 Spell::GetDebugText(void)
char* Spell::GetDebugText()
{
    return (char*)0x00c22574;
}

// win1.41 0071fb10 mac 1030e5c0 Spell::_dt(void)
Spell::~Spell()
{
}

// win1.41 00720130 mac 105190d0 Spell::GetParticleType(void)
extern "C" void jmp_addr_0x007201d0(void);
__declspec(naked) void Spell::GetParticleType()
{
    __asm {
            call jmp_addr_0x007201d0
            mov eax, dword ptr [eax + 0x20]
            ret
        }
}

// win1.41 007202b0 mac 10518bd0 Spell::GetImpressiveType(void)
extern "C" void jmp_addr_0x007201d0(void);
__declspec(naked) IMPRESSIVE_TYPE Spell::GetImpressiveType()
{
    __asm {
            call jmp_addr_0x007201d0
            mov eax, dword ptr [eax + 0x24]
            ret
        }
}

// win1.41 007203e0 mac 105188d0 Spell::DebugDraw(void)
void Spell::DebugDraw()
{
}

// win1.41 007212f0 mac 10516c10 SpellWithObjects::ProcessSpellSeed(void)
bool32_t SpellWithObjects::ProcessSpellSeed()
{
    return Spell::ProcessSpellSeed();
}

// win1.41 00721340 mac 10516b00 Spell::GetMovementDirection(LHPoint *)
__declspec(naked) void Spell::GetMovementDirection(LHPoint* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            add ecx, 0x2c
            mov edx, dword ptr [ecx]
            mov dword ptr [eax], edx
            mov edx, dword ptr [ecx + 0x04]
            mov dword ptr [eax + 0x04], edx
            mov ecx, dword ptr [ecx + 0x08]
            mov dword ptr [eax + 0x08], ecx
            ret 4
        }
}

// win1.41 00721360 mac 10516aa0 Spell::DrawSpellSeed(void)
extern "C" void jmp_addr_0x00729020(void);
__declspec(naked) void Spell::DrawSpellSeed()
{
    __asm {
            mov ecx, dword ptr [ecx + 0x000000ac]
            test ecx, ecx
            je L_0072136f
            jmp jmp_addr_0x00729020
            L_0072136f:
            ret
        }
}

// win1.41 007216d0 mac 105162d0 Spell::GetUpdateOfBoredomValue(Reaction *, GameThingWithPos *)
float Spell::GetUpdateOfBoredomValue(Reaction* param_1, GameThingWithPos* param_2)
{
    return (float)GameThingWithPos::GetUpdateOfBoredomValue((Reaction*)param_1, (GameThingWithPos*)param_2);
}

// win1.41 00722220 mac 10519f70 SpellCreature::GetSaveType(void)
uint32_t SpellCreature::GetSaveType()
{
    return (uint32_t)0x00000013;
}

// win1.41 00722230 mac 10519fb0 SpellCreature::GetDebugText(void)
char* SpellCreature::GetDebugText()
{
    return (char*)0x00c225ac;
}

// win1.41 00722240 mac 10519e90 SpellCreature::_dt(void)
SpellCreature::~SpellCreature()
{
}

// win1.41 007222c0 mac 1051a7a0 SpellCreature::GetCreatureCastOn(void)
uint32_t SpellCreature::GetCreatureCastOn()
{
    return *(uint32_t*)((char*)this + 0x000000ec);
}

// win1.41 007224f0 mac 1051a290 SpellCreature::CloseDown(void)
extern "C" void jmp_addr_0x00720160(void);
__declspec(naked) void SpellCreature::CloseDown()
{
    __asm {
            jmp jmp_addr_0x00720160
        }
}

// win1.41 007226c0 mac 1051a970 SpellDispenser::IsActive( const(void))
bool32_t SpellDispenser::IsActive() const
{
    return *(bool32_t*)((char*)this + 0x000000d0);
}

// win1.41 007226d0 mac 1051a9b0 SpellDispenser::IsSpellDispenser(void)
bool32_t SpellDispenser::IsSpellDispenser()
{
    return (bool32_t)0x00000001;
}

// win1.41 007226f0 mac 1051aa40 SpellDispenser::GetSaveType(void)
uint32_t SpellDispenser::GetSaveType()
{
    return (uint32_t)0x0000010b;
}

// win1.41 00722700 mac 1051a8e0 SpellDispenser::_dt(void)
SpellDispenser::~SpellDispenser()
{
}

// win1.41 00722fa0 mac 1051ac90 SpellDispenser::GetDebugText(void)
char* SpellDispenser::GetDebugText()
{
    return (char*)(*(char**)((char*)this + 0x28) + 0x18);
}

// win1.41 00722fb0 mac 1051ac40 SpellDispenser::GetScriptObjectType(void)
uint32_t SpellDispenser::GetScriptObjectType()
{
    return (uint32_t)0x00000024;
}

// win1.41 00723270 mac 1051e760 SpellFlock::CloseDown(void)
void SpellFlock::CloseDown()
{
    this->SpellWithObjects::CloseDown();
}

// win1.41 00724290 mac 1051ccf0 SpellFlockGround::GetParticleType(void)
void SpellFlockGround::GetParticleType()
{
    __asm { mov eax, 0x7e }
}

// win1.41 00725f40 mac 10525c70 GSpellIconInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GSpellIconInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x2; return (GBaseInfo*)0xd9d3e8;
}

// win1.41 00725fb0 mac 10525b60 GSpellIconInfo::_dt(void)
GSpellIconInfo::~GSpellIconInfo()
{
}

// win1.41 007260e0 mac 10525630 SpellIcon::InteractsWithPhysicsObjects(void)
bool32_t SpellIcon::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00720f40 mac 10516a40 Spell::SpellEvent(const SpellEventInfo &)
// Spell events of type 1 or 11 are ignored; any other event is dispatched to the per-spell handler.
bool32_t Spell::SpellEvent(const SpellEventInfo& param_1)
{
    switch (*(int*)&param_1) {
    case 1:
    case 11:
        return 1;
    }
    return Func720C30(param_1);
}
