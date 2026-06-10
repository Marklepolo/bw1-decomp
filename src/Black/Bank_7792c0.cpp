#include "PlannedWorshipSite.h"
#include "Workshop.h"
#include "WorshipSite.h"
#include "WorshipSiteInfo.h"



// win1.41 007792c0 mac inlined Workshop::IsWorkshop_0(void)
bool32_t Workshop::IsWorkshop()
{
    return (bool32_t)0x00000001;
}

// win1.41 007792d0 mac inlined Workshop::IsWorkshop_1(Creature *)
bool32_t Workshop::IsWorkshop(Creature* param_1)
{
    return (bool32_t)0x00000001;
}

// win1.41 007792e0 mac 10164890 Workshop::CanActAsAContainer(Creature *)
bool32_t Workshop::CanActAsAContainer(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 007792f0 mac 101648e0 Workshop::IsStoragePit(Creature *)
bool32_t Workshop::IsStoragePit(Creature* param_1)
{
    return (bool32_t)(0);
}

// win1.41 00779300 mac 10164920 Workshop::GetSaveType(void)
uint32_t Workshop::GetSaveType()
{
    return (uint32_t)(0x52);
}

// win1.41 00779310 mac 10164960 Workshop::GetDebugText(void)
char* Workshop::GetDebugText()
{
    return (char*)(0xc24cbc);
}

// win1.41 00779320 mac 101644f0 Workshop::_dt(void)
Workshop::~Workshop()
{
}

// win1.41 0077a330 mac 101625a0 Workshop::ResolveLoad(void)
void Workshop::ResolveLoad()
{
    Object::ResolveLoad();
}

// win1.41 0077a610 mac 10161f90 Workshop::ScaffoldMoved(Scaffold *)
__declspec(naked) void Workshop::ScaffoldMoved(Scaffold* param_1)
{
    __asm {
            mov eax, dword ptr [esp + 0x04]
            xor edx, edx
            mov dl, byte ptr [eax + 0x00000088]
            shr dl, 6
            and edx, 0x03
            mov byte ptr [edx + ecx * 0x1 + 0x000000dc], 0x01
            ret 4
        }
}

// win1.41 0077a8b0 mac 105b3c70 GWorshipSiteInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GWorshipSiteInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x9; return (GBaseInfo*)0xdcbd30;
}

// win1.41 0077a920 mac 105b0900 GWorshipSiteInfo::_dt(void)
GWorshipSiteInfo::~GWorshipSiteInfo()
{
}

// win1.41 0077bef0 mac 105ab110 PlannedWorshipSite::GetSaveType(void)
uint32_t PlannedWorshipSite::GetSaveType()
{
    return (uint32_t)(0x3b);
}

// win1.41 0077bf00 mac 105ab150 PlannedWorshipSite::GetDebugText(void)
char* PlannedWorshipSite::GetDebugText()
{
    return (char*)(0xc24d54);
}

// win1.41 0077bf10 mac 105ab030 PlannedWorshipSite::_dt(void)
PlannedWorshipSite::~PlannedWorshipSite()
{
}

// win1.41 0077d030 mac 105ae820 WorshipSite::UpdateFrom3DPosition(void)
void WorshipSite::UpdateFrom3DPosition()
{
}
