#include "Script.h"
#include "ScriptMarker.h"



// win1.41 0070d960 mac 10501850 ScriptMarker::GetScriptObjectType(void)
uint32_t ScriptMarker::GetScriptObjectType()
{
    return (uint32_t)0x00000001;
}
