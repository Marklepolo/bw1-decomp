#include "MagicShield.h"
#include "MapShield.h"
#include "MapShieldInfo.h"
#include "OneOffSpellSeed.h"
#include "PhysicalShield.h"
#include "SpellHeal.h"
#include "SpellSeed.h"
#include "SpellSeedInfo.h"
#include "SpellShield.h"
#include "SpellStormAndTornado.h"
#include "SpellSystemInfo.h"
#include "SpookyVoiceInfo.h"
#include "SpookyVoices.h"



// win1.41 0072a2d0 mac 10527cc0 SpellSeed::GetInHandImmersionTexture(void)
extern "C" void jmp_addr_0x007290f0(void);
__declspec(naked) IMMERSION_EFFECT_TYPE SpellSeed::GetInHandImmersionTexture()
{
    __asm {
            call jmp_addr_0x007290f0
            mov eax, dword ptr [eax + 0x10]
            dec eax
            neg eax
            sbb eax, eax
            and eax, 0xfffffff2
            add eax, 0x0d
            ret
        }
}

// win1.41 0072a520 mac 10527690 OneOffSpellSeed::IsEffectReceiver(EffectValues *)
bool32_t OneOffSpellSeed::IsEffectReceiver(EffectValues* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0072a630 mac 10527330 OneOffSpellSeed::InterfaceValidToTap(GInterfaceStatus *)
uint32_t OneOffSpellSeed::InterfaceValidToTap(GInterfaceStatus* param_1)
{
    return (uint32_t)(1);
}

// win1.41 0072a910 mac 10526db0 OneOffSpellSeed::GetMesh( const(void))
int OneOffSpellSeed::GetMesh() const
{
    return (int)(0);
}

// win1.41 0072a920 mac 10526d60 OneOffSpellSeed::GetPhysicsConstantsType(void)
uint32_t OneOffSpellSeed::GetPhysicsConstantsType()
{
    return (uint32_t)(9);
}

// win1.41 0072ab00 mac 105269e0 OneOffSpellSeed::IsOneOffSpellAggressive(Creature *)
extern "C" void jmp_addr_0x0072a5f0(void);
extern "C" void jmp_addr_0x0072afe0(void);
__declspec(naked) bool32_t OneOffSpellSeed::IsOneOffSpellAggressive(Creature* param_1)
{
    __asm {
            push -0x1
            call jmp_addr_0x0072a5f0
            mov ecx, eax
            call jmp_addr_0x0072afe0
            mov eax, dword ptr [eax + 0x48]
            ret 4
        }
}

// win1.41 0072ab20 mac 10526950 OneOffSpellSeed::IsOneOffSpellCompassionate(Creature *)
extern "C" void jmp_addr_0x0072a5f0(void);
extern "C" void jmp_addr_0x0072afe0(void);
__declspec(naked) bool32_t OneOffSpellSeed::IsOneOffSpellCompassionate(Creature* param_1)
{
    __asm {
            push -0x1
            call jmp_addr_0x0072a5f0
            mov ecx, eax
            call jmp_addr_0x0072afe0
            mov eax, dword ptr [eax + 0x4c]
            ret 4
        }
}

// win1.41 0072ab40 mac 105268c0 OneOffSpellSeed::IsOneOffSpellPlayful(Creature *)
extern "C" void jmp_addr_0x0072a5f0(void);
extern "C" void jmp_addr_0x0072afe0(void);
__declspec(naked) bool32_t OneOffSpellSeed::IsOneOffSpellPlayful(Creature* param_1)
{
    __asm {
            push -0x1
            call jmp_addr_0x0072a5f0
            mov ecx, eax
            call jmp_addr_0x0072afe0
            mov eax, dword ptr [eax + 0x44]
            ret 4
        }
}

// win1.41 0072ab60 mac 10526820 OneOffSpellSeed::IsOneOffSpellToRestoreHealth(Creature *)
extern "C" void jmp_addr_0x0072a5f0(void);
extern "C" void jmp_addr_0x0072afe0(void);
__declspec(naked) bool32_t OneOffSpellSeed::IsOneOffSpellToRestoreHealth(Creature* param_1)
{
    __asm {
            push -0x1
            call jmp_addr_0x0072a5f0
            mov ecx, eax
            call jmp_addr_0x0072afe0
            mov eax, dword ptr [eax + 0x50]
            ret 4
        }
}

// win1.41 0072ac80 mac 105265f0 OneOffSpellSeed::GetOverwriteTapToolTip(void)
uint32_t OneOffSpellSeed::GetOverwriteTapToolTip()
{
    return (uint32_t)(0xef7);
}

// win1.41 0072ae00 mac 1052de00 GSpellSystemInfo::_dt(void)
GSpellSystemInfo::~GSpellSystemInfo()
{
}

// win1.41 0072ae70 mac 1052df40 GSpellSeedInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GSpellSeedInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x1e; return (GBaseInfo*)0xd9d678;
}

