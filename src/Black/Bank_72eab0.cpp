#include "FireEffect.h"
#include "FireGraphic.h"
#include "Object.h"
#include "StoragePit.h"
#include "Stream.h"
#include "StreetLantern.h"
#include "StreetLight.h"
#include "TerrainMaterialInfo.h"
#include "Waterfall.h"



// win1.41 0072eab0 mac 1014cc60 FireEffect::GetPlayer(void)
GPlayer* FireEffect::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x20);
}

// win1.41 0072eac0 mac 101508d0 FireEffect::GetSaveType(void)
uint32_t FireEffect::GetSaveType()
{
    return (uint32_t)0x00000029;
}

// win1.41 0072ead0 mac 10150910 FireEffect::GetDebugText(void)
char* FireEffect::GetDebugText()
{
    return (char*)0x00c2295c;
}

// win1.41 0072eae0 mac 10150470 FireEffect::_dt(void)
FireEffect::~FireEffect()
{
}

// win1.41 007310d0 mac 1014bc70 FireEffect::ResolveLoad(void)
void FireEffect::ResolveLoad()
{
    CreateSprites();
}

// win1.41 00732ae0 mac 10149240 FireEffect::GetFirstCaused(void)
uint32_t FireEffect::GetFirstCaused()
{
    return *(uint32_t*)((char*)this + 0x44);
}

// win1.41 00734170 mac 10154230 GWaterfall::ToBeDeleted(int)
void GWaterfall::ToBeDeleted(int param_1)
{
}

// win1.41 007341b0 mac 10154110 GWaterfall::CallVirtualFunctionsForCreation(MapCoords const &)
void GWaterfall::CallVirtualFunctionsForCreation(const MapCoords& param_1)
{
}

// win1.41 00734650 mac 101534b0 GWaterfall::Save(GameOSFile &)
bool32_t GWaterfall::Save(GameOSFile& file)
{
    return (bool32_t)0x00000001;
}

// win1.41 00734660 mac 10153470 GWaterfall::Load(GameOSFile &)
bool32_t GWaterfall::Load(GameOSFile& file)
{
    return (bool32_t)0x00000001;
}

// win1.41 007349d0 mac 10535050 GStreetLantern::InteractsWithPhysicsObjects(void)
bool32_t GStreetLantern::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00734a70 mac 1002d8c0 GStreetLantern::Draw(void)
extern "C" void jmp_addr_0x0063b5d0(void);
extern "C" void jmp_addr_0x007feb30(void);
extern "C" void jmp_addr_0x00801c90(void);
__declspec(naked) void GStreetLantern::Draw()
{
    __asm {
            push ebx
            push ebp
            push esi
            mov ebx, ecx
            mov esi, dword ptr [ebx + 0x40]
            push edi
            lea edi, dword ptr [esi + 0x50]
            push edi
            lea ebp, dword ptr [esi + 0x4c]
            lea eax, dword ptr [esi + 0x38]
            push ebp
            push eax
            call jmp_addr_0x00801c90
            mov eax, dword ptr [edi]
            push ebp
            push eax
            lea eax, dword ptr [esi + 0x38]
            push eax
            call jmp_addr_0x007feb30
            add esp, 0x18
            mov dword ptr [edi], eax
            pop edi
            mov ecx, esi
            pop esi
            pop ebp
            mov edx, ebx
            pop ebx
            jmp jmp_addr_0x0063b5d0
        }
}

// win1.41 00734d40 mac 10003680 GStreetLantern::GetScriptObjectType(void)
uint32_t GStreetLantern::GetScriptObjectType()
{
    return (uint32_t)0x00000008;
}

// win1.41 00735230 mac 10542330 GTerrainMaterialInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GTerrainMaterialInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x0000002b;
    return (GBaseInfo*)0x00da0a20;
}

// win1.41 00735290 mac 105420c0 GTerrainMaterialInfo::_dt(void)
GTerrainMaterialInfo::~GTerrainMaterialInfo()
{
}
