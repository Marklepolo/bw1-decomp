#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "AnimalDove.h"
#include "AnimalDove.h"
#include "AnimalBat.h"
#include "AnimalBat.h"
#include "AnimalCrow.h"
#include "AnimalPigeon.h"
#include "AnimalSeagull.h"
#include "AnimalSwallow.h"
#include "AnimalCow.h"
#include "AnimalSheep.h"
#include "AnimalSheep.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "AnimalGoat.h"
#include "AnimalGoat.h"
#include "AnimalHorse.h"
#include "AnimalHorse.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "AnimalZebra.h"
#include "AnimalZebra.h"
#include "AnimalPig.h"
#include "AnimalPig.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "AnimalTortoise.h"
#include "AnimalTortoise.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "AnimalDove.h"
#include "AnimalDove.h"
#include "AnimalDove.h"
#include "AnimalDove.h"
#include "AnimalDove.h"
#include "AnimalCrow.h"
#include "AnimalCrow.h"
#include "AnimalSwallow.h"
#include "AnimalSwallow.h"
#include "AnimalPigeon.h"
#include "AnimalSeagull.h"
#include "AnimalBat.h"
#include "AnimalBat.h"
#include "AnimalVulture.h"
#include "AnimalLeopard.h"
#include "AnimalLeopard.h"
#include "AnimalLion.h"
#include "AnimalLion.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "AnimalTiger.h"
#include "AnimalTiger.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "PuzzleGame.h"
#include "AnimalWolf.h"
#include "Animal.h"
#include "AnimatedStatic.h"
#include "AnimatedStaticInfo.h"
#include "Feature.h"
#include "FeatureInfo.h"
#include "MultiMapFixed.h"
#include "WorshipSiteUpgrade.h"



// win1.41 0041a2b0 mac 1007c6d0 Animal::SetStateSpeed(void)
void Animal::SetStateSpeed()
{
}

// win1.41 0041b200 mac 101662b0 Animal::GetScriptObjectType(void)
uint32_t Animal::GetScriptObjectType()
{
    return (uint32_t)(6);
}

// win1.41 00421f20 mac 100a67f0 GAnimatedStaticInfo::_dt(void)
GAnimatedStaticInfo::~GAnimatedStaticInfo()
{
}

// win1.41 00422000 mac 100a5570 MultiMapFixed::GetPercentAbodeFullWithAdults(void)
float MultiMapFixed::GetPercentAbodeFullWithAdults()
{
    return 1.0f;
}

// win1.41 00422010 mac 100a55c0 MultiMapFixed::GetPercentAbodeFullWithChildren(void)
float MultiMapFixed::GetPercentAbodeFullWithChildren()
{
    return 1.0f;
}

// win1.41 00422040 mac 100a56a0 MultiMapFixed::IsCivic(void)
bool32_t MultiMapFixed::IsCivic()
{
    return (bool32_t)(0);
}

// win1.41 00422050 mac 100a56e0 MultiMapFixed::IsWonder(void)
bool32_t MultiMapFixed::IsWonder()
{
    return (bool32_t)(0);
}

// win1.41 00422060 mac 100a5720 MultiMapFixed::GetAbodeType(void)
ABODE_TYPE MultiMapFixed::GetAbodeType()
{
    return ABODE_TYPE_GENERAL;
}

// win1.41 00422070 mac 100a5760 MultiMapFixed::DoResourceAdding(RESOURCE_TYPE, unsigned long, GInterfaceStatus *, bool, MapCoords const &, int)
__declspec(naked) uint32_t MultiMapFixed::DoResourceAdding(RESOURCE_TYPE type, GInterfaceStatus* iface, bool param_3, MapCoords* param_4, int param_5)
{
    __asm {
            xor eax, eax
            ret 24
        }
}

