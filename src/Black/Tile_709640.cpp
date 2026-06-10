#include "Script.h"
#include "ScriptHighlight.h"
#include "ScriptHighlightInfo.h"



// win1.41 00709640 mac 104fc510 GScriptHighlightInfo::GetBaseInfo(unsigned long &)
GBaseInfo* GScriptHighlightInfo::GetBaseInfo(uint32_t& param_1)
{
    param_1 = 0x00000004;
    return (GBaseInfo*)0x00d96390;
}
