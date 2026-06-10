#include "Creature.h"



// win1.41 00477ee0 mac 101da160 Creature::GetFacingPitch(void)
float Creature::GetFacingPitch()
{
    return *(float*)((char*)*(void**)((char*)*(void**)((char*)this + 0x160) + 0x58) + 0x486c);
}

// win1.41 00477ef0 mac 101da120 Creature::GetProjectileSpeed(void)
float Creature::GetProjectileSpeed()
{
    return 0.0f;
}

// win1.41 00477f30 mac 101da020 Creature::ResetStateAfterReacting(void)
void Creature::ResetStateAfterReacting()
{
    (*(void (__fastcall **)(Creature*))((char*)*(void**)this + 0x998))(this);
}

// win1.41 00477f50 mac 101d9f50 Creature::GetHeight(void)
float Creature::GetHeight()
{
    char* p1 = *(char**)((char*)this + 0x160);
        char* p2 = *(char**)(p1 + 0x58);
        return *(float*)(p2 + 0x90) * 15.0f;
}

// win1.41 004792c0 mac 101d8510 Creature::GetRadius(void)
float Creature::GetRadius()
{
    return *(float*)(*(char**)(*(char**)((char*)this + 0x160) + 0x58) + 0x5228);
}

// win1.41 004792d0 mac 101d84a0 Creature::GetCitadel(void)
__declspec(naked) Citadel* Creature::GetCitadel()
{
    __asm {
            mov eax, dword ptr [ecx + 0x00001070]
            test eax, eax
            je L_004792e1
            mov eax, dword ptr [eax + 0x00000a48]
            ret
            L_004792e1:
            xor eax, eax
            ret
        }
}

// win1.41 004794a0 mac 101d7fc0 Creature::IsReadyForNewScriptAction(void)
__declspec(naked) bool32_t Creature::IsReadyForNewScriptAction()
{
    __asm {
            mov eax, dword ptr [ecx + 0x00000164]
            mov ecx, dword ptr [eax + 0x00000fb4]
            lea ecx, dword ptr [ecx + ecx * 0x2]
            shl ecx, 5
            push esi
            mov esi, dword ptr [ecx + eax * 0x1 + 0x00000fd8]
            xor edx, edx
            cmp esi, 0x40
            sete dl
            pop esi
            mov eax, edx
            ret
        }
}

// win1.41 00479b80 mac 101d6f90 Creature::GetPhysicsConstantsType(void)
uint32_t Creature::GetPhysicsConstantsType()
{
    return (uint32_t)(0);
}

// win1.41 00479d10 mac 101d6d70 Creature::CanBecomeAPhysicsObject(void)
bool32_t Creature::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 0047a320 mac 101d63d0 Creature::InterfaceGiveObject(GInterfaceStatus *, Object *)
uint32_t Creature::InterfaceGiveObject(GInterfaceStatus* param_1, Object* param_2)
{
    return (uint32_t)(0x16);
}

// win1.41 0047b150 mac 101d4b00 Creature::GetImpressiveIntensity(IMPRESSIVE_TYPE)
extern "C" void jmp_addr_0x004ef4f0(void);
__declspec(naked) float Creature::GetImpressiveIntensity(IMPRESSIVE_TYPE param_1)
{
    __asm {
            mov ecx, dword ptr [ecx + 0x00000160]
            call jmp_addr_0x004ef4f0
            ret 4
        }
}

// win1.41 0047b190 mac 101d4a30 Creature::GetScale(void)
extern "C" void jmp_addr_0x004ef4f0(void);
__declspec(naked) float Creature::GetScale()
{
    __asm {
            mov ecx, dword ptr [ecx + 0x00000160]
            jmp jmp_addr_0x004ef4f0
        }
}

// win1.41 0047b1a0 mac 101d49f0 Creature::GetAge(void)
uint32_t Creature::GetAge()
{
    return *(uint32_t*)((char*)*(void**)((char*)this + 0x160) + 0x8);
}

// win1.41 0047b1b0 mac 101d49b0 Creature::SetAge(unsigned long)
__declspec(naked) void Creature::SetAge(uint32_t param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x00000160]
            mov ecx, dword ptr [esp + 0x04]
            mov dword ptr [eax + 0x08], ecx
            ret 4
        }
}

// win1.41 0047c8b0 mac 101d10b0 Creature::GetScriptObjectType(void)
uint32_t Creature::GetScriptObjectType()
{
    return (uint32_t)(0xc);
}

// win1.41 0047d2c0 mac 101cfdf0 Creature::SetControlledByScript(int)
__declspec(naked) void Creature::SetControlledByScript(int param_1)
{
    __asm {
            xor eax, eax
            mov al, byte ptr [esp + 0x04]
            xor edx, edx
            mov dx, word ptr [ecx + 0x24]
            and eax, 0x01
            shl eax, 0xa
            and edx, 0x0000fbff
            or eax, edx
            mov word ptr [ecx + 0x24], ax
            ret 4
        }
}


bool32_t Creature::InteractsWithPhysicsObjects()
{
    __asm { mov al, 0x1 }
}
