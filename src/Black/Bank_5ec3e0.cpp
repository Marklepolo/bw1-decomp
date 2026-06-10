#include "PuzzleGame.h"
#include "DataPath.h"
#include "LHInetWeather.h"
#include "Living.h"
#include "LivingAction.h"
#include "Mobile.h"
#include "lionhead/lhmultiplayer/ver4.0/LHLobby.h"



// win1.41 005ec3e0 mac 10382af0 Living::GetNumTurnsToDieOver(void)
uint32_t Living::GetNumTurnsToDieOver()
{
    return (uint32_t)(0x258);
}

// win1.41 005ecc10 mac 10084310 Living::IsDancing(void)
bool32_t Living::IsDancing()
{
    return (bool32_t)(this->dance_group != NULL);
}

// win1.41 005ecf60 mac 1006ced0 Living::GetFlockPos(void)
__declspec(naked) MapCoords* Living::GetFlockPos()
{
    __asm {
            mov eax, dword ptr [ecx + 0x000000b8]
            test eax, eax
            jne L_005ecf6b
            ret
            L_005ecf6b:
            add eax, 0x14
            ret
        }
}

// win1.41 005ed4f0 mac 103801d0 Living::CanBecomeAPhysicsObject(void)
bool32_t Living::CanBecomeAPhysicsObject()
{
    return (bool32_t)(1);
}

// win1.41 005ed580 mac inlined Living::ExitInLanded(VILLAGER_STATES)
int Living::ExitInLanded(VILLAGER_STATES param_1)
{
    return (int)(1);
}

// win1.41 005edd90 mac inlined Living::EnterMoveToPos(VILLAGER_STATES, VILLAGER_STATES)
uint32_t Living::EnterMoveToPos(VILLAGER_STATES param_1, VILLAGER_STATES param_2)
{
    return (uint32_t)(1);
}

// win1.41 005edda0 mac 1001fb70 Living::ExitMoveToPos(unsigned char)
extern "C" void jmp_addr_0x0060a9f0(void);
__declspec(naked) int Living::ExitMoveToPos(uint8_t param_1)
{
    __asm {
            push esi
            mov esi, ecx
            push esi
            lea ecx, dword ptr [esi + 0x70]
            call jmp_addr_0x0060a9f0
            mov dword ptr [esi + 0x60], 0x00000000
            mov eax, 0x00000001
            pop esi
            ret 4
        }
}

// win1.41 005eddc0 mac 1037f2a0 Living::ExitBeingEaten(unsigned char)
int Living::ExitBeingEaten(uint8_t param_1)
{
    return (int)(1);
}

// win1.41 005eed20 mac 1037d880 Living::ResolveLoad(void)
void Living::ResolveLoad()
{
    Object::ResolveLoad();
}

// win1.41 005ef070 mac 10383840 DataPath::GetSaveType(void)
uint32_t DataPath::GetSaveType()
{
    return (uint32_t)(0x99);
}

// win1.41 005ef080 mac 10383880 DataPath::GetDebugText(void)
char* DataPath::GetDebugText()
{
    return (char*)(0xbf3ac8);
}

// win1.41 005ef090 mac 1037d2b0 DataPath::_dt(void)
DataPath::~DataPath()
{
}

// win1.41 005ef340 mac 1037cc80 Living::GetInHandImmersionTexture(void)
IMMERSION_EFFECT_TYPE Living::GetInHandImmersionTexture()
{
    return IMMERSION_EFFECT_TYPE_ANIMATING_IN_HAND;
}


bool32_t PuzzleHorse::InHand()
{
    return (bool32_t)0x1;
}

uint32_t DataForScriptRemind::GetSaveType()
{
    return (uint32_t)0x105;
}

// ==== AUTOHARVEST ====
// AUTOHARVEST ?Birthday@PuzzleHorse@@UAEXXZ
void PuzzleHorse::Birthday()
{
}

// AUTOHARVEST ?GetDebugText@DataForScriptRemind@@UAEPADXZ
char* DataForScriptRemind::GetDebugText()
{
    return (char*)0xbf3afc;
}

