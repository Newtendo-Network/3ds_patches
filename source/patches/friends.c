#include "friends.h"

void Patch_Friends_Module(uint32_t pid)
{
    Handle processHandle;
    Handle debugHandle;
    if(R_SUCCEEDED(svcOpenProcess(&processHandle, pid)))
    {
        if(R_SUCCEEDED(svcDebugActiveProcess(&debugHandle, pid)))
        {
            Patches_EatEvents(debugHandle);

            Patches_WriteString(debugHandle, 0x00161279, FRIENDS_NASC_PROD_URL);
            Patches_WriteString(debugHandle, 0x0016129A, FRIENDS_NASC_TEST_URL);
            Patches_WriteString(debugHandle, 0x001612C0, FRIENDS_NASC_DEV_URL);

            svcCloseHandle(debugHandle);
        }
        svcCloseHandle(processHandle);
    }
}