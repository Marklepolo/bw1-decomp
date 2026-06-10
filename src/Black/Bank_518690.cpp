#include "Creature.h"
#include "Feature.h"
#include "MobileObject.h"
#include "MobileStatic.h"
#include "MultiMapFixed.h"
#include "Object.h"
#include "OneOffSpellSeed.h"
#include "Rock.h"
#include "Scaffold.h"
#include "SpellIcon.h"
#include "SpellSeed.h"
#include "StoragePit.h"
#include "WorshipSite.h"
#include "WorshipTotem.h"



// win1.41 00518690 mac 100238a0 Feature::Draw(void)
void Feature::Draw()
{
    MultiMapFixed::Draw();
}

// win1.41 00518710 mac 100c8c10 SpellSeed::Draw(void)
void SpellSeed::Draw()
{
}

// win1.41 00519350 mac 1001a950 StoragePit::Draw(void)
void StoragePit::Draw()
{
    Abode::Draw();
}