// win1.41 0072aee0 mac 1052d120 GSpellSeedInfo::_dt(void)
GSpellSeedInfo::~GSpellSeedInfo()
{
}

// win1.41 0072b430 mac 10534300 SpellShield::IsSpellShield(void)
bool32_t SpellShield::IsSpellShield()
{
    return (bool32_t)(this);
}

// win1.41 0072b450 mac 105321c0 SpellShield::GetRadius(void)
float SpellShield::GetRadius()
{
    return this->Get2DRadius();
}

// win1.41 0072b470 mac 10534380 SpellShield::GetDebugText(void)
char* SpellShield::GetDebugText()
{
    return (char*)(0xc22794);
}

// win1.41 0072b480 mac 10534250 SpellShield::_dt(void)
SpellShield::~SpellShield()
{
}

// win1.41 0072b840 mac 10532f10 SpellShield::CloseDown(void)
void SpellShield::CloseDown()
{
    SpellWithObjects::CloseDown();
}

// win1.41 0072bdf0 mac 10531f60 GMapShieldInfo::_dt(void)
GMapShieldInfo::~GMapShieldInfo()
{
}

// win1.41 0072c000 mac 10533fc0 MapShield::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t MapShield::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0072c010 mac 10534010 MapShield::HandShouldFeelWithMeshIntersect(void)
bool32_t MapShield::HandShouldFeelWithMeshIntersect()
{
    return (bool32_t)(0);
}

// win1.41 0072c030 mac 105341d0 MapShield::GetSaveType(void)
uint32_t MapShield::GetSaveType()
{
    return (uint32_t)(0);
}

// win1.41 0072c040 mac 10534210 MapShield::GetDebugText(void)
char* MapShield::GetDebugText()
{
    return (char*)(0xc22800);
}

// win1.41 0072c050 mac 105304c0 MapShield::_dt(void)
MapShield::~MapShield()
{
}

// win1.41 0072c1b0 mac 10531700 MapShield::GetMesh( const(void))
int MapShield::GetMesh() const
{
    return (int)(0x22a);
}

// win1.41 0072c1c0 mac 105316c0 MapShield::GetTopPos(void)
float MapShield::GetTopPos()
{
    return 0.0f;
}

// win1.41 0072c1d0 mac 10531680 MapShield::CanBecomeAPhysicsObject(void)
bool32_t MapShield::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 0072c1e0 mac 10531620 MapShield::ShouldPhysicsRaiseObjectUntilNotIntersectingThis(Object *)
bool MapShield::ShouldPhysicsRaiseObjectUntilNotIntersectingThis(Object* param_1)
{
    return false;
}

// win1.41 0072c210 mac 10534150 MagicShield::GetSaveType(void)
uint32_t MagicShield::GetSaveType()
{
    return (uint32_t)(0x18);
}

