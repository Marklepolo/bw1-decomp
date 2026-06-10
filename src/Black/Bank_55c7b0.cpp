#include "BaseInfo.h"
#include "Living.h"
#include "Mobile.h"
#include "Reaction.h"



// win1.41 0055c7b0 mac 10099cb0 Reaction::GetPlayer(void)
GPlayer* Reaction::GetPlayer()
{
    return *(GPlayer**)((char*)this + 0x38);
}

// win1.41 0055c7c0 mac 10134150 Reaction::SetPlayer(GPlayer *)
void Reaction::SetPlayer(GPlayer* param_1)
{
    *(uint32_t*)((char*)this + 0x38) = (uint32_t)param_1;
}

// win1.41 0055c7d0 mac 10049510 Reaction::GetRadius(void)
float Reaction::GetRadius()
{
    return *(float*)((char*)this + 0x3c);
}

// win1.41 0055c7e0 mac 10134280 Reaction::GetSaveType(void)
uint32_t Reaction::GetSaveType()
{
    return (uint32_t)0x00000026;
}

// win1.41 0055c7f0 mac 101342c0 Reaction::GetDebugText(void)
char* Reaction::GetDebugText()
{
    return (char*)0x00bed188;
}

// win1.41 0055c800 mac 10136550 Reaction::_dt(void)
Reaction::~Reaction()
{
}
