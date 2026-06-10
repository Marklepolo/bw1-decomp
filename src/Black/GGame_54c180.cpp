#include "Camera.h"
#include "CameraEditor.h"
#include "Game.h"
#include "Global.h"
#include "HelpSystem.h"
#include "Interface.h"
#include "lionhead/lh3dlib/development/LH3DRender.h"
#include "lionhead/lh3dlib/development/LHCoord.h"
#include "lionhead/lhlib/ver5.0/LHMouse.h"
#include "lionhead/lhlib/ver5.0/LHSystem.h"



// win1.41 0054c180 mac 1003a410 GGame::GetCamera(void)
GCamera* GGame::GetCamera()
{
    return this->camera;
}

// win1.41 0054c330 mac 10496be0 GGame::Delete(void)
void GGame::Delete()
{
}

// win1.41 0054d820 mac 10083dd0 GGame::ProcessGameCode(void)
void GGame::ProcessGameCode()
{
    StartTurn();
    if ((field_0x14 & 4) == 0)
    {
        ProcessTurn();
    }
    EndTurn();
}
