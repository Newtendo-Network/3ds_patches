#include "patches.h"

void Patches_WriteString(Handle debugHandle, u32 addr, const char *str)
{
    svcWriteProcessMemory(debugHandle, str, addr, strlen(str) + 1);
}

void Patches_EatEvents(Handle debug)
{
    DebugEventInfo info;
    Result r;

    while (true)
    {
        if ((r = svcGetProcessDebugEvent(&info, debug)) != 0)
        {
            if (r == (s32)(0xd8402009))
                break;
        }
        svcContinueDebugEvent(debug, (DebugFlags)3);
    }
}