#ifndef APP_STATE_H
#define APP_STATE_H

#include "includes.h"

class App_State
{
public:
    virtual void run(HWND hwnd) = 0;
    virtual LRESULT winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    virtual ~App_State() {}
};

#endif // APP_STATE_H
