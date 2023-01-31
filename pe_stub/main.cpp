#pragma code_seg(".stub")
#pragma comment(linker, "/MERGE:.rdata=.stub")
#pragma comment(linker, "/MERGE:.pdata=.stub")

#include <lazy_importer.hpp>
#include <foxywinapi.hpp>


HWND open_console(const char* title)
{
    LI_FN(AllocConsole)();
    LI_FN(SetConsoleTitleA)(title);
    HANDLE in_handle, out_handle, err_handle;
    in_handle  = LI_FN(CreateFileA)("CONIN$", (GENERIC_READ | GENERIC_WRITE), 0,
        nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    out_handle = LI_FN(CreateFileA)("CONOUT$", GENERIC_WRITE, 0,
        nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    err_handle = LI_FN(CreateFileA)("CONOUT$", GENERIC_WRITE, 0,
        nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    LI_FN(SetStdHandle)(STD_INPUT_HANDLE, in_handle);
    LI_FN(SetStdHandle)(STD_OUTPUT_HANDLE, out_handle);
    LI_FN(SetStdHandle)(STD_ERROR_HANDLE, err_handle);

    LI_FN(SetConsoleMode)(in_handle, ENABLE_WINDOW_INPUT);

    return LI_FN(GetConsoleWindow)();
}

void close_console()
{
    LI_FN(FreeConsole)();

    LI_FN(CloseHandle)(LI_FN(GetStdHandle)(STD_INPUT_HANDLE));
    LI_FN(CloseHandle)(LI_FN(GetStdHandle)(STD_OUTPUT_HANDLE));
    LI_FN(CloseHandle)(LI_FN(GetStdHandle)(STD_ERROR_HANDLE));
}


void start()
{
    auto user32 = LI_FN(LoadLibraryA)("user32.dll");
    open_console("PE loader");

    printf("[i] PE loader stub is starting!\n");

    char test_buf[1024] = "hamlo";
    printf("[+] test_buf: %s\n", test_buf);

    while(1)  {
        LI_FN(Sleep)(10);
    };
}
