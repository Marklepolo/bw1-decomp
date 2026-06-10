#include "DancePathInfo.h"
#include "GestureSystemData.h"
#include "GestureSystemDataList.h"
#include "Global.h"
#include "GlobalGameLists.h"
#include "Graveyard.h"
#include "GroupBehaviour.h"
#include "Persistent.h"



// win1.41 00580a10 mac 102cb7a0 Persistent::VirtualFunc(void)
void Persistent::VirtualFunc()
{
}

// win1.41 00580a20 mac 102cb7e0 Persistent::OnLoaded(void)
void Persistent::OnLoaded()
{
}

// win1.41 00580a30 mac 102cb810 Persistent::DefineProperties(PropertyList *)
void Persistent::DefineProperties(PropertyList* param_1)
{
}

// win1.41 00580a40 mac 102cbd80 Persistent::_dt(void)
Persistent::~Persistent()
{
}

// win1.41 00595cd0 mac 100f4d60 Graveyard::InteractsWithPhysicsObjects(void)
bool32_t Graveyard::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00596190 mac 100fa600 GroupBehaviour::_dt(void)
GroupBehaviour::~GroupBehaviour()
{
}