// win1.41 00422080 mac 100a57d0 MultiMapFixed::DoResourceRemoving(RESOURCE_TYPE, unsigned long, GInterfaceStatus *, bool *)
uint32_t MultiMapFixed::DoResourceRemoving(RESOURCE_TYPE type, uint32_t param_2, GInterfaceStatus* iface, bool param_4)
{
    return (uint32_t)(0);
}

// win1.41 00422090 mac inlined MultiMapFixed::SetTown(void)
void MultiMapFixed::SetTown(Town* town)
{
}

// win1.41 004220a0 mac 100a5880 MultiMapFixed::GetTown(void)
Town* MultiMapFixed::GetTown()
{
    return (Town*)(0);
}

// win1.41 004220b0 mac 100a58c0 MultiMapFixed::GetShouldNotBeAddedToPlanned(void)
bool32_t MultiMapFixed::GetShouldNotBeAddedToPlanned()
{
    return (bool32_t)(0);
}

// win1.41 004220c0 mac 100a5910 MultiMapFixed::SetShouldNotBeAddedToPlanned(int)
void MultiMapFixed::SetShouldNotBeAddedToPlanned(bool value)
{
}

// win1.41 00422140 mac 100a5490 Feature::GetCreatureBeliefType(void)
uint32_t Feature::GetCreatureBeliefType()
{
    return (uint32_t)(0xf);
}

// win1.41 004221a0 mac 100a5e20 AnimatedStatic::_dt(void)
AnimatedStatic::~AnimatedStatic()
{
}


GPlayer* SpellWolf::GetPlayer()
{
    return (GPlayer*)*(unsigned int *)((char *)this + 0x198);
}


void SpellWolf::SetPlayer(GPlayer* param_1)
{
    *(unsigned int *)((char *)this + 0x198) = (unsigned int)param_1;
}


void Animal::ResolveLoad()
{
    Living::ResolveLoad();
}

uint32_t PieceVillager::GetSaveType()
{
    return (uint32_t)0x9d;
}

char* PieceVillager::GetDebugText()
{
    return (char*)0x9c8f24;
}

uint32_t Dove::StandAnimation()
{
    return (uint32_t)0x8;
}

uint32_t SpellDove::StandAnimation()
{
    return (uint32_t)0x17;
}

uint32_t Bat::StandAnimation()
{
    return (uint32_t)0x2;
}

uint32_t SpellBat::StandAnimation()
{
    return (uint32_t)0x2;
}

uint32_t Crow::StandAnimation()
{
    return (uint32_t)0x7;
}

uint32_t Pigeon::StandAnimation()
{
    return (uint32_t)0x11;
}

uint32_t Seagull::StandAnimation()
{
    return (uint32_t)0x16;
}

uint32_t Swallow::StandAnimation()
{
    return (uint32_t)0x1b;
}

uint32_t Cow::GetSaveType()
{
    return (uint32_t)0x82;
}

uint32_t Sheep::GetSaveType()
{
    return (uint32_t)0x83;
}

char* Sheep::GetDebugText()
{
    return (char*)0x9c8fbc;
}

uint32_t PieceSheep::GetSaveType()
{
    return (uint32_t)0x9b;
}

char* PieceSheep::GetDebugText()
{
    return (char*)0x9c8fec;
}

uint32_t Goat::GetSaveType()
{
    return (uint32_t)0x84;
}

char* Goat::GetDebugText()
{
    return (char*)0x9c901c;
}

uint32_t Horse::GetSaveType()
{
    return (uint32_t)0x85;
}

char* Horse::GetDebugText()
{
    return (char*)0x9c9044;
}

uint32_t PieceHorse::GetSaveType()
{
    return (uint32_t)0x9b;
}

char* PieceHorse::GetDebugText()
{
    return (char*)0x9c9074;
}

uint32_t Zebra::GetSaveType()
{
    return (uint32_t)0x86;
}

char* Zebra::GetDebugText()
{
    return (char*)0x9c90a4;
}

