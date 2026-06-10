#include "HandStateMultiPickUp.h"
#include "HandStateNormal.h"
#include "HandStatePlayAnim.h"
#include "HandStateTotem.h"
#include "HandStateTug.h"



// win1.41 005b7510 mac 1033cb10 HandStatePlayAnim::Enter(void)
void HandStatePlayAnim::Enter()
{
    *(uint32_t*)((char*)this + 0x18) = 0x00000000;
}
