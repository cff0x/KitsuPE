#include "main.h"
#include <stdio.h>
#include <basic_library/basic_library.h>
#include <foxylib/utils/console/console.h>


static const char WINDOW_TEXT[] = "Henlo! UwU\nI'm an ugly Win32 API window";

#define BUTTON_ID_MSGBOX 1
#define BUTTON_ID_QUIT 2

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 25
#define BUTTON_SPACING 10

HWND button_beep;
HWND button_quit;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow) {

    console_init("test gui");
    console_start();


    MSG  msg;
    WNDCLASSW wc = { 0 };
    wc.lpszClassName = L"Basic Win32 API Window";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(WHITE_BRUSH);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);


    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Basic Win32 API Forms Application",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        150, 150, 450, 150, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    RECT text_rect = { 0, 0, 0, 0 };
    RECT button_beep_rect = { 0, 0, 0, 0 }, button_quit_rect = { 0, 0, 0, 0 };

    GetClientRect(hwnd, &rect);


    switch (msg) {

    case WM_CREATE:
        button_beep = CreateWindowW(L"Button", L"Show MessageBox",
            WS_VISIBLE | WS_CHILD,
            0, 0, 0, 0, hwnd, (HMENU)BUTTON_ID_MSGBOX, NULL, NULL);

        button_quit = CreateWindowW(L"Button", L"Quit",
            WS_VISIBLE | WS_CHILD,
            0, 0, 0, 0, hwnd, (HMENU)BUTTON_ID_QUIT, NULL, NULL);



    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        HFONT hFont = CreateFont (16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
                                  OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                  DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma"));

        SelectObject(hdc, hFont);

        // text parameters
        SetTextColor(hdc, RGB(0x00, 0x00, 0x00));
        SetBkMode(hdc, TRANSPARENT);


        SendMessage(button_beep, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(button_quit, WM_SETFONT, (WPARAM)hFont, TRUE);

        // calc text size + position
        DrawText(hdc, WINDOW_TEXT, -1, &text_rect, DT_CALCRECT);

        text_rect.top = (rect.bottom - text_rect.bottom - BUTTON_HEIGHT - BUTTON_SPACING) / 2;
        text_rect.left = (rect.right - text_rect.right) / 2;
        text_rect.right = text_rect.left + text_rect.right;
        text_rect.bottom = text_rect.top + text_rect.bottom;

        // calc button size + position
        button_beep_rect.left = (rect.right / 2) - BUTTON_WIDTH - BUTTON_SPACING / 2;
        button_beep_rect.top = (rect.bottom) / 2 + BUTTON_SPACING;
        button_quit_rect.left = (rect.right / 2) + BUTTON_SPACING / 2;
        button_quit_rect.top = (rect.bottom) / 2 + BUTTON_SPACING;

        // fill window background
        FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

        // draw text
        DrawText(hdc, WINDOW_TEXT, -1, &text_rect, 0);

        // set button size + position
        SetWindowPos(button_beep, NULL, button_beep_rect.left, button_beep_rect.top, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_NOREDRAW);
        SetWindowPos(button_quit, NULL, button_quit_rect.left, button_quit_rect.top, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_NOREDRAW);

        EndPaint(hwnd, &ps);
        break;
    case WM_EXITSIZEMOVE:
        InvalidateRect(hwnd, NULL, 1);
        break;
    case WM_COMMAND:

        if (LOWORD(wParam) == BUTTON_ID_MSGBOX) {

            MessageBeep(MB_OK);
            test_function_msgbox("This message box is created from a DLL");
        }

        if (LOWORD(wParam) == BUTTON_ID_QUIT) {
            MessageBox(hwnd, test_function_retval("lol lol"), "he", MB_OK);
            PostQuitMessage(0);
        }

        break;

    case WM_DESTROY:

        PostQuitMessage(0);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}