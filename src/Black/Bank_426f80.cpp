#include "Audio.h"
#include "ThingMusicInfo.h"



// win1.41 00426f80 mac 101791a0 GAudio::GetSaveType(void)
uint32_t GAudio::GetSaveType()
{
    return (uint32_t)0x00000101;
}

// win1.41 00426f90 mac 101791e0 GAudio::GetDebugText(void)
char* GAudio::GetDebugText()
{
    return (char*)0x009caf98;
}

// win1.41 00429300 mac 1017c940 ThingMusicInfo::GetSaveType(void)
uint32_t ThingMusicInfo::GetSaveType()
{
    return (uint32_t)0x00000109;
}

// win1.41 00429310 mac 1017c980 ThingMusicInfo::GetDebugText(void)
char* ThingMusicInfo::GetDebugText()
{
    return (char*)0x009cb3e4;
}

// win1.41 00429320 mac 1017c8b0 ThingMusicInfo::_dt(void)
ThingMusicInfo::~ThingMusicInfo()
{
}
