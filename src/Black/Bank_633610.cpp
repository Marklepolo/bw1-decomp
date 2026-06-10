#include "CreatureDatabase.h"
#include "FireEffect.h"
#include "GameOSFile.h"
#include "GameThingWithPos.h"
#include "MPFEChangedMapMessage.h"
#include "MPFEChangedTeamRequestMessage.h"
#include "MPFEMapErrorMessage.h"
#include "MPFEUserTeamList.h"
#include "MultiplayerDatabase.h"
#include "Network.h"
#include "Object.h"
#include "ObjectInfo.h"
#include "PhysicsObject.h"
#include "StatsDatabase.h"
#include <lionhead/lh3dlib/development/LHMatrix.h>
#include <lionhead/lh3dlib/development/LHPoint.h>
#include <string.h>



// win1.41 00633610 mac 10109f20 MultiplayerDatabase::ReceiveReturnData(void)
bool32_t MultiplayerDatabase::ReceiveReturnData()
{
    return (bool32_t)(0);
}

// win1.41 006336b0 mac 10109d30 CreatureDatabase::CreatureDatabase(void)
CreatureDatabase::CreatureDatabase()
{
}

// win1.41 006338d0 mac 10109a30 StatsDatabase::StatsDatabase(void)
StatsDatabase::StatsDatabase()
{
}

// win1.41 006363c0 mac 101cbbe0 GObjectInfo::_dt(void)
GObjectInfo::~GObjectInfo()
{
}

// win1.41 00636a90 mac 103d8920 Object::IsTuggable(void)
bool32_t Object::IsTuggable()
{
    return (bool32_t)(1);
}

// win1.41 00636aa0 mac 100933f0 Object::ValidToShakeFromHand(void)
bool32_t Object::ValidToShakeFromHand()
{
    return (bool32_t)(1);
}

// win1.41 00637470 mac 103d7730 Object::HasSunk(void)
bool32_t Object::HasSunk()
{
    return (bool32_t)(0);
}

// win1.41 00637690 mac 103d7220 Object::GetCollideSoundType(void)
SOUND_COLLISION_TYPE Object::GetCollideSoundType()
{
    return *(SOUND_COLLISION_TYPE*)((char*)*(void**)((char*)this + 0x28) + 0x48);
}

// win1.41 006377c0 mac 103d6ee0 Object::ReactToPhysicsImpact(PhysicsObject *, bool)
void Object::ReactToPhysicsImpact(PhysicsObject* param_1, bool param_2)
{
}

// win1.41 006377e0 mac 103d6e10 Object::CanBecomeAPhysicsObject(void)
bool32_t Object::CanBecomeAPhysicsObject()
{
    return (bool32_t)(0);
}

// win1.41 00637ce0 mac 103d6270 Object::GetHeatCapacity(void)
float Object::GetHeatCapacity()
{
    return *(float*)(*(char**)((char*)this + 0x28) + 0x000000b0);
}

// win1.41 00637cf0 mac 103d6220 Object::GetActualObjectToEffect(GPlayer *, bool)
void* Object::GetActualObjectToEffect(GPlayer* player, bool param_2)
{
    return (void*)this;
}

// win1.41 006380b0 mac 103d5740 Object::GetProjectileSpeed(void)
float Object::GetProjectileSpeed()
{
    return 0.0f;
}

// win1.41 00638110 mac 103d55b0 Object::GetRadius(void)
float Object::GetRadius()
{
    return this->Get2DRadius();
}

// win1.41 00638150 mac 103d5500 Object::GetHeightForHandAboveInteractObject(void)
float Object::GetHeightForHandAboveInteractObject()
{
    return this->GetHeight();
}

// win1.41 00638550 mac 103d5010 Object::IsBuildingMaterial(void)
bool32_t Object::IsBuildingMaterial()
{
    return *(bool32_t*)(*(char**)((char*)this + 0x28) + 0x000000bc);
}

// win1.41 00638580 mac 103d4f70 Object::GetQueryFirstEnumText(void)
HELP_TEXT Object::GetQueryFirstEnumText()
{
    return *(HELP_TEXT*)((char*)*(void**)((char*)this + 0x28) + 0x50);
}

