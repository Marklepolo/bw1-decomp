#include "JPSysInterface.h"
#include "PSysManager.h"



// win1.41 00672c90 mac 10423cc0 PSysManager::GetSaveType(void)
uint32_t PSysManager::GetSaveType()
{
    return (uint32_t)0x000000a4;
}

// win1.41 00672ca0 mac 10423d00 PSysManager::GetDebugText(void)
char* PSysManager::GetDebugText()
{
    return (char*)0x009ceaa8;
}

// win1.41 00672cb0 mac 103dcfb0 PSysManager::_dt(void)
PSysManager::~PSysManager()
{
}

// win1.41 006735c0 mac 103dc100 PSysManager::GetPlayer(void)
GPlayer* PSysManager::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x18);
}
