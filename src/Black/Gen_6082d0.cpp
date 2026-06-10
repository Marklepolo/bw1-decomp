#include "FieldCrop.h"

bool32_t FieldCrop::CanBecomeAPhysicsObject()
{
    return (bool32_t)0x1;
}

uint32_t FieldCrop::GetPhysicsConstantsType()
{
    return (uint32_t)0x6;
}
