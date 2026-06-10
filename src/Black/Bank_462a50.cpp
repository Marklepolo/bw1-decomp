#include "PSysProperties.h"
#include "PSysProperties.h"
#include "CameraExclusion.h"
#include "CameraModeNew3.h"
#include "CameraModeTwoObjects.h"
#include "Citadel.h"
#include "CitadelEntrance.h"
#include "CitadelHeart.h"
#include "CitadelHeartInfo.h"
#include "CitadelInfo.h"
#include "CitadelPart.h"
#include "Config.h"
#include "Container.h"
#include "ContainerInfo.h"
#include "FireGraphic.h"
#include "HandState.h"
#include "HandStateInvisible.h"
#include "Object.h"
#include "PSysBase.h"
#include "PlannedCitadelHeart.h"
#include "PlannedCitadelPart.h"
#include "PlannedMultiMapFixed.h"
#include "PlannedTownCitadelHeart.h"
#include "WorshipSiteInfo.h"
#include "lionhead/lh3dlib/development/LH3DCamera.h"
#include "lionhead/lhfile/ver3.0/LHOSFile.h"



// win1.41 00462a50 mac 1005c760 Container::GetPlayer(void)
GPlayer* Container::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x2c);
}

// win1.41 00462a60 mac 101b6e50 Citadel::GetCreatureBeliefType(void)
uint32_t Citadel::GetCreatureBeliefType()
{
    return (uint32_t)0x00000002;
}

// win1.41 00462a70 mac 101b6e90 Citadel::GetCreatureBeliefListType(void)
uint32_t Citadel::GetCreatureBeliefListType()
{
    return (uint32_t)(0);
}

// win1.41 00462a80 mac 101b6ed0 Citadel::GetOrigin(void)
uint32_t Citadel::GetOrigin()
{
    return (uint32_t)0x00000002;
}

// win1.41 00462a90 mac 101b6f00 Citadel::IsSuitableForCreatureActivity(void)
bool32_t Citadel::IsSuitableForCreatureActivity()
{
    return (bool32_t)0x00000001;
}

// win1.41 00462aa0 mac 101b6f50 Citadel::GetText(void)
const char* Citadel::GetText()
{
    return (const char*)0x009ce038;
}

// win1.41 00462ab0 mac 101b6f80 Citadel::IsCitadel(void)
bool32_t Citadel::IsCitadel()
{
    return (bool32_t)0x00000001;
}

// win1.41 00462ac0 mac 101b6fb0 Citadel::GetSaveType(void)
uint32_t Citadel::GetSaveType()
{
    return (uint32_t)0x00000035;
}

// win1.41 00462ad0 mac 101b6ff0 Citadel::GetDebugText(void)
char* Citadel::GetDebugText()
{
    return (char*)0x009ce860;
}

// win1.41 00462ae0 mac 101b6d30 Citadel::_dt(void)
Citadel::~Citadel()
{
}

// win1.41 00464380 mac inlined GWorshipSiteInfo::GetAbodeType( const(void))
ABODE_TYPE GWorshipSiteInfo::GetAbodeType() const
{
    return ABODE_TYPE_CITADEL;
}

// win1.41 00464390 mac 101c1de0 GCitadelHeartInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GCitadelHeartInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x1; return (GBaseInfo*)0xc5e270;
}

// win1.41 004643e0 mac 101c1bf0 GCitadelHeartInfo::_dt(void)
GCitadelHeartInfo::~GCitadelHeartInfo()
{
}

// win1.41 004648b0 mac 100e33f0 Object::Draw(void)
void Object::Draw()
{
}

// win1.41 00464a80 mac 1008aa80 CitadelPart::GetCitadel(void)
Citadel* CitadelPart::GetCitadel()
{
    return *(Citadel**)((char*)this + 0x00000080);
}

// win1.41 00464a90 mac 101c2400 CitadelPart::GetMesh( const(void))
int CitadelPart::GetMesh() const
{
    return *(int*)(*(char**)((char*)this + 0x28) + 0x00000124);
}

// win1.41 00464aa0 mac 101c2460 CitadelPart::GetCreatureBeliefType(void)
uint32_t CitadelPart::GetCreatureBeliefType()
{
    return (uint32_t)0x00000004;
}

// win1.41 00464b00 mac inlined CitadelPart::IsCitadelPart_0(void)
bool32_t CitadelPart::IsCitadelPart()
{
    return (bool32_t)0x00000001;
}

