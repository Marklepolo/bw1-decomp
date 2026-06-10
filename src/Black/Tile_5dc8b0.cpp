#include "InfluenceInfo.h"
#include "Interface.h"
#include "InterfaceCollide.h"
#include "InterfaceFlags.h"
#include "InterfaceHandState.h"
#include "InterfaceMessageBuffer.h"
#include "InterfaceStatus.h"
#include "LeashStatus.h"



// win1.41 005dc8b0 mac 10035b20 GInterfaceStatus::GetInterface(void)
GInterface* GInterfaceStatus::GetInterface()
{
    return *(GInterface**)((char*)this + 0x2c);
}