// win1.41 00638590 mac 103d4f10 Object::GetQueryLastEnumText(void)
HELP_TEXT Object::GetQueryLastEnumText()
{
    return info->helpEndEnum;
}

// win1.41 006385a0 mac 1004c960 Object::GetFOVHelpMessageSet(void)
uint32_t Object::GetFOVHelpMessageSet()
{
    return *(uint32_t*)(*(char**)((char*)this + 0x28) + 0x58);
}

// win1.41 006385b0 mac 103d4d50 Object::GetFOVHelpCondition(void)
uint32_t Object::GetFOVHelpCondition()
{
    return *(uint32_t*)(*(char**)((char*)this + 0x28) + 0x5c);
}

// win1.41 006385c0 mac 103d4cf0 Object::GetHandHelpMessageSet(void)
uint32_t Object::GetHandHelpMessageSet()
{
    return *(uint32_t*)(*(char**)((char*)this + 0x28) + 0x60);
}

// win1.41 006385d0 mac 103d4c90 Object::GetHandHelpCondition(void)
uint32_t Object::GetHandHelpCondition()
{
    return *(uint32_t*)(*(char**)((char*)this + 0x28) + 0x64);
}

// win1.41 00638730 mac 10097740 Object::IsARootedObject(void)
bool32_t Object::IsARootedObject()
{
    return (bool32_t)(0);
}

// win1.41 00638bf0 mac 103d41a0 Object::GetHoldType(void)
HOLD_TYPE Object::GetHoldType()
{
    return HOLD_TYPE_ABOVE;
}

// win1.41 00638c30 mac 103d4110 Object::GetHoldLoweringMultiplier(void)
float Object::GetHoldLoweringMultiplier()
{
    return 0.0f;
}

// win1.41 00638cf0 mac 103d3f30 Object::GetImportance(void)
float Object::GetImportance()
{
    return 0.0f;
}

// win1.41 00639610 mac 103d3310 Object::GetAggressorValueFromDamage(float)
__declspec(naked) float Object::GetAggressorValueFromDamage(float param_1)
{
    __asm {
            mov eax, dword ptr [ecx + 0x28]
            fld dword ptr [esp + 0x04]
            fmul dword ptr [eax + 0x000000ec]
            ret 4
        }
}

// win1.41 00639940 mac 103d2cf0 Object::GetUpdateOfBoredomValue(Reaction *, GameThingWithPos *)
float Object::GetUpdateOfBoredomValue(Reaction* param_1, GameThingWithPos* param_2)
{
    return (float)GameThingWithPos::GetUpdateOfBoredomValue(param_1, param_2);
}

// win1.41 00639a00 mac 103d2b20 Object::IsFireMan(void)
bool32_t Object::IsFireMan()
{
    return (bool32_t)(0);
}

// win1.41 00639a80 mac 103d2950 Object::GetFireGPHXDrawn(bool *, bool *, bool *, bool *)
void Object::GetFireGPHXDrawn(bool* param_1, bool* param_2, bool* param_3, bool* param_4)
{
}

// win1.41 00639a90 mac 103d2900 Object::GetRainCoolingMultiplier(void)
float Object::GetRainCoolingMultiplier()
{
    return 0.009999999776482582f;
}

// win1.41 00639aa0 mac 1001a370 Object::GetDefaultFireCentrePos(MapCoords *)
__declspec(naked) LHPoint* Object::GetDefaultFireCentrePos(LHPoint* pos)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            add ecx, 0x14
            mov edx, dword ptr [ecx]
            mov dword ptr [eax], edx
            mov edx, dword ptr [ecx + 0x04]
            mov dword ptr [eax + 0x04], edx
            mov ecx, dword ptr [ecx + 0x08]
            mov dword ptr [eax + 0x08], ecx
            ret 4
        }
}

// win1.41 00639ac0 mac 103d2490 Object::GetDefaultFireRadius(void)
float Object::GetDefaultFireRadius()
{
    return this->Get2DRadius();
}

