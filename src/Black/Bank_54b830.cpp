#include "Game.h"
#include "GestureSystem.h"
#include "GestureSystemData.h"
#include "GestureSystemDataList.h"
#include "GestureSystemResult.h"
#include "GlobalGameLists.h"
#include "KeyBuffer.h"
#include "PlayerInfo.h"
#include "SoundMap.h"
#include "TerrainMap.h"
#include "TerrainMapInfo.h"
#include "TerrainMapTypeInfo.h"
#include "lhall/released/headers/LHTimer.h"
#include "lionhead/lh3dlib/development/LH3DMapCoords.h"



// win1.41 0054b830 mac 1058eb00 GPlayerInfo::GetBaseInfo(unsigned long &)
__declspec(naked) GBaseInfo* GPlayerInfo::GetBaseInfo(uint32_t& param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            mov dword ptr [eax], 0x00000001
            mov eax, 0x00d47988
            ret 4
        }
}

// win1.41 0054b950 mac 10167a10 GKeyBuffer::_dt(void)
GKeyBuffer::~GKeyBuffer()
{
}

// win1.41 0054b9b0 mac 10512c00 GGame::GetSaveType(void)
uint32_t GGame::GetSaveType()
{
    return (uint32_t)(0x6a);
}

// win1.41 0054b9c0 mac 10496160 GGame::GetDebugText(void)
char* GGame::GetDebugText()
{
    return (char*)(0xbec3cc);
}

// win1.41 0054ba10 mac 100cb590 GSoundMap::_dt(void)
GSoundMap::~GSoundMap()
{
}

// win1.41 0054bd70 mac 10588760 TerrainMapTypeInfo::GetBaseInfo(unsigned long &)
GBaseInfo* TerrainMapTypeInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0;
        return (GBaseInfo*)0;
}

// win1.41 0054bd80 mac 1032d1b0 TerrainMapInfo::GetBaseInfo(unsigned long &)
GBaseInfo* TerrainMapInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0xe;
        return (GBaseInfo*)((char*)this + 0x10);
}

// win1.41 0054be50 mac 104e7bd0 GPlayerInfo::_dt(void)
GPlayerInfo::~GPlayerInfo()
{
}

// win1.41 0054bf00 mac 10512cc0 TerrainMapTypeInfo::_dt(void)
TerrainMapTypeInfo::~TerrainMapTypeInfo()
{
}

// win1.41 0054bf20 mac 104eff40 GGame::ClearVariables(void)
__declspec(naked) void GGame::ClearVariables()
{
    __asm {
            xor eax, eax
            mov byte ptr [ecx + 0x00250174], al
            mov dword ptr [ecx + 0x00250188], eax
            mov dword ptr [ecx + 0x00250194], eax
            mov dword ptr [ecx + 0x0025018c], eax
            mov dword ptr [ecx + 0x00250190], eax
            mov byte ptr [ecx + 0x002502c8], al
            mov dword ptr [ecx + 0x00205d44], eax
            mov dword ptr [ecx + 0x00250094], eax
            mov dword ptr [ecx + 0x00205d38], eax
            mov dword ptr [ecx + 0x002502c0], eax
            mov dword ptr [ecx + 0x00205d50], eax
            mov dword ptr [ecx + 0x00205d54], eax
            mov dword ptr [ecx + 0x00205d58], eax
            mov byte ptr [ecx + 0x00005978], 0x01
            mov byte ptr [ecx + 0x00005979], al
            mov byte ptr [ecx + 0x00005318], al
            mov dword ptr [ecx + 0x002502d0], eax
            mov dword ptr [ecx + 0x002502d4], eax
            mov dword ptr [ecx + 0x002502d8], eax
            mov dword ptr [ecx + 0x002502dc], eax
            mov dword ptr [ecx + 0x002502e0], eax
            mov dword ptr [ecx + 0x002502e4], eax
            mov dword ptr [ecx + 0x14], 0x00000020
            mov dword ptr [ecx + 0x00205a0c], eax
            mov dword ptr [ecx + 0x00205a10], eax
            mov dword ptr [ecx + 0x00205a14], eax
            mov dword ptr [ecx + 0x00205a18], eax
            mov dword ptr [ecx + 0x00205a1c], eax
            ret
        }
}
