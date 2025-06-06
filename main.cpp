#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>

#include "App_State.h"
#include "Profil_Menu.h"
#include "Main_Menu.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DestroyChildProc(HWND hwndChild, LPARAM lParam)
{
    DestroyWindow(hwndChild);
    return TRUE;
}

App_State *current_state;
App_State *next_state;

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    HWND hwnd;        /* This is the handle for our window */
    MSG messages;     /* Here messages to the application are saved */
    WNDCLASSEX wincl; /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure; /* This function is called by windows */
    wincl.style = CS_DBLCLKS;            /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL; /* No menu */
    wincl.cbClsExtra = 0;      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                                       /* Extended possibilites for variation */
        szClassName,                             /* Classname */
        _T("BlitzField"), /* Title Text */
        WS_OVERLAPPEDWINDOW,                     /* default window */
        CW_USEDEFAULT,                           /* Windows decides the position */
        CW_USEDEFAULT,                           /* where the window ends up on the screen */
        800,                                     /* The programs width */
        600,                                     /* and height in pixels */
        HWND_DESKTOP,                            /* The window is a child-window to desktop */
        NULL,                                    /* No menu */
        hThisInstance,                           /* Program Instance handler */
        NULL                                     /* No Window Creation data */
    );

    ShowWindow(hwnd, nCmdShow);

    current_state = new Profil_Menu(&next_state, hThisInstance);

    // This way, we make each new state act as if the window was just created (so we can potentially run WM_CREATE inside App_State::winproc)
    CREATESTRUCT cs = {};
    SendMessage(hwnd, WM_CREATE, 0, (LPARAM)&cs);

    while (true)
    {
        if (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
        {
            if (messages.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
        if (current_state)
            current_state->run(hwnd);
        if (next_state)
        {
            EnumChildWindows(hwnd, DestroyChildProc, 0); // in case there are child windows such as buttons, destroy them
            delete current_state;
            current_state = next_state;
            next_state = 0;
            SendMessage(hwnd, WM_CREATE, 0, (LPARAM)&cs);
            InvalidateRect(hwnd, 0, 1);
        }
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        delete current_state;
        current_state = 0;
        PostQuitMessage(0);
        return 0;
    }
    if (current_state)
        return current_state->winproc(hwnd, message, wParam, lParam);

    return DefWindowProc(hwnd, message, wParam, lParam);
}
