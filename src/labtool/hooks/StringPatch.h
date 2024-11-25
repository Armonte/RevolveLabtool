#ifndef STRING_PATCH_H
#define STRING_PATCH_H

#include "pch.h"

class StringPatch {
public:
    static void PatchDebugStrings();

private:
    static void PatchColors(DWORD_PTR base);
    static void PatchMemory(uintptr_t address, const char* newString);
    static void PatchMemory(uintptr_t address, const char* bytes, size_t length);
    static void PatchMemory(uintptr_t address, BYTE value);
};

#endif