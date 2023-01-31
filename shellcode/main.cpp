#include <foxywinapi.hpp>

__attribute__((unused)) __attribute__((section("base")))
void shellcode()
{
    auto user32 = LI_FN(LoadLibraryA)("user32.dll");
    LI_FN(MessageBoxA)(nullptr, "This message box got called from our shellcode!", "Yay! :3", MB_OK);
}
