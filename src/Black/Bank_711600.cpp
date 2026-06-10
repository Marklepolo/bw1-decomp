#include "ScriptTimer.h"
#include "SecretCreature.h"
#include "Settings.h"



// win1.41 00711600 mac 10506a30 ScriptTimer::GetScriptObjectType(void)
uint32_t ScriptTimer::GetScriptObjectType()
{
    return (uint32_t)0x00000011;
}

// win1.41 00711d60 mac 101441a0 SecretCreature::_dt(void)
SecretCreature::~SecretCreature()
{
}
