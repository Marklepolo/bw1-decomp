#include "MPFEConnectionStatus.h"

bool MPFEConnectionStatus::IsInternetLobby()
{
    return *(unsigned int *)((char *)this + 0x0) == 0;
}
