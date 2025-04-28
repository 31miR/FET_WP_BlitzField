#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "App_State.h"
#include "includes.h"
#include "Upgrades_Menu.h"
#include <windows.h>

class Main_Menu : public App_State
{
private:
    App_State **nextStatePtr;
    HINSTANCE hInstance;
    HBITMAP hbmNewGame, hbmNewGameMask, hbmBackground;
    ;
    HBITMAP hbmContinue, hbmContinueMask;
    HBITMAP hbmUpgrades, hbmUpgradesMask;
    HBITMAP hbmSettings, hbmSettingsMask;
    HBITMAP hbmArrow, hbmArrowMask;
    HBITMAP hbmNewGameHover, hbmNewGameHoverMask;
    HBITMAP hbmContinueHover, hbmContinueHoverMask;
    HBITMAP hbmUpgradesHover, hbmUpgradesHoverMask;
    HBITMAP hbmSettingsHover, hbmSettingsHoverMask;
    HBITMAP hbmArrowHover, hbmArrowHoverMask;
    bool hoveringNewGame = false;
    bool hoveringContinue = false;
    bool hoveringUpgrades = false;
    bool hoveringSettings = false;
    bool hoveringArrow = false;
    bool music_on;
    HCURSOR hCursorCustom;
    Player_Data player_data;

public:
    Main_Menu(App_State **next_state, HINSTANCE, const Player_Data &player_data, bool music_on = true);
    ~Main_Menu();
    void run(HWND hwnd);
    LRESULT CALLBACK winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif // MAIN_MENU_H
