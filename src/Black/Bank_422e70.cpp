#include "Feature.h"
#include "lionhead/lh3dlib/development/LH3DObject.h"



// win1.41 00422e70 mac 100d1840 Feature::GetSaveType(void)
uint32_t Feature::GetSaveType()
{
    return (uint32_t)0x00000074;
}

// win1.41 00422e80 mac 100d1880 Feature::GetDebugText(void)
char* Feature::GetDebugText()
{
    return (char*)0x009c95b4;
}
