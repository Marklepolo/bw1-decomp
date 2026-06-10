#include "DialogBoxBase.h"
#include "DialogBoxKeyBinding.h"



// win1.41 005127b0 mac 102b1e90 DialogBoxKeyBinding::DialogBoxKeyBinding(void)
DialogBoxKeyBinding::DialogBoxKeyBinding()
{
}

// win1.41 00512bc0 mac 102b1890 DialogBoxKeyBinding::Destroy(void)
void DialogBoxKeyBinding::Destroy()
{
    DialogBoxBase::Destroy();
}
