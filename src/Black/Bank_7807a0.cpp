#include "ChallengeRoom.h"
#include "ChallengeRoomCamera.h"
#include "CreatureRoom.h"
#include "WorshipSpellIcon.h"
#include "WorshipTotem.h"



// win1.41 007807a0 mac 105b75c0 WorshipTotem::IsEffectReceiver(EffectValues *)
bool32_t WorshipTotem::IsEffectReceiver(EffectValues* param_1)
{
    return (bool32_t)(0);
}

// win1.41 007807b0 mac inlined WorshipTotem::SetSpecularColor(LH3DColor)
void WorshipTotem::SetSpecularColor(LH3DColor param_1)
{
    *(LH3DColor*)((char*)this + 0x0000008c) = param_1;
}

// win1.41 007807e0 mac 105b76e0 WorshipTotem::IsSacrificeAltar(void)
bool32_t WorshipTotem::IsSacrificeAltar()
{
    return (bool32_t)(1);
}

// win1.41 007807f0 mac 105b7720 WorshipTotem::GetSaveType(void)
uint32_t WorshipTotem::GetSaveType()
{
    return (uint32_t)(0x98);
}

// win1.41 00780800 mac 105b7760 WorshipTotem::GetDebugText(void)
char* WorshipTotem::GetDebugText()
{
    return (char*)(0xc24e44);
}

// win1.41 00780f00 mac 105b7a00 WorshipTotem::ResolveLoad(void)
void WorshipTotem::ResolveLoad()
{
    Object::ResolveLoad();
}
