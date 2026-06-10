#include "Script.h"
#include "ScriptHighlight.h"
#include "ScriptHighlightInfo.h"



// win1.41 007096b0 mac 104fb990 GScriptHighlightInfo::_dt(void)
GScriptHighlightInfo::~GScriptHighlightInfo()
{
}

// win1.41 00709740 mac 104fa180 ScriptHighlight::IsScriptHighlight(void)
bool32_t ScriptHighlight::IsScriptHighlight()
{
    return (bool32_t)0x00000001;
}

// win1.41 00709760 mac 104fa210 ScriptHighlight::PhysicsEditorCreate(int)
void ScriptHighlight::PhysicsEditorCreate(int param_1)
{
}

// win1.41 00709770 mac 104fa250 ScriptHighlight::ValidForPlaceInHand(GInterfaceStatus *)
bool32_t ScriptHighlight::ValidForPlaceInHand(GInterfaceStatus* param_1)
{
    return 0;
}

// win1.41 00709780 mac 104fa2b0 ScriptHighlight::ApplyOnlyAfterReleased(void)
uint32_t ScriptHighlight::ApplyOnlyAfterReleased()
{
    return 0;
}

// win1.41 007097a0 mac 104fa370 ScriptHighlight::CanBeSleptNextToByCreature(Creature *)
bool32_t ScriptHighlight::CanBeSleptNextToByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 007097b0 mac 104fa3d0 ScriptHighlight::CanBeDestroyedByStoning(Creature *)
bool32_t ScriptHighlight::CanBeDestroyedByStoning(Creature* param_1)
{
    return 0;
}

// win1.41 007097c0 mac 104fa420 ScriptHighlight::CanBeSetOnFire(Creature *)
bool32_t ScriptHighlight::CanBeSetOnFire(Creature* param_1)
{
    return 0;
}

// win1.41 007097d0 mac 104fa470 ScriptHighlight::CanBeCrushed(void)
bool32_t ScriptHighlight::CanBeCrushed()
{
    return 0;
}

// win1.41 007097e0 mac 104fa4b0 ScriptHighlight::IsEffectReceiver(EffectValues *)
bool32_t ScriptHighlight::IsEffectReceiver(EffectValues* param_1)
{
    return 0;
}

// win1.41 00709800 mac 104fa550 ScriptHighlight::ValidAsInterfaceTarget(void)
bool32_t ScriptHighlight::ValidAsInterfaceTarget()
{
    return 0;
}

// win1.41 00709810 mac 104fa5a0 ScriptHighlight::CanBecomeAPhysicsObject(void)
bool32_t ScriptHighlight::CanBecomeAPhysicsObject()
{
    return 0;
}

// win1.41 00709820 mac 104fa5f0 ScriptHighlight::InteractsWithPhysicsObjects(void)
bool32_t ScriptHighlight::InteractsWithPhysicsObjects()
{
    __asm { xor al, al }
}

// win1.41 00709830 mac 104fa640 ScriptHighlight::CanBePickedUpByCreature(Creature *)
bool32_t ScriptHighlight::CanBePickedUpByCreature(Creature* param_1)
{
    return 0;
}

// win1.41 00709840 mac 104fa690 ScriptHighlight::InterfaceMustBeInInfluenceForInteraction(void)
bool32_t ScriptHighlight::InterfaceMustBeInInfluenceForInteraction()
{
    return 0;
}

// win1.41 00709850 mac 104fa6f0 ScriptHighlight::GetSaveType(void)
uint32_t ScriptHighlight::GetSaveType()
{
    return (uint32_t)0x0000003f;
}

// win1.41 00709860 mac 104fa730 ScriptHighlight::GetDebugText(void)
char* ScriptHighlight::GetDebugText()
{
    return (char*)0x00c205dc;
}

// win1.41 00709870 mac 104fc120 ScriptHighlight::_dt(void)
ScriptHighlight::~ScriptHighlight()
{
}

// win1.41 0070ae10 mac 104fa8c0 ScriptHighlight::GetOverwriteTapToolTip(void)
__declspec(naked) uint32_t ScriptHighlight::GetOverwriteTapToolTip()
{
    __asm {
            mov eax, dword ptr [ecx + 0x28]
            mov edx, dword ptr [eax + 0x10]
            xor ecx, ecx
            cmp edx, 0x01
            setne cl
            dec ecx
            and ecx, 0x00000ef2
            mov eax, ecx
            ret
        }
}

// win1.41 0070ae30 mac 100083b0 ScriptHighlight::GetScriptObjectType(void)
uint32_t ScriptHighlight::GetScriptObjectType()
{
    return (uint32_t)0x00000025;
}

// win1.41 0070ae40 mac 104fa770 ScriptHighlight::AddToRoutePlan(RPHolder *, Creature *, int, void (*)(int, Point2D, float, int))
extern "C" void jmp_addr_0x00638b00(void);
__declspec(naked) void ScriptHighlight::AddToRoutePlan(RPHolder* param_1, Creature* param_2, int param_3, void (__cdecl* param_4)(int, Point2D, float, int))
{
    __asm {
            mov eax, dword ptr [esp + 0x10]
            mov edx, dword ptr [esp + 0x0c]
            push eax
            mov eax, dword ptr [esp + 0x0c]
            push edx
            mov edx, dword ptr [esp + 0x0c]
            push eax
            push edx
            call jmp_addr_0x00638b00
            ret 16
        }
}
