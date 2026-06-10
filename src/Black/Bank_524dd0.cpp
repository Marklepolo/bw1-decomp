#include "EditorHug.h"
#include "EditorIconBase.h"
#include "EffectInfo.h"
#include "EffectValues.h"
#include "Feature.h"
#include "FeatureInfo.h"
#include "Field.h"
#include "FieldInfo.h"
#include "FieldTypeInfo.h"
#include "FireFly.h"
#include "Flowers.h"
#include "FlowersInfo.h"
#include "MagicEffectInfo.h"
#include "PlannedFeature.h"
#include "WorshipSiteUpgrade.h"



// win1.41 00524dd0 mac 100cc6a0 GEffectInfo::_dt(void)
GEffectInfo::~GEffectInfo()
{
}

// win1.41 00524e30 mac 100ccbe0 GMagicEffectInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GMagicEffectInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x2a; return (GBaseInfo*)0xcc6630;
}

// win1.41 00524ea0 mac 100cca30 GMagicEffectInfo::_dt(void)
GMagicEffectInfo::~GMagicEffectInfo()
{
}

// win1.41 00524f40 mac 10412ff0 EffectValues::_dt(void)
EffectValues::~EffectValues()
{
}

// win1.41 00527320 mac 100a6900 GFeatureInfo::_dt(void)
GFeatureInfo::~GFeatureInfo()
{
}

// win1.41 00527480 mac 100d16a0 PlannedFeature::GetSaveType(void)
uint32_t PlannedFeature::GetSaveType()
{
    return (uint32_t)0x00000073;
}

// win1.41 00527490 mac 100d16e0 PlannedFeature::GetDebugText(void)
char* PlannedFeature::GetDebugText()
{
    return (char*)0x00be9cd0;
}

// win1.41 005276c0 mac 10008370 Feature::GetScriptObjectType(void)
uint32_t Feature::GetScriptObjectType()
{
    return (uint32_t)0x00000003;
}

// win1.41 005276d0 mac 100d0c30 Feature::IsMushroom(Creature *)
__declspec(naked) bool32_t Feature::IsMushroom(Creature* param_1)
{
    __asm {
            mov ecx, dword ptr [ecx + 0x28]
            sub ecx, 0x00cc99a0
            mov eax, 0xe070381d
            imul ecx
            mov eax, edx
            add eax, ecx
            sar eax, 8
            mov ecx, eax
            shr ecx, 0x1f
            add eax, ecx
            sub eax, 0x36
            neg eax
            sbb eax, eax
            inc eax
            ret 4
        }
}

// win1.41 00527910 mac 100d06a0 GFlowersInfo::_dt(void)
GFlowersInfo::~GFlowersInfo()
{
}

// win1.41 00527990 mac 100d00f0 Flowers::GetSaveType(void)
uint32_t Flowers::GetSaveType()
{
    return (uint32_t)0x0000010a;
}

// win1.41 005279a0 mac 100d0130 Flowers::GetDebugText(void)
char* Flowers::GetDebugText()
{
    return (char*)0x00be9d18;
}

// win1.41 00527cc0 mac 100d5dc0 GFieldInfo::_dt(void)
GFieldInfo::~GFieldInfo()
{
}

// win1.41 00527d30 mac 100d18c0 GFieldTypeInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GFieldTypeInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x2; return (GBaseInfo*)0xccf070;
}

// win1.41 00527da0 mac 100d1a40 GFieldTypeInfo::_dt(void)
GFieldTypeInfo::~GFieldTypeInfo()
{
}

// win1.41 00528900 mac 100d4c80 Field::IsEffectReceiver(EffectValues *)
// A field is NOT an effect receiver (returns 0) only if it is un-tuggable AND the incoming effect's
// values[2] (the relevant effect-type magnitude) is positive; otherwise it receives (returns 1).
bool32_t Field::IsEffectReceiver(EffectValues* param_1)
{
    if (ValidForPlaceInHand(0) == 0 && param_1 != 0 && *(float*)((char*)param_1 + 8) > 0.0f)
        return 0;
    return 1;
}

// win1.41 00527f20 mac 100d5fa0 Field::GetCreatureBeliefType(void)
uint32_t Field::GetCreatureBeliefType()
{
    return (uint32_t)0x0000000b;
}

