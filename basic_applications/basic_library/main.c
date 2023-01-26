#include "main.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, "Basic Library -> DllMain called! (DLL_PROCESS_ATTACH)", "Basic Library", MB_OK);
        break;

    case DLL_THREAD_ATTACH:
        //MessageBox(NULL, "Basic Library -> DllMain called! (DLL_THREAD_ATTACH)", "Basic Library", MB_OK);
        break;

    case DLL_THREAD_DETACH:
        //MessageBox(NULL, "Basic Library -> DllMain called! (DLL_THREAD_DETACH)", "Basic Library", MB_OK);
        break;

    case DLL_PROCESS_DETACH:
        MessageBox(NULL, "Basic Library -> DllMain called! (DLL_PROCESS_DETACH)", "Basic Library", MB_OK);
        break;
    }
    return TRUE;
}

void __cdecl test_function_msgbox(const char* text)
{
    MessageBox(NULL, text, "Basic Library (test_function_msgbox)", MB_OK);
}

char* __cdecl test_function_retval(char* text)
{
    char* return_value = "\0";
    sprintf(return_value, "Basic Library -> test_function_retval text parameter: %s", text);
    return return_value;
}
