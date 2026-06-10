#include "GameOSFile.h"
#include "GameThing.h"
#include "GameThingWithPos.h"
#include "GatheringBox.h"
#include "MultiplayerConditionBox.h"
#include "SetupMP3Button.h"
#include "SetupStaticTextNoHit.h"
#include "stdbool.h"



// win1.41 0056fbe0 mac 101724b0 GameThing::Save(GameOSFile &)
bool32_t GameThing::Save(GameOSFile& file)
{
    uint32_t saveType = GetSaveType();

    GameOSFileWriteCheckSum(file, saveType);

    SaveExtraData(file);

    if (saveType != 0)
    {
        file.WriteCheckSum(this);

        GameOSFileWriteCheckSum(file, destroyed);
        GameOSFileWriteCheckSum(file, field_0xa);

        return 1;
    }
    return 0;
}

// win1.41 0056fe60 mac 100bbfe0 GameThingWithPos::GetPower( const(void))
float GameThingWithPos::GetPower() const
{
    return 0;
}

// win1.41 0056fec0 mac 10513050 GameThingWithPos::GetPSysPower( const(void))
float GameThingWithPos::GetPSysPower() const
{
    return 0;
}

// win1.41 0056fed0 mac 10160960 GameThing::MaintainSpell(Spell *, float)
__declspec(naked) void GameThing::MaintainSpell(uint32_t param_1, float param_2)
{
    __asm {
            fld dword ptr [esp + 0x08]
            ret 8
        }
}

// win1.41 0056ff50 mac 1056c0f0 GameThingWithPos::GetPhysicsMovementDirection(LHPoint *)
__declspec(naked) void GameThingWithPos::GetPhysicsMovementDirection(LHPoint* pos)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            xor ecx, ecx
            mov dword ptr [eax + 0x08], ecx
            mov dword ptr [eax + 0x04], ecx
            mov dword ptr [eax], ecx
            ret 4
        }
}

// win1.41 00570200 mac 100008c0 GameThingWithPos::GetScriptObjectType(void)
uint32_t GameThingWithPos::GetScriptObjectType()
{
    return 0;
}

// win1.41 00570210 mac 10357d80 GameThingWithPos::SetSpeedInMetres(float, int)
void GameThingWithPos::SetSpeedInMetres(float speed, int scale)
{
}

// win1.41 00570220 mac 103e3220 GameThingWithPos::GetSpeedInMetres( const(void))
float GameThingWithPos::GetSpeedInMetres() const
{
    return 0;
}

// win1.41 00570240 mac 101473d0 GameThingWithPos::GetDefaultSpeedInMetres(void)
float GameThingWithPos::GetDefaultSpeedInMetres()
{
    return 0;
}

// win1.41 00570250 mac 101723c0 GameThingWithPos::SetSpeedInMetresPerSecond(float, int)
void GameThingWithPos::SetSpeedInMetresPerSecond(float speed, int scale)
{
}

// win1.41 00570260 mac 1055f490 GameThingWithPos::GetSpeedInMetresPerSecond( const(void))
float GameThingWithPos::GetSpeedInMetresPerSecond() const
{
    return 0;
}

// win1.41 00570270 mac 100bc060 GameThingWithPos::GetRunningSpeedInMetresPerSecond(void)
float GameThingWithPos::GetRunningSpeedInMetresPerSecond()
{
    return 0;
}

// win1.41 00570280 mac 1055e070 GameThingWithPos::GetDefaultSpeedInMetresPerSecond(void)
float GameThingWithPos::GetDefaultSpeedInMetresPerSecond()
{
    return 0;
}

// win1.41 00570290 mac 1036ad90 GameThingWithPos::ForDrawFXGetNumVertices(void)
int GameThingWithPos::ForDrawFXGetNumVertices()
{
    return 0;
}

// win1.41 005702a0 mac 1056f610 GameThingWithPos::ForDrawFXGetVertexPos(long, LHPoint *)
void GameThingWithPos::ForDrawFXGetVertexPos(int param_1, LHPoint* param_2)
{
    __asm { xor al, al }
}

// win1.41 005703d0 mac 10174fb0 GameThingWithPos::GetFOVHelpMessageSet(void)
uint32_t GameThingWithPos::GetFOVHelpMessageSet()
{
    return 0;
}

// win1.41 005703e0 mac 100e46f0 GameThingWithPos::GetFOVHelpCondition(void)
uint32_t GameThingWithPos::GetFOVHelpCondition()
{
    return 0;
}

// win1.41 005703f0 mac 10512f10 GameThingWithPos::Save(GameOSFile &)
bool32_t GameThingWithPos::Save(GameOSFile& file)
{
    if (GameThing::Save(file))
    {
        GameOSFileWriteCheckSum(file, coords);
        GameOSFileWriteCheckSum(file, field_0x24);
        return true;
    }
    return false;
}

// win1.41 00570570 mac 10541fb0 GameThingWithPos::GetSpellCastPos(void)
__declspec(naked) void GameThingWithPos::GetSpellCastPos(MapCoords* outPos)
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

// win1.41 00570590 mac 101bf190 GameThingWithPos::GetOverwritePickUpToolTip(void)
uint32_t GameThingWithPos::GetOverwritePickUpToolTip()
{
    return 0;
}

// win1.41 005705a0 mac 100b34e0 GameThingWithPos::GetOverwriteInteractableToolTip(void)
uint32_t GameThingWithPos::GetOverwriteInteractableToolTip()
{
    return 0;
}

// win1.41 005705b0 mac 10097060 GameThingWithPos::GetOverwriteDropToolTip(void)
uint32_t GameThingWithPos::GetOverwriteDropToolTip()
{
    return 0;
}

// win1.41 005705c0 mac 103eff20 GameThingWithPos::GetOverwriteTapToolTip(void)
uint32_t GameThingWithPos::GetOverwriteTapToolTip()
{
    return 0;
}

// win1.41 005705d0 mac 10098a30 GameThingWithPos::SetToZero(void)
__declspec(naked) void GameThingWithPos::SetToZero()
{
    __asm {
            xor eax, eax
            mov word ptr [ecx + 0x24], ax
            mov dword ptr [ecx + 0x20], eax
            mov dword ptr [ecx + 0x14], eax
            mov dword ptr [ecx + 0x18], eax
            mov dword ptr [ecx + 0x1c], eax
            ret
        }
}

// win1.41 00571f10 mac 10328bc0 SetupStaticTextNoHit::~SetupStaticTextNoHit(void)
SetupStaticTextNoHit::~SetupStaticTextNoHit()
{
}

// win1.41 00571f30 mac 103547d0 SetupMP3Button::~SetupMP3Button(void)
SetupMP3Button::~SetupMP3Button()
{
}


IMPRESSIVE_TYPE GameThingWithPos::GetImpressiveType()
{
    return (IMPRESSIVE_TYPE)0x1b;
}
