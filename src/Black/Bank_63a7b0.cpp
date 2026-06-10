#include "Game3DObject.h"
#include "Object.h"
#include "ObjectInfo.h"



// win1.41 0063a7b0 mac 103d07b0 Object::DropSfx(void)
uint32_t Object::DropSfx()
{
    return (uint32_t)(0);
}

// win1.41 0063a7c0 mac 103d0770 Object::GetInHandImmersionTexture(void)
IMMERSION_EFFECT_TYPE Object::GetInHandImmersionTexture()
{
    return IMMERSION_EFFECT_TYPE_NONE;
}

// win1.41 0063a7d0 mac 103d06c0 Object::CanBecomeArtifact(void)
bool Object::CanBecomeArtifact()
{
    // IsInScript seems to use a 32 bit register and forces this 8 bit bool
    // function to use the full 32 bit register instead of 8 bits.
    return info->artifactMultiplier > 0.0f && !IsInScript();
}

// win1.41 0063a800 mac 10038850 Object::SetYJustAngle(float)
__declspec(naked) void Object::SetYJustAngle(float angle)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            mov dword ptr [ecx + 0x4c], eax
            ret 4
        }
}

// win1.41 0063a920 mac 103d03c0 Object::BlocksTownClearArea( const(void))
bool32_t Object::BlocksTownClearArea()
{
    return (bool32_t)(1);
}

// win1.41 0063aad0 mac 103d0050 Object::GetRadiusMultiplierForApplyingPotToPos(void)
float Object::GetRadiusMultiplierForApplyingPotToPos()
{
    return 0;
}