// win1.41 00527f30 mac inlined Field::IsField(Creature *)
bool32_t Field::IsField(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00527f40 mac inlined Field::IsField(void)
bool32_t Field::IsField()
{
    return (bool32_t)0x00000001;
}

// win1.41 00527f60 mac 100d60d0 Field::CanBePoodOn(Creature *)
bool32_t Field::CanBePoodOn(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527f70 mac 100d6110 Field::CanBePickedUpByCreature(Creature *)
bool32_t Field::CanBePickedUpByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527f80 mac 100d6160 Field::CanBeStompedOnByCreature(Creature *)
bool32_t Field::CanBeStompedOnByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527f90 mac 100d61b0 Field::CanBeGivenToVillager(Creature *)
bool32_t Field::CanBeGivenToVillager(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527fa0 mac 100d6200 Field::CanBePutInAStoragePit(Creature *)
bool32_t Field::CanBePutInAStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527fb0 mac 100d6250 Field::CanBeDestroyedByStoning(Creature *)
bool32_t Field::CanBeDestroyedByStoning(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527fc0 mac 100d62a0 Field::CanBeExaminedByCreature(Creature *)
bool32_t Field::CanBeExaminedByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527fd0 mac 100d62f0 Field::CanBeEatenByCreature(Creature *)
bool32_t Field::CanBeEatenByCreature(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00527fe0 mac 100d6340 Field::CanBeSleptNextToByCreature(Creature *)
bool32_t Field::CanBeSleptNextToByCreature(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00527ff0 mac 100d6390 Field::IsBeingBuilt(Creature *)
bool32_t Field::IsBeingBuilt(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00528000 mac 100d63d0 Field::NeedsRepair(Creature *)
bool32_t Field::NeedsRepair(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00528010 mac 100d2c60 Field::GetResourceType(void)
RESOURCE_TYPE Field::GetResourceType()
{
    return (RESOURCE_TYPE)0;
}

// win1.41 00528020 mac 100d6410 Field::InteractsWithPhysicsObjects(void)
bool32_t Field::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00528030 mac 100d6450 Field::CanBecomeAPhysicsObject(void)
bool32_t Field::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 00528040 mac 100d6490 Field::IsTuggable(void)
bool32_t Field::IsTuggable()
{
    return (bool32_t)(0);
}

// win1.41 00528050 mac 100d64c0 Field::IsLockedInInteract(void)
bool32_t Field::IsLockedInInteract()
{
    return (bool32_t)0x00000001;
}

// win1.41 00528070 mac 100d6540 Field::GetSaveType(void)
uint32_t Field::GetSaveType()
{
    return (uint32_t)0x00000032;
}

// win1.41 00528080 mac 100d6570 Field::GetDebugText(void)
char* Field::GetDebugText()
{
    return (char*)0x00be9d98;
}

// win1.41 00528090 mac 100d5ed0 Field::_dt(void)
Field::~Field()
{
}

// win1.41 00528960 mac 100560a0 Field::GetTown(void)
Town* Field::GetTown()
{
    return *(Town**)((char*)this + 0x00000118);
}

// win1.41 00528e80 mac 100d4150 Field::Get2DRadius(void)
float Field::Get2DRadius()
{
    return 5.0f;
}

// win1.41 00529330 mac inlined Field::GetArrivePos(MapCoords *)
__declspec(naked) MapCoords* Field::GetArrivePos(MapCoords* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            add ecx, 0x14
            push esi
            mov esi, dword ptr [ecx]
            mov edx, eax
            mov dword ptr [edx], esi
            mov esi, dword ptr [ecx + 0x04]
            mov dword ptr [edx + 0x04], esi
            mov ecx, dword ptr [ecx + 0x08]
            mov dword ptr [edx + 0x08], ecx
            pop esi
            ret 4
        }
}

// win1.41 00529500 mac 10000730 Field::GetPercentFull(void)
__declspec(naked) float Field::GetPercentFull()
{
    __asm {
            _emit 0x51
            _emit 0x33
            _emit 0xc0
            _emit 0x8a
            _emit 0x81
            _emit 0xcc
            _emit 0x00
            _emit 0x00
            _emit 0x00
            _emit 0x8b
            _emit 0x89
            _emit 0x20
            _emit 0x01
            _emit 0x00
            _emit 0x00
            _emit 0x89
            _emit 0x44
            _emit 0x24
            _emit 0x00
            _emit 0xdb
            _emit 0x44
            _emit 0x24
            _emit 0x00
            _emit 0xd8
            _emit 0xb1
            _emit 0x28
            _emit 0x01
            _emit 0x00
            _emit 0x00
            _emit 0x59
            _emit 0xc3
        }
}

// win1.41 00529af0 mac 100d2830 Field::NetworkFriendlyEndLockedSelect(GInterfaceStatus *)
extern "C" void jmp_addr_0x0068fa50(void);
__declspec(naked) bool32_t Field::NetworkFriendlyEndLockedSelect(GInterfaceStatus* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            push eax
            call jmp_addr_0x0068fa50
            add esp, 0x04
            mov eax, 0x00000001
            ret 4
        }
}

// win1.41 00529ff0 mac inlined Field::CanBeDestroyedBySpell_1(Spell *)
bool32_t Field::CanBeDestroyedBySpell(Spell* param_1)
{
    return 0;
}

// win1.41 0052a000 mac 100d1d20 Field::GetOverwriteInteractableToolTip(void)
uint32_t Field::GetOverwriteInteractableToolTip()
{
    return (uint32_t)0x00000e73;
}

// win1.41 0052a1a0 mac 100da240 FireFly::InteractsWithPhysicsObjects(void)
bool32_t FireFly::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 0052a1b0 mac 100da1f0 FireFly::ReactToPhysicsImpact(PhysicsObject *, bool)
void FireFly::ReactToPhysicsImpact(PhysicsObject* param_1, bool param_2)
{
}

// win1.41 0052a1c0 mac 100da1b0 FireFly::CanBecomeAPhysicsObject(void)
bool32_t FireFly::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 0052a2f0 mac 100d6690 FireFly::GetSaveType(void)
uint32_t FireFly::GetSaveType()
{
    return (uint32_t)0x0000002a;
}

// win1.41 0052a300 mac 100d66d0 FireFly::GetDebugText(void)
char* FireFly::GetDebugText()
{
    return (char*)0x00be9dd8;
}

// win1.41 0052a310 mac 100d9be0 FireFly::_dt(void)
FireFly::~FireFly()
{
}
