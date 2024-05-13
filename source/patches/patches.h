#pragma once

#include <3ds.h>
#include <string.h>

void Patches_WriteString(Handle debugHandle, u32 addr, const char *str);

void Patches_EatEvents(Handle debug);