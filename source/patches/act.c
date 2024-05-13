#include "act.h"

/*
int patch_ACT_GetServerURL(void* _this, const char* subdomain, const char* otherSubdomain, int ver)
{
    const char* nintendoURL = "nintendo.net";
    const char* pretendoURL = "pretendo.cc";
    const char* newtendoURL = "newtendo.net";

    int (*FRD_GetServerTypes)(unsigned int* outType, unsigned int* outEnv, unsigned char* outEnvNum) = (void*)0x105340;
    void (*ACT_RequestBuilder_SetServerURL)(void* _this, const char* url, int unk) = (void*)0x10ed48;
    int (*ACT_snprintf)(char* buffer, int size, const char* format, ...) = (void*)0x114310;

    char buffer[128];
    unsigned int type, env;
    unsigned char envNum;

    FRD_GetServerTypes(&type, &env, &envNum);

    const char* url = (type == 2) ? newtendoURL : nintendoURL;


    ACT_snprintf(buffer, sizeof(buffer), "https://%s%saccount.%s/v%u/api/", subdomain, otherSubdomain, url, ver);
    ACT_RequestBuilder_SetServerURL((void*)((unsigned int)_this + 4), buffer, 0);
    return 0;
}
*/

// Origin: 0x10E4F8
// Generated from Godbolt with -Os (above C function, then tuned by hand)
static const uint8_t act_patch[] = {
    0xF0, 0xB5,                 // push {r4, r5, r6, r7, lr}
    0x16, 0x1C,                 // mov r6, r2
    0x14, 0x22,                 // mov r2, #20
    0xA9, 0xB0,                 // sub sp, sp, #164
    0x05, 0xAA,                 // add r2, sp, #20
    0x04, 0x1C,                 // mov r4, r0
    0x0D, 0x1C,                 // mov r5, r1
    0x1F, 0x1C,                 // mov r7, r3
    0x07, 0xA9,                 // add r1, sp, #28
    0x06, 0xA8,                 // add r0, sp, #24
    0xF6, 0xF7, 0x18, 0xFF,     // bl FRD_GetServerTypes
    0x06, 0x9A,                 // ldr r2, [sp, #24]
    0x10, 0xA3,                 // adr r3, newtendoURL
    0x02, 0x2A,                 // cmp r2, #2
    0x03, 0xD0,                 // beq @end
    0x0A, 0xA3,                 // adr r3, nintendoURL
    0x00, 0x2A,                 // cmp r2, #0
    0x00, 0xD0,                 // beq @end
    0x19, 0xA3,                 // adr r3, pretendoURL
    0x01, 0x93,                 // str r3, [sp, #4]
    0x80, 0x21,                 // mov r1, #128
    0x2B, 0x1C,                 // mov r3, r5
    0x0F, 0xA2,                 // adr r2, formatURL
    0x02, 0x97,                 // str r7, [sp, #8]
    0x00, 0x96,                 // str r6, [sp]
    0x08, 0xA8,                 // add r0, sp, #32
    0x05, 0xF0, 0xEF, 0xFE,     // bl ACT_snprintf
    0x20, 0x1D,                 // add r0, r4, #4
    0x00, 0x22,                 // mov r2, #0
    0x08, 0xA9,                 // add r1, sp, #32
    0x00, 0xF0, 0x06, 0xFC,     // bl ACT_RequestBuilder_SetServerURL
    0x00, 0x20,                 // mov r0, #0
    0x29, 0xB0,                 // add sp, sp, #164
    0xF0, 0xBD,                 // pop {r4, r5, r6, r7, pc}
    0x00, 0x00,                 // ==================================== Padding
    // String "nintendo.net"
    0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x2E, 0x6E, 0x65, 0x74, 0x00, 0x00, 0x00, 0x00,
    // String "newtendo.net"
    0x6E, 0x65, 0x77, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x2E, 0x6E, 0x65, 0x74, 0x00, 0x00, 0x00, 0x00,
    // String "https://%s%saccount.%s/v%u/api/"
    0x68, 0x74, 0x74, 0x70, 0x73, 0x3A, 0x2F, 0x2F, 0x25, 0x73, 0x25, 0x73, 0x61, 0x63, 0x63, 0x6F, 0x75, 0x6E, 0x74, 0x2E, 0x25, 0x73, 0x2F, 0x76, 0x25, 0x75, 0x2F, 0x61, 0x70, 0x69, 0x2F, 0x00,
    // String "pretendo.cc"
    0x70, 0x72, 0x65, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x2E, 0x63, 0x63, 0x00
};


void Patch_ACT_Module(uint32_t pid)
{
    Handle processHandle;
    Handle debugHandle;
    if(R_SUCCEEDED(svcOpenProcess(&processHandle, pid)))
    {
        if(R_SUCCEEDED(svcDebugActiveProcess(&debugHandle, pid)))
        {
            Patches_EatEvents(debugHandle);

            svcWriteProcessMemory(debugHandle, act_patch, 0x10e4f8, sizeof(act_patch));

            svcCloseHandle(debugHandle);
        }
        svcCloseHandle(processHandle);
    }
}