#ifndef UPGRADES_MENU_H
#define UPGRADES_MENU_H
#include "App_State.h"
#include "Main_Menu.h"

class Upgrades_Menu : public App_State
{
public:
    Upgrades_Menu(App_State **nextStatePtr, const Player_Data &player_data, bool music_on = true);
    ~Upgrades_Menu();
    void run(HWND hwnd);
    LRESULT CALLBACK winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    HBITMAP hbmBackground;
    HBITMAP hbmUnspentPoints, hbmUnspentPointsMask;
    HBITMAP hbmHealthPoints, hbmHealthPointsMask;
    HBITMAP hbmStaminaPoints, hbmStaminaPointsMask;
    HBITMAP hArrowBitmap;
    HBITMAP hArrowMaskBitmap;
    HBITMAP hbmManje, hbmManjeMask;
    HBITMAP hbmVece, hbmVeceMask;

private:
    App_State **nextStatePtr;
    Player_Data player_data;
    bool music_on;
};

#endif // UPGRADES_MENU_H
