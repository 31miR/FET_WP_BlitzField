#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <windows.h>
#include "App_State.h"

class Settings_Menu : public App_State
{
public:
    Settings_Menu(App_State **next_state, HINSTANCE, const Player_Data &player_data, bool music_on = true);
    ~Settings_Menu();
    void run(HWND hwnd);
    LRESULT CALLBACK winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    App_State **nextStatePtr;
    HINSTANCE hInstance;
    HWND hwnd;
    HBITMAP hMusicBitmap, hMusicMaskBitmap;
    int onCounter, offCounter, onCounter1, offCounter1;
    bool hoveringArrow = false;
    HCURSOR hCursorCustom;
    HBITMAP hBackgroundBitmap = NULL;
    HBITMAP hOnBitmap, hOnMaskBitmap, hOffBitmap, hOffMaskBitmap;
    HBITMAP hArrowBitmap, hArrowMaskBitmap;
    HBITMAP hONHoverBitmap, hONHoverMaskBitmap, hOFFHoverBitmap, hOFFHoverMaskBitmap, hArrowHoverBitmap, hArrowHoverMaskBitmap;
    HDC hdcMem, hdcMask;
    bool isHoverOn = false;
    bool isHoverOn1 = false;
    bool isHoverArrow = false;
    bool music_on;
    Player_Data player_data;
};

#endif
