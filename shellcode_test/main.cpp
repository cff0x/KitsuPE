#include <Windows.h>
#include <iostream>

unsigned char shellcode[436] = {
    0x56, 0x57, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x65, 0x48, 0x8B, 0x04, 0x25, 0x60, 0x00, 0x00, 0x00,
    0x4C, 0x8B, 0x40, 0x18, 0x49, 0x83, 0xC0, 0x10, 0x4D, 0x8B, 0x00, 0x49, 0x8B, 0x40, 0x30, 0x48,
    0x63, 0x48, 0x3C, 0x44, 0x8B, 0x8C, 0x08, 0x88, 0x00, 0x00, 0x00, 0x4D, 0x85, 0xC9, 0x74, 0xE8,
    0x42, 0x8B, 0x54, 0x08, 0x18, 0x48, 0x85, 0xD2, 0x74, 0xDE, 0x46, 0x8B, 0x5C, 0x08, 0x20, 0x49,
    0x01, 0xC3, 0x4C, 0x8D, 0x50, 0x01, 0x41, 0x8B, 0x4C, 0x93, 0xFC, 0x48, 0xFF, 0xCA, 0x8A, 0x1C,
    0x08, 0x84, 0xDB, 0x74, 0x24, 0x4C, 0x01, 0xD1, 0xBE, 0x66, 0xFA, 0xAF, 0x7F, 0x0F, 0xBE, 0xFB,
    0x31, 0xF7, 0x69, 0xF7, 0x93, 0x01, 0x00, 0x01, 0x8A, 0x19, 0x48, 0xFF, 0xC1, 0x84, 0xDB, 0x75,
    0xEC, 0x81, 0xFE, 0x08, 0x0B, 0xEA, 0xE9, 0x74, 0x07, 0x48, 0x85, 0xD2, 0x75, 0xC8, 0xEB, 0x98,
    0x42, 0x8B, 0x4C, 0x08, 0x1C, 0x42, 0x8B, 0x5C, 0x08, 0x24, 0x48, 0x01, 0xC1, 0x48, 0x01, 0xC3,
    0x89, 0xD2, 0x0F, 0xB7, 0x14, 0x53, 0x8B, 0x14, 0x91, 0x48, 0x01, 0xC2, 0x48, 0x8D, 0x0D, 0xC1,
    0x00, 0x00, 0x00, 0xFF, 0xD2, 0x65, 0x48, 0x8B, 0x04, 0x25, 0x60, 0x00, 0x00, 0x00, 0x4C, 0x8B,
    0x40, 0x18, 0x49, 0x83, 0xC0, 0x10, 0x4D, 0x8B, 0x00, 0x49, 0x8B, 0x40, 0x30, 0x48, 0x63, 0x48,
    0x3C, 0x44, 0x8B, 0x8C, 0x08, 0x88, 0x00, 0x00, 0x00, 0x4D, 0x85, 0xC9, 0x74, 0xE8, 0x42, 0x8B,
    0x54, 0x08, 0x18, 0x48, 0x85, 0xD2, 0x74, 0xDE, 0x46, 0x8B, 0x5C, 0x08, 0x20, 0x49, 0x01, 0xC3,
    0x4C, 0x8D, 0x50, 0x01, 0x41, 0x8B, 0x4C, 0x93, 0xFC, 0x48, 0xFF, 0xCA, 0x8A, 0x1C, 0x08, 0x84,
    0xDB, 0x74, 0x24, 0x4C, 0x01, 0xD1, 0xBE, 0xEC, 0xCE, 0x42, 0xF1, 0x0F, 0xBE, 0xFB, 0x31, 0xF7,
    0x69, 0xF7, 0x93, 0x01, 0x00, 0x01, 0x8A, 0x19, 0x48, 0xFF, 0xC1, 0x84, 0xDB, 0x75, 0xEC, 0x81,
    0xFE, 0xE7, 0x73, 0xFB, 0x7C, 0x74, 0x07, 0x48, 0x85, 0xD2, 0x75, 0xC8, 0xEB, 0x98, 0x42, 0x8B,
    0x4C, 0x08, 0x1C, 0x42, 0x8B, 0x5C, 0x08, 0x24, 0x48, 0x01, 0xC1, 0x48, 0x01, 0xC3, 0x89, 0xD2,
    0x0F, 0xB7, 0x14, 0x53, 0x44, 0x8B, 0x14, 0x91, 0x49, 0x01, 0xC2, 0x48, 0x8D, 0x15, 0x35, 0x00,
    0x00, 0x00, 0x4C, 0x8D, 0x05, 0x26, 0x00, 0x00, 0x00, 0x31, 0xC9, 0x45, 0x31, 0xC9, 0x48, 0x83,
    0xC4, 0x20, 0x5B, 0x5F, 0x5E, 0x49, 0xFF, 0xE2, 0x00, 0x10, 0x00, 0x00, 0x58, 0x11, 0x00, 0x00,
    0xA8, 0x11, 0x00, 0x00, 0x75, 0x73, 0x65, 0x72, 0x33, 0x32, 0x2E, 0x64, 0x6C, 0x6C, 0x00, 0x59,
    0x61, 0x79, 0x21, 0x20, 0x3A, 0x33, 0x00, 0x54, 0x68, 0x69, 0x73, 0x20, 0x6D, 0x65, 0x73, 0x73,
    0x61, 0x67, 0x65, 0x20, 0x62, 0x6F, 0x78, 0x20, 0x67, 0x6F, 0x74, 0x20, 0x63, 0x61, 0x6C, 0x6C,
    0x65, 0x64, 0x20, 0x66, 0x72, 0x6F, 0x6D, 0x20, 0x6F, 0x75, 0x72, 0x20, 0x73, 0x68, 0x65, 0x6C,
    0x6C, 0x63, 0x6F, 0x64, 0x65, 0x21, 0x00, 0xCC, 0x01, 0x07, 0x04, 0x00, 0x07, 0x32, 0x03, 0x30,
    0x02, 0x70, 0x01, 0x60
};

int main(int argc, char** argv)
{
    printf("[i] Trying to load shellcode...\n");

    void* exec = VirtualAlloc(nullptr, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcode, sizeof(shellcode));
    ((void(*)())exec)();
}