// win1.41 00464b10 mac inlined CitadelPart::IsCitadelPart_1(Creature *)
bool32_t CitadelPart::IsCitadelPart(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 00464b20 mac inlined CitadelHeart::SetSpecularColor(LH3DColor)
void CitadelHeart::SetSpecularColor(LH3DColor param_1)
{
    *(LH3DColor*)((char*)this + 0x000000a0) = param_1;
}

// win1.41 00464b50 mac 101c2180 CitadelHeart::GetObjectCollide(void)
uint32_t CitadelHeart::GetObjectCollide()
{
    return *(uint32_t*)((char*)this + 0x00000090);
}

// win1.41 00464b60 mac 101c21c0 CitadelHeart::GetAbodeType(void)
ABODE_TYPE CitadelHeart::GetAbodeType()
{
    return ABODE_TYPE_CITADEL;
}

// win1.41 00464b70 mac 101c2200 CitadelHeart::ShouldFootpathsGoRound(void)
bool32_t CitadelHeart::ShouldFootpathsGoRound()
{
    return (bool32_t)(0);
}

// win1.41 00464b80 mac 101c2250 CitadelHeart::IsCitadelHeart(void)
bool32_t CitadelHeart::IsCitadelHeart()
{
    return (bool32_t)0x00000001;
}

// win1.41 00464b90 mac 10011680 CitadelHeart::Draw(void)
void CitadelHeart::Draw()
{
}

// win1.41 00464ba0 mac 101c2380 CitadelHeart::GetSaveType(void)
uint32_t CitadelHeart::GetSaveType()
{
    return (uint32_t)0x0000003a;
}

// win1.41 00464bb0 mac 101c23c0 CitadelHeart::GetDebugText(void)
char* CitadelHeart::GetDebugText()
{
    return (char*)0x009cea00;
}

// win1.41 00464bc0 mac 101c0df0 CitadelHeart::_dt(void)
CitadelHeart::~CitadelHeart()
{
}

// win1.41 00464da0 mac 101c0af0 CitadelHeart::SetToZero(void)
__declspec(naked) void CitadelHeart::SetToZero()
{
    __asm {
            xor eax, eax
            mov dword ptr [ecx + 0x000000a8], eax
            mov dword ptr [ecx + 0x0000008c], eax
            mov dword ptr [ecx + 0x00000098], eax
            mov dword ptr [ecx + 0x00000094], eax
            mov dword ptr [ecx + 0x000000a0], eax
            mov dword ptr [ecx + 0x000000a4], 0xffffffff
            mov dword ptr [ecx + 0x000000dc], eax
            mov dword ptr [ecx + 0x000000ac], eax
            mov dword ptr [ecx + 0x000000b0], eax
            mov dword ptr [ecx + 0x000000b4], eax
            mov byte ptr [ecx + 0x000000b8], al
            mov dword ptr [ecx + 0x000000bc], eax
            mov dword ptr [ecx + 0x000000c0], eax
            mov dword ptr [ecx + 0x000000cc], eax
            mov dword ptr [ecx + 0x000000c4], eax
            mov dword ptr [ecx + 0x000000c8], eax
            mov dword ptr [ecx + 0x000000d0], eax
            mov dword ptr [ecx + 0x000000d4], eax
            mov dword ptr [ecx + 0x000000e4], eax
            mov dword ptr [ecx + 0x78], eax
            ret
        }
}

// win1.41 00465560 mac 100d17b0 PlannedMultiMapFixed::IsWonder(void)
bool32_t PlannedMultiMapFixed::IsWonder()
{
    return (bool32_t)(0);
}

// win1.41 00465580 mac 101c20f0 PlannedCitadelPart::GetSaveType(void)
uint32_t PlannedCitadelPart::GetSaveType()
{
    return (uint32_t)0x00000037;
}

// win1.41 00465590 mac 101c2130 PlannedCitadelPart::GetDebugText(void)
char* PlannedCitadelPart::GetDebugText()
{
    return (char*)0x009cea5c;
}

// win1.41 004655a0 mac 101c2050 PlannedCitadelHeart::_dt(void)
PlannedCitadelHeart::~PlannedCitadelHeart()
{
}

// win1.41 004664e0 mac inlined FireGraphic::SpritePos::GetSaveType( (void))
uint32_t FireGraphic::SpritePos::GetSaveType()
{
    return 0;
}

// win1.41 004664f0 mac 10110ed0 PSysBase::GetDebugText(void)
char* PSysBase::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 00466500 mac 10086ed0 PSysBase::_dt(void)
PSysBase::~PSysBase()
{
}

// win1.41 00467b30 mac 101bdfc0 CitadelHeart::ChecksVerticesVObjects(void)
bool32_t CitadelHeart::ChecksVerticesVObjects()
{
    __asm { xor al, al }
}

// win1.41 00467b60 mac 101bdef0 CitadelHeart::GetPhysicsConstantsType(void)
uint32_t CitadelHeart::GetPhysicsConstantsType()
{
    return (uint32_t)(0);
}

// win1.41 00467e10 mac 101c1ee0 PlannedTownCitadelHeart::IsCivic(void)
bool32_t PlannedTownCitadelHeart::IsCivic()
{
    return (bool32_t)(0);
}

// win1.41 00467e20 mac 101c1f20 PlannedTownCitadelHeart::IsWonder(void)
bool32_t PlannedTownCitadelHeart::IsWonder()
{
    return (bool32_t)(0);
}

// win1.41 00467e30 mac 101c1f60 PlannedTownCitadelHeart::GetAbodeType(void)
ABODE_TYPE PlannedTownCitadelHeart::GetAbodeType()
{
    return ABODE_TYPE_CITADEL;
}

// win1.41 00467e40 mac 101c1fb0 PlannedTownCitadelHeart::GetSaveType(void)
uint32_t PlannedTownCitadelHeart::GetSaveType()
{
    return (uint32_t)0x00000039;
}

// win1.41 00467e50 mac 101c2000 PlannedTownCitadelHeart::GetDebugText(void)
char* PlannedTownCitadelHeart::GetDebugText()
{
    return (char*)0x009ceae0;
}

// win1.41 00467e60 mac 101c1e40 PlannedTownCitadelHeart::_dt(void)
PlannedTownCitadelHeart::~PlannedTownCitadelHeart()
{
}

// win1.41 004680b0 mac 101bd410 CitadelHeart::GetScriptObjectType(void)
uint32_t CitadelHeart::GetScriptObjectType()
{
    return (uint32_t)0x00000012;
}

// win1.41 00468da0 mac 101bc010 CitadelHeart::DestroyedByEffect(GPlayer *, float)
extern "C" void jmp_addr_0x00465ab0(void);
__declspec(naked) bool32_t CitadelHeart::DestroyedByEffect(GPlayer* param_1, float param_2)
{
    __asm {
            call jmp_addr_0x00465ab0
            mov eax, 0x00000001
            ret 8
        }
}

// win1.41 00468e60 mac 101bb570 CitadelEntrance::GetSaveType(void)
uint32_t CitadelEntrance::GetSaveType()
{
    return (uint32_t)0x00000110;
}

// win1.41 00468e70 mac 101bb5b0 CitadelEntrance::GetDebugText(void)
char* CitadelEntrance::GetDebugText()
{
    return (char*)0x009ceb20;
}

// win1.41 00468f90 mac 101bbbe0 CitadelEntrance::GetQueryFirstEnumText(void)
HELP_TEXT CitadelEntrance::GetQueryFirstEnumText()
{
    return (HELP_TEXT)0x7d0;
}

// win1.41 00468fa0 mac 101bbb70 CitadelEntrance::GetQueryLastEnumText(void)
HELP_TEXT CitadelEntrance::GetQueryLastEnumText()
{
    return this->GetQueryFirstEnumText();
}

// win1.41 00469380 mac 101bb5f0 CitadelEntrance::ResolveLoad(void)
void CitadelEntrance::ResolveLoad()
{
    *(uint32_t*)((char*)this + 0x28) = 0x00d41f68;
}

// win1.41 00469490 mac 101ba510 CitadelPart::Process(void)
uint32_t CitadelPart::Process()
{
    return (uint32_t)0x00000001;
}

// win1.41 004694a0 mac 101b91f0 CitadelPart::ConvertToPlanned(void)
PlannedMultiMapFixed* CitadelPart::ConvertToPlanned()
{
    return (PlannedMultiMapFixed*)(0);
}

// win1.41 004694d0 mac 101c37b0 CitadelPart::GetSaveType(void)
uint32_t CitadelPart::GetSaveType()
{
    return (uint32_t)0x00000036;
}

// win1.41 004694e0 mac 101c37f0 CitadelPart::GetDebugText(void)
char* CitadelPart::GetDebugText()
{
    return (char*)0x009ceb34;
}

// win1.41 004694f0 mac 101c3830 CitadelPart::ShouldFootpathsGoRound(void)
bool32_t CitadelPart::ShouldFootpathsGoRound()
{
    return (bool32_t)0x00000001;
}

// win1.41 00469500 mac 101c3520 CitadelPart::_dt(void)
CitadelPart::~CitadelPart()
{
}

// win1.41 004695c0 mac 101c32d0 CitadelPart::DestroyedByEffect(GPlayer *, float)
bool32_t CitadelPart::DestroyedByEffect(GPlayer* param_1, float param_2)
{
    return (bool32_t)(0);
}

// win1.41 004695d0 mac inlined CitadelPart::CanBeDestroyedBySpell_1(Spell *)
bool32_t CitadelPart::CanBeDestroyedBySpell(Spell* param_1)
{
    return 0;
}

// win1.41 00469750 mac 10075f70 CitadelPart::GetPlayer(void)
GPlayer* CitadelPart::GetPlayer()
{
    return *(GPlayer**)(*(char**)((char*)this + 0x00000080) + 0x2c);
}

// win1.41 0046b820 mac 100bfe80 GContainerInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GContainerInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000004;
    return (GBaseInfo*)0x00c5e5e8;
}

// win1.41 0046b900 mac 100bf890 Container::_dt(void)
Container::~Container()
{
}


bool32_t LeashObj::ValidAsInterfaceLeashTarget()
{
    return (bool32_t)0;
}

const char* LeashObj::GetText()
{
    return (const char*)0x9ce9f4;
}

void CitadelHeart::ResolveLoad()
{
    Object::ResolveLoad();
}

uint32_t UR_PlasmaInf::GetSaveType()
{
    return (uint32_t)0xba;
}

char* UR_PlasmaInf::GetDebugText()
{
    return (char*)0x9ceaa8;
}