uint32_t Pig::GetSaveType()
{
    return (uint32_t)0x87;
}

char* Pig::GetDebugText()
{
    return (char*)0x9c90cc;
}

bool32_t PiecePig::DecideWhatToDo()
{
    return (bool32_t)0x1;
}

uint32_t PiecePig::GetSaveType()
{
    return (uint32_t)0x9b;
}

char* PiecePig::GetDebugText()
{
    return (char*)0x9c90f0;
}

uint32_t Tortoise::GetSaveType()
{
    return (uint32_t)0x88;
}

char* Tortoise::GetDebugText()
{
    return (char*)0x9c9120;
}

uint32_t PieceTortoise::GetSaveType()
{
    return (uint32_t)0x9b;
}

char* PieceTortoise::GetDebugText()
{
    return (char*)0x9c9154;
}

uint32_t Dove::GetSaveType()
{
    return (uint32_t)0x8e;
}

char* Dove::GetDebugText()
{
    return (char*)0x9c9184;
}

uint32_t Dove::GetScriptObjectType()
{
    return (uint32_t)0x15;
}

uint32_t SpellDove::GetSaveType()
{
    return (uint32_t)0x90;
}

char* SpellDove::GetDebugText()
{
    return (char*)0x9c91d0;
}

uint32_t Crow::GetSaveType()
{
    return (uint32_t)0x8f;
}

char* Crow::GetDebugText()
{
    return (char*)0x9c91fc;
}

uint32_t Swallow::GetSaveType()
{
    return (uint32_t)0x91;
}

char* Swallow::GetDebugText()
{
    return (char*)0x9c9228;
}

uint32_t Pigeon::GetSaveType()
{
    return (uint32_t)0x92;
}

uint32_t Seagull::GetSaveType()
{
    return (uint32_t)0x93;
}

uint32_t Bat::GetSaveType()
{
    return (uint32_t)0x94;
}

uint32_t SpellBat::GetSaveType()
{
    return (uint32_t)0x95;
}

uint32_t Vulture::GetSaveType()
{
    return (uint32_t)0x96;
}

uint32_t Leopard::GetSaveType()
{
    return (uint32_t)0x8a;
}

char* Leopard::GetDebugText()
{
    return (char*)0x9c9354;
}

uint32_t Lion::GetSaveType()
{
    return (uint32_t)0x89;
}

char* Lion::GetDebugText()
{
    return (char*)0x9c9364;
}

uint32_t PieceLion::GetSaveType()
{
    return (uint32_t)0x9a;
}

char* PieceLion::GetDebugText()
{
    return (char*)0x9c93b0;
}

uint32_t SpellWolf::GetSaveType()
{
    return (uint32_t)0x8d;
}

char* SpellWolf::GetDebugText()
{
    return (char*)0x9c942c;
}

uint32_t Tiger::GetSaveType()
{
    return (uint32_t)0x8b;
}

char* Tiger::GetDebugText()
{
    return (char*)0x9c9474;
}

uint32_t Wolf::GetSaveType()
{
    return (uint32_t)0x8c;
}

char* Wolf::GetDebugText()
{
    return (char*)0x9c94bc;
}

uint32_t PieceWolf::GetSaveType()
{
    return (uint32_t)0x9c;
}

char* PieceWolf::GetDebugText()
{
    return (char*)0x9c94e8;
}

uint32_t ChessPion::GetSaveType()
{
    return (uint32_t)0x75;
}

char* ChessPion::GetDebugText()
{
    return (char*)0x9c95a4;
}


bool32_t PieceVillager::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0;
}

bool32_t Cow::IsCow(Creature* param_1)
{
    return (bool32_t)0x1;
}

uint32_t Dove::CanBePoodOn(Creature* param_1)
{
    return (uint32_t)0;
}

bool32_t Bat::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0x1;
}

bool32_t SpellBat::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0x1;
}