// win1.41 00639b10 mac 103d22d0 Object::ProcessInInteract(GInterfaceStatus *)
uint32_t Object::ProcessInInteract(GInterfaceStatus* status)
{
    return (uint32_t)(1);
}

// win1.41 00639b20 mac 103d2290 Object::SetInScript(int)
__declspec(naked) void Object::SetInScript(int param_1)
{
    __asm {
            xor eax, eax
            mov al, byte ptr [esp + 0x04]
            xor edx, edx
            mov dx, word ptr [ecx + 0x24]
            and eax, 0x01
            shl eax, 9
            and edx, 0x0000fdff
            or eax, edx
            mov word ptr [ecx + 0x24], ax
            ret 4
        }
}

// win1.41 00639b50 mac 103d2250 Object::RemoveFromGame(void)
uint32_t Object::RemoveFromGame()
{
    return (uint32_t)(0);
}

// win1.41 00639b70 mac 103d2180 Object::GetDrawImportance(void)
float Object::GetDrawImportance()
{
    return *(float*)(*(char**)((char*)this + 0x28) + 0x000000f8);
}

// win1.41 00639b80 mac 103d2110 Object::GetDiscipleStateIfInteractedWith(GInterfaceStatus *, Villager *)
uint32_t Object::GetDiscipleStateIfInteractedWith(GInterfaceStatus* status, Villager* villager)
{
    return (uint32_t)(0);
}

// win1.41 00639b90 mac 103d1d50 Object::Save(GameOSFile &)
bool32_t Object::Save(GameOSFile& file)
{
    if (GameThingWithPos::Save(file))
    {
        file.WriteInfo(info);
        GameOSFileWriteCheckSum(file, obj_coords);
        GameOSFileWriteCheckSum(file, field_0x3c);
        GameOSFileWriteCheckSum(file, life);
        GameOSFileWriteCheckSum(file, scale);
        GameOSFileWriteCheckSum(file, y_angle);
        file.WritePtr(fire_effect);
        if ((field_0x24 & 0x40) && !(field_0xa & 0x10))
        {
            PhysicsObject* physObj = PhysicsObject::SearchForPhysicsObject(this);
            LHMatrix m;
            LHPoint p1;
            LHPoint p2;
            if (physObj != NULL)
            {
                m = physObj->field_0xa4;
                p1 = physObj->field_0x104;
                p2 = physObj->field_0x90;
            }
            else
            {
                m.m[0xb] = 0.0f;
                m.m[10] = 0.0f;
                m.m[9] = 0.0f;
                m.m[7] = 0.0f;
                m.m[6] = 0.0f;
                m.m[5] = 0.0f;
                m.m[3] = 0.0f;
                m.m[2] = 0.0f;
                m.m[1] = 0.0f;
                m.m[8] = 1.0f;
                m.m[4] = 1.0f;
                m.m[0] = 1.0f;
                p1.z = 0.0f;
                p1.y = 0.0f;
                p1.x = 0.0f;
                p2.z = 0.0f;
                p2.y = 0.0f;
                p2.x = 0.0f;
            }
            GameOSFileWriteCheckSum(file, m);
            GameOSFileWriteCheckSum(file, p1);
            GameOSFileWriteCheckSum(file, p2);
        }
        return true;
    }
    return false;
}

// win1.41 0063a220 mac 103d1140 Object::GetImmersionTexture(void)
IMMERSION_EFFECT_TYPE Object::GetImmersionTexture()
{
    return *(IMMERSION_EFFECT_TYPE*)(*(char**)((char*)this + 0x28) + 0x4c);
}


bool32_t Object::InteractsWithPhysicsObjects()
{
    return *(unsigned int *)((char *)this + 0x40) != 0;
}

// win1.41 006377d0 Object::ShouldPhysicsRaiseObjectUntilNotIntersectingThis(Object *)
bool Object::ShouldPhysicsRaiseObjectUntilNotIntersectingThis(Object* param_1)
{
    // forwards InteractsWithPhysicsObjects (slot 0x79c) via a bool-typed raw vtable call -> no int->bool normalize
    return (*(bool (__fastcall **)(Object*))((char*)*(void**)this + 0x79c))(this);
}
