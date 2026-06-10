#include "CameraExclusion.h"
#include "CameraModeNew3.h"
#include "CameraModeTwoObjects.h"
#include "Citadel.h"
#include "CitadelEntrance.h"
#include "CitadelHeart.h"
#include "CitadelHeartInfo.h"
#include "CitadelInfo.h"
#include "CitadelPart.h"
#include "Config.h"
#include "Container.h"
#include "ContainerInfo.h"
#include "FireGraphic.h"
#include "HandState.h"
#include "HandStateInvisible.h"
#include "Object.h"
#include "PSysBase.h"
#include "PlannedCitadelHeart.h"
#include "PlannedCitadelPart.h"
#include "PlannedMultiMapFixed.h"
#include "PlannedTownCitadelHeart.h"
#include "WorshipSiteInfo.h"
#include "lionhead/lh3dlib/development/LH3DCamera.h"
#include "lionhead/lhfile/ver3.0/LHOSFile.h"



// win1.41 00462980 mac 101bb430 GCitadelInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GCitadelInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000001;
    return (GBaseInfo*)0x00c5e1e8;
}