bool32_t Vulture::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0x1;
}

bool32_t Lion::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0x1;
}

bool32_t PieceLion::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0;
}

bool32_t PieceWolf::CanBeFrighteningToCreature(Creature* param_1)
{
    return (bool32_t)0;
}

// ==== AUTOHARVEST ====
// AUTOHARVEST ?StandAnimation@Lion@@UAEIXZ
uint32_t Lion::StandAnimation()
{
    return (uint32_t)0x6a;
}

// AUTOHARVEST ?StandAnimation@Leopard@@UAEIXZ
uint32_t Leopard::StandAnimation()
{
    return (uint32_t)0x50;
}

// AUTOHARVEST ?StandAnimation@Tiger@@UAEIXZ
uint32_t Tiger::StandAnimation()
{
    return (uint32_t)0xa4;
}

// AUTOHARVEST ?StandAnimation@Wolf@@UAEIXZ
uint32_t Wolf::StandAnimation()
{
    return (uint32_t)0xb8;
}

// AUTOHARVEST ?StandAnimation@SpellWolf@@UAEIXZ
uint32_t SpellWolf::StandAnimation()
{
    return (uint32_t)0xb8;
}

// AUTOHARVEST ?StandAnimation@PuzzleCow@@UAEIXZ
uint32_t PuzzleCow::StandAnimation()
{
    return (uint32_t)0x2a;
}

// AUTOHARVEST ?StandAnimation@Sheep@@UAEIXZ
uint32_t Sheep::StandAnimation()
{
    return (uint32_t)0x8e;
}

// AUTOHARVEST ?StandAnimation@Horse@@UAEIXZ
uint32_t Horse::StandAnimation()
{
    return (uint32_t)0x39;
}

// AUTOHARVEST ?StandAnimation@Pig@@UAEIXZ
uint32_t Pig::StandAnimation()
{
    return (uint32_t)0x7e;
}

// AUTOHARVEST ?StandAnimation@Tortoise@@UAEIXZ
uint32_t Tortoise::StandAnimation()
{
    return (uint32_t)0xab;
}

// AUTOHARVEST ?StandAnimation@PieceVillager@@UAEIXZ
uint32_t PieceVillager::StandAnimation()
{
    return (uint32_t)0x181;
}

// AUTOHARVEST ?GetDebugText@Cow@@UAEPADXZ
char* Cow::GetDebugText()
{
    return (char*)0x9c8f7c;
}

// AUTOHARVEST ?GetDebugText@Pigeon@@UAEPADXZ
char* Pigeon::GetDebugText()
{
    return (char*)0x9c9250;
}

// AUTOHARVEST ?GetDebugText@Seagull@@UAEPADXZ
char* Seagull::GetDebugText()
{
    return (char*)0x9c9278;
}

// AUTOHARVEST ?GetDebugText@Bat@@UAEPADXZ
char* Bat::GetDebugText()
{
    return (char*)0x9c929c;
}

// AUTOHARVEST ?GetDebugText@SpellBat@@UAEPADXZ
char* SpellBat::GetDebugText()
{
    return (char*)0x9c92c0;
}

// AUTOHARVEST ?GetDebugText@Vulture@@UAEPADXZ
char* Vulture::GetDebugText()
{
    return (char*)0x9c92f0;
}

// AUTOHARVEST ?GetNumTurnsToDieOver@SpellDove@@UAEIXZ
uint32_t SpellDove::GetNumTurnsToDieOver()
{
    return (uint32_t)0x14;
}

// AUTOHARVEST ?SetSpeed@SpellWolf@@UAEXH@Z
void SpellWolf::SetSpeed(int param_1)
{
}

// AUTOHARVEST ?GetNumTurnsToDieOver@SpellWolf@@UAEIXZ
uint32_t SpellWolf::GetNumTurnsToDieOver()
{
    return (uint32_t)0x14;
}