// win1.41 0072c220 mac 10534190 MagicShield::GetDebugText(void)
char* MagicShield::GetDebugText()
{
    return (char*)(0xc2282c);
}

// win1.41 0072c230 mac 105340b0 MagicShield::_dt(void)
MagicShield::~MagicShield()
{
}

// win1.41 0072c2e0 mac 105313e0 MagicShield::ProcessShield(void)
void MagicShield::ProcessShield()
{
}

// win1.41 0072c2f0 mac 105313a0 MagicShield::DrawShield(void)
void MagicShield::DrawShield()
{
}

// win1.41 0072c300 mac 10531370 MagicShield::Draw(void)
void MagicShield::Draw()
{
}

// win1.41 0072c310 mac 10531320 MagicShield::IsEffectReceiver(EffectValues *)
bool32_t MagicShield::IsEffectReceiver(EffectValues* param_1)
{
    return (bool32_t)(0);
}

// win1.41 0072c330 mac 10531270 MagicShield::InteractsWithPhysicsObjects(void)
bool32_t MagicShield::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 0072caf0 mac 10533ee0 PhysicalShield::GetAlwaysRemainsInPhysicsInternalSystem(void)
bool32_t PhysicalShield::GetAlwaysRemainsInPhysicsInternalSystem()
{
    __asm { mov al, 0x01 }
}

// win1.41 0072cb00 mac 10533f40 PhysicalShield::GetSaveType(void)
uint32_t PhysicalShield::GetSaveType()
{
    return (uint32_t)(0x17);
}

// win1.41 0072cb10 mac 10533f80 PhysicalShield::GetDebugText(void)
char* PhysicalShield::GetDebugText()
{
    return (char*)(0xc22860);
}

// win1.41 0072cb20 mac 10533e40 PhysicalShield::_dt(void)
PhysicalShield::~PhysicalShield()
{
}

// win1.41 0072ce80 mac 1052fda0 PhysicalShield::DestroyedByEffect(GPlayer *, float)
bool32_t PhysicalShield::DestroyedByEffect(GPlayer* param_1, float param_2)
{
    return (bool32_t)Object::DestroyedByEffect(param_1, param_2);
}

// win1.41 0072cea0 mac 1052fd70 PhysicalShield::Draw(void)
void PhysicalShield::Draw()
{
}

// win1.41 0072d170 mac 1052f8a0 PhysicalShield::SetDying(void)
bool32_t PhysicalShield::SetDying()
{
    *(uint8_t*)((char*)this + 0xf8) = 1;
        *(uint32_t*)((char*)this + 0x60) = 0;
        return (bool32_t)1;
}

// win1.41 0072d600 mac 1052f2c0 PhysicalShield::InteractsWithPhysicsObjects(void)
bool32_t PhysicalShield::InteractsWithPhysicsObjects()
{
    __asm { mov al, 0x01 }
}

// win1.41 0072d7e0 mac 1052ef50 PhysicalShield::GetPhysicsConstantsType(void)
uint32_t PhysicalShield::GetPhysicsConstantsType()
{
    return (uint32_t)(0xa);
}

// win1.41 0072d960 mac 1052e140 SpellStormAndTornado::GetRadius(void)
float SpellStormAndTornado::GetRadius()
{
    return this->Get2DRadius();
}

// win1.41 0072d980 mac 1052e1f0 SpellStormAndTornado::GetDebugText(void)
char* SpellStormAndTornado::GetDebugText()
{
    return (char*)(0xc22870);
}

// win1.41 0072d990 mac 1052dff0 SpellStormAndTornado::_dt(void)
SpellStormAndTornado::~SpellStormAndTornado()
{
}

// win1.41 0072e220 mac 10149010 GSpookyVoiceInfo::_dt(void)
GSpookyVoiceInfo::~GSpookyVoiceInfo()
{
}

// win1.41 0072e250 mac 10148e30 GSpookyVoices::_dt(void)
GSpookyVoices::~GSpookyVoices()
{
}
