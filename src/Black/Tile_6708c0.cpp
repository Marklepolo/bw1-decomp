#include "PileFood.h"
#include "PileResource.h"
#include "PileWood.h"
#include "Pot.h"
#include "PotStructure.h"
#include "PrayerIconInfo.h"
#include "PrayerSite.h"
#include "PrayerSiteInfo.h"



// win1.41 006708c0 mac inlined PrayerSite::GetPlayer(void)
GPlayer* PrayerSite::GetPlayer()
{
    return (GPlayer*)(0);
}

// win1.41 006708e0 mac inlined PrayerSite::GetTown(void)
Town* PrayerSite::GetTown()
{
    return (Town*)(0);
}
