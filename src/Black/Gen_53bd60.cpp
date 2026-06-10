#include "EndGameBox.h"
#include "SkipBox.h"

bool32_t EndGameBox::CanESCOut()
{
    __asm { xor al, al }
}

bool32_t SkipBox::CanESCOut()
{
    __asm { xor al, al }
}
