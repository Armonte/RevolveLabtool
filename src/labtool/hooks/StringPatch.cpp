#include "StringPatch.h"

void StringPatch::PatchDebugStrings() {
    DWORD_PTR base = (DWORD_PTR)GetModuleHandle(NULL);
    //enable debug menu
    PatchMemory(base + 0x742128, (BYTE)0x01);
    // Patch colors first
    PatchColors(base);

    // Patch the debug menu strings
    PatchMemory(base + 0x1D4A98, "P1 Char ID     ");
    PatchMemory(base + 0x1D4A84, "P2 Char ID     ");
    PatchMemory(base + 0x1D4A70, "Ctrl Player    ");
    PatchMemory(base + 0x1D4A5C, "X Coord        ");
    PatchMemory(base + 0x1D4A48, "Y Coord        ");
    PatchMemory(base + 0x1D4A34, "Remain HP %    ");
    PatchMemory(base + 0x1D4A20, "Curr Time      ");
    PatchMemory(base + 0x1D4A0C, "Rnds Left      ");
    PatchMemory(base + 0x1D49F8, "Opp Hits       ");
    PatchMemory(base + 0x1D49E4, "Opp Dist       ");
    PatchMemory(base + 0x1D49D0, "Skill Lvl      ");
    PatchMemory(base + 0x1D49BC, "Opp CharID     ");
    PatchMemory(base + 0x1D49A8, "Sp Move        ");
    PatchMemory(base + 0x1D4994, "Opp HP %       ");
    PatchMemory(base + 0x1D4980, "Dir (-1/+1)      ");
    PatchMemory(base + 0x1D496C, "Last Guard     ");

    // Second block
    PatchMemory(base + 0x1D4958, "P1 DMG         ");
    PatchMemory(base + 0x1D4944, "P2 DMG         ");
    PatchMemory(base + 0x1D4930, "Win CharID     ");
    PatchMemory(base + 0x1D491C, "Los CharID     ");
    // Skip SeVolume, VoiceVolume, BgmVolume as they're not in your translation list
    PatchMemory(base + 0x1D4910, "Time Left      ");
    PatchMemory(base + 0x1D4904, "P1 Corr        ");
    PatchMemory(base + 0x1D48F8, "P2 Corr        ");
}

void StringPatch::PatchColors(DWORD_PTR base) {
    DWORD oldProtect;
    
    // Change memory protection for the entire color section
    if (VirtualProtect((LPVOID)(base + 0x12D0E), 0x20, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        // Change RED (0,0,255 → 40,150,240)
        *(BYTE*)(base + 0x12D23) = 0x46;  // push 200 (6A C8)
        *(BYTE*)(base + 0x12D25) = 0x50;  // push 80  (6A 50)
        *(BYTE*)(base + 0x12D27) = 0xC8;  // push 70  (6A 46)
        
        // Change BLUE (255,0,0 → 200,80,70)
        *(BYTE*)(base + 0x12D0F) = 0xF0;  // push 40  (6A 28)
        *(BYTE*)(base + 0x12D14) = 0x96;  // push 150 (6A 96)
        *(BYTE*)(base + 0x12D16) = 0x28;  // push 240 (6A F0)

        // Restore protection
        VirtualProtect((LPVOID)(base + 0x12D0E), 0x20, oldProtect, &oldProtect);
    }
}

void StringPatch::PatchMemory(uintptr_t address, const char* newString) {
    DWORD oldProtect;
    const size_t FIXED_LENGTH = 16; // All original strings seem to be 16 chars including spaces
    char paddedString[FIXED_LENGTH] = {0};
    
    // Copy string and pad with spaces
    strncpy_s(paddedString, newString, FIXED_LENGTH - 1);
    for (size_t i = strlen(paddedString); i < FIXED_LENGTH - 1; i++) {
        paddedString[i] = ' ';
    }
    paddedString[FIXED_LENGTH - 1] = '\0';

    // Change memory protection to allow writing
    if (VirtualProtect((LPVOID)address, FIXED_LENGTH, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        // Write the new padded string
        memcpy((void*)address, paddedString, FIXED_LENGTH);
        
        // Restore original memory protection
        VirtualProtect((LPVOID)address, FIXED_LENGTH, oldProtect, &oldProtect);
    }
}

// Overload for byte array patches
void StringPatch::PatchMemory(uintptr_t address, const char* bytes, size_t length) {
    DWORD oldProtect;

    // Change memory protection to allow writing
    VirtualProtect((LPVOID)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);
    
    // Write the bytes
    memcpy((void*)address, bytes, length);
    
    // Restore original memory protection
    VirtualProtect((LPVOID)address, length, oldProtect, &oldProtect);
}

void StringPatch::PatchMemory(uintptr_t address, BYTE value) {
    DWORD oldProtect;
    if (VirtualProtect((LPVOID)address, 1, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        *(BYTE*)address = value;
        VirtualProtect((LPVOID)address, 1, oldProtect, &oldProtect);
    }
}