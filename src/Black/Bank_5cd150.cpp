#include "Influence.h"
#include "InfluenceInfo.h"
#include "Interface.h"
#include "InterfaceCollide.h"
#include "InterfaceFlags.h"
#include "InterfaceHandState.h"
#include "InterfaceMessageBuffer.h"
#include "InterfaceStatus.h"
#include "LeashStatus.h"



// win1.41 005cd150 mac 100fd4f0 GInfluenceInfo::_dt(void)
GInfluenceInfo::~GInfluenceInfo()
{
}

// win1.41 005ce2a0 mac 10368cb0 GInterfaceMessageBuffer::_dt(void)
GInterfaceMessageBuffer::~GInterfaceMessageBuffer()
{
}

// win1.41 005ce2f0 mac 10357e00 GInterface::GetSaveType(void)
uint32_t GInterface::GetSaveType()
{
    return (uint32_t)0x00000064;
}

// win1.41 005ce300 mac 10357e40 GInterface::GetDebugText(void)
char* GInterface::GetDebugText()
{
    return (char*)0x00bf1bdc;
}

// win1.41 005ce310 mac 1035c380 GInterface::_dt(void)
GInterface::~GInterface()
{
}

// win1.41 005ce340 mac 1035c820 GInterfaceFlags::_dt(void)
GInterfaceFlags::~GInterfaceFlags()
{
}

// win1.41 005ce360 mac 1035c790 InterfaceHandState::_dt(void)
InterfaceHandState::~InterfaceHandState()
{
}

// win1.41 005ce380 mac 1017a1d0 GInterfaceCollide::_dt(void)
GInterfaceCollide::~GInterfaceCollide()
{
}

// win1.41 005d0510 mac 10358340 GInterface::ResolveLoad(void)
__declspec(naked) void GInterface::ResolveLoad()
{
    __asm {
            xor eax, eax
            mov dword ptr [ecx + 0x000003b8], eax
            mov dword ptr [ecx + 0x000003bc], eax
            mov dword ptr [ecx + 0x000003c0], eax
            mov edx, 0x7f7fffff
            mov dword ptr [ecx + 0x000003c4], edx
            mov dword ptr [ecx + 0x000003c8], eax
            mov dword ptr [ecx + 0x000003cc], edx
            mov dword ptr [ecx + 0x000003d0], eax
            mov dword ptr [ecx + 0x000003d4], edx
            mov dword ptr [ecx + 0x000003d8], eax
            mov dword ptr [ecx + 0x000003dc], edx
            mov dword ptr [ecx + 0x4c], eax
            ret
        }
}

// win1.41 005db930 mac 1037ad30 GLeashStatus::GetSaveType(void)
uint32_t GLeashStatus::GetSaveType()
{
    return (uint32_t)0x00000102;
}

// win1.41 005db940 mac 1037aca0 GLeashStatus::_dt(void)
GLeashStatus::~GLeashStatus()
{
}

// win1.41 005db960 mac 1036bdc0 GInterfaceStatus::GetText(void)
const char* GInterfaceStatus::GetText()
{
    return (const char*)0x00bf2a60;
}

// win1.41 005db970 mac 1036be00 GInterfaceStatus::GetSaveType(void)
uint32_t GInterfaceStatus::GetSaveType()
{
    return (uint32_t)0x00000065;
}

// win1.41 005db980 mac 1036be40 GInterfaceStatus::GetDebugText(void)
char* GInterfaceStatus::GetDebugText()
{
    return (char*)0x00bf2a74;
}


uint32_t InfluenceRing::GetScriptObjectType()
{
    return (uint32_t)0xe;
}
