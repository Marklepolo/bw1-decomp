#include "Script.h"
#include "ScriptCreatureCurse.h"
#include "ScriptDLL.h"



// win1.41 006f62b0 mac 104e7c70 GScript::ScriptErrorMessage(char*)
__declspec(naked) void GScript::ScriptErrorMessage(char* msg)
{
    __asm {
            ret
        }
}

// win1.41 006f62c0 mac 100054c0 GScript::ScriptWarningMessage(char*)
__declspec(naked) void GScript::ScriptWarningMessage(char* msg)
{
    __asm {
            ret
        }
}
