#ifndef APP_STATE_H
#define APP_STATE_H

#include <tchar.h>
#include <windows.h>

class App_State
{
public:
    virtual void run(HWND hwnd) = 0;
    virtual LRESULT winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

#endif // APP_STATE_H
