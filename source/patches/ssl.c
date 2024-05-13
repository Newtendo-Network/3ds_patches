#include "ssl.h"

// https://github.com/SciresM/3DS-SSL-Patch
// Origin: 0x106C56
static const uint8_t noSSLPatch[] = {
	0xE7, 0x1D, 0xF9, 0x37, 0x3A, 0x1B, 0x90, 0x18, 0x1B, 0x30, 0x05, 0x43,
	0xBD, 0x62, 0x00, 0x2E, 0x04, 0xD0, 0x20, 0x1C, 0x20, 0x30, 0x31, 0x1C
};

void Patch_SSL_Module(uint32_t pid)
{
    Handle processHandle;
    Handle debugHandle;
    if(R_SUCCEEDED(svcOpenProcess(&processHandle, pid)))
    {
        if(R_SUCCEEDED(svcDebugActiveProcess(&debugHandle, pid)))
        {
            Patches_EatEvents(debugHandle);

            svcWriteProcessMemory(debugHandle, noSSLPatch, 0x00106C56, sizeof(noSSLPatch));

            svcCloseHandle(debugHandle);
        }
        svcCloseHandle(processHandle);
    }
}