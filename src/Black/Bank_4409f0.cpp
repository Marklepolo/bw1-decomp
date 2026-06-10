#include "BWLan.h"
#include "Camera.h"
#include "MapCoords.h"
#include "lionhead/lh3dlib/development/LHPoint.h"
#include "lionhead/lh3dlib/development/Zoomer.h"



// win1.41 004409f0 mac 101812f0 BWLan::LeaveMainRoom(void)
void BWLan::LeaveMainRoom()
{
    (*(void (__fastcall **)(BWLan*))((char*)*(void**)this + 0x2c))(this);
}

// win1.41 004415b0 mac 1017fff0 BWLan::StartGame(void)
void BWLan::StartGame()
{
}

// win1.41 00441af0 mac 101980f0 GCamera::GetText(void)
const char* GCamera::GetText()
{
    return (const char*)0x009cd9d8;
}

// win1.41 00441b10 mac 101982b0 GCamera::GetHeight(void)
float GCamera::GetHeight()
{
    return *(float*)((char*)this + 0x1c);
}

// win1.41 00441b20 mac 101982e0 GCamera::GetSaveType(void)
uint32_t GCamera::GetSaveType()
{
    return (uint32_t)0x00000077;
}

// win1.41 00441b30 mac 10378450 GCamera::_dt(void)
GCamera::~GCamera()
{
}

// win1.41 00441380 mac 10180f30 BWLan::InitialiseLobbyState(void)
bool BWLan::InitialiseLobbyState()
{
    return true;
}
