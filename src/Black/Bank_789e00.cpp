#include "CreatureRoom.h"
#include "CreatureRoomCamera.h"
#include "InnerCamera.h"



// win1.41 00789e00 mac 10288de0 CreatureRoomCamera::Close(void)
void CreatureRoomCamera::Close()
{
    InnerCamera::Close();
}
