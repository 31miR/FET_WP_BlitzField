#include "Main_Menu.h"
#include "App_State.h"
#include "Settings_Menu.h"
#include "Profil_Menu.h"
#include <windows.h>
#include <winuser.h>
#include "Level_01.h"

Main_Menu::Main_Menu(App_State **next_state, HINSTANCE hInstance, const Player_Data &player_data, bool music_on)
{
    this->music_on = music_on;
    this->nextStatePtr = next_state;
    this->hInstance = hInstance;
    hbmNewGame = hbmNewGameMask = NULL;
    hbmContinue = hbmContinueMask = NULL;
    hbmUpgrades = hbmUpgradesMask = NULL;
    hbmSettings = hbmSettingsMask = NULL;
    hbmArrow = hbmArrowMask = NULL;
    this->player_data = player_data;
}

void Main_Menu::run(HWND hwnd)
{
}

Main_Menu::~Main_Menu()
{
    if (hbmNewGame)
        DeleteObject(hbmNewGame);
    if (hbmNewGameMask)
        DeleteObject(hbmNewGameMask);
    if (hbmContinue)
        DeleteObject(hbmContinue);
    if (hbmContinueMask)
        DeleteObject(hbmContinueMask);
    if (hbmUpgrades)
        DeleteObject(hbmUpgrades);
    if (hbmUpgradesMask)
        DeleteObject(hbmUpgradesMask);
    if (hbmSettings)
        DeleteObject(hbmSettings);
    if (hbmSettingsMask)
        DeleteObject(hbmSettingsMask);
    if (hbmArrow)
        DeleteObject(hbmArrow);
    if (hbmArrowMask)
        DeleteObject(hbmArrowMask);
    if (hbmNewGameHover)
        DeleteObject(hbmNewGameHover);
    if (hbmNewGameHoverMask)
        DeleteObject(hbmNewGameHoverMask);
    if (hbmContinueHover)
        DeleteObject(hbmContinueHover);
    if (hbmContinueHoverMask)
        DeleteObject(hbmContinueHoverMask);
    if (hbmUpgradesHover)
        DeleteObject(hbmUpgradesHover);
    if (hbmUpgradesHoverMask)
        DeleteObject(hbmUpgradesHoverMask);
    if (hbmSettingsHover)
        DeleteObject(hbmSettingsHover);
    if (hbmSettingsHoverMask)
        DeleteObject(hbmSettingsHoverMask);
    if (hbmArrowHover)
        DeleteObject(hbmArrowHover);
    if (hbmArrowHoverMask)
        DeleteObject(hbmArrowHoverMask);
    if (hCursorCustom)
        DeleteObject(hCursorCustom);
}

LRESULT Main_Menu::winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        BITMAP bm;
    case WM_CREATE:
    {
        hbmBackground = (HBITMAP)LoadImage(NULL, "resources/BACKGROUND.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmNewGame = (HBITMAP)LoadImage(NULL, "resources/NEWGAME.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmNewGameMask = (HBITMAP)LoadImage(NULL, "resources/NEWGAME_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmContinue = (HBITMAP)LoadImage(NULL, "resources/CONTINUE_GAME.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmContinueMask = (HBITMAP)LoadImage(NULL, "resources/CONTINUE_GAME_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmUpgrades = (HBITMAP)LoadImage(NULL, "resources/UPGRADES.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmUpgradesMask = (HBITMAP)LoadImage(NULL, "resources/UPGRADES_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmSettings = (HBITMAP)LoadImage(NULL, "resources/SETTINGS.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmSettingsMask = (HBITMAP)LoadImage(NULL, "resources/SETTINGS_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmArrow = (HBITMAP)LoadImage(NULL, "resources/ARROW.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmArrowMask = (HBITMAP)LoadImage(NULL, "resources/ARROW_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmNewGameHover = (HBITMAP)LoadImage(NULL, "resources/NEWGAME_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmNewGameHoverMask = (HBITMAP)LoadImage(NULL, "resources/NEWGAME_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmContinueHover = (HBITMAP)LoadImage(NULL, "resources/CONTINUE_GAME_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmContinueHoverMask = (HBITMAP)LoadImage(NULL, "resources/CONTINUE_GAME_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmUpgradesHover = (HBITMAP)LoadImage(NULL, "resources/UPGRADES_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmUpgradesHoverMask = (HBITMAP)LoadImage(NULL, "resources/UPGRADES_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmSettingsHover = (HBITMAP)LoadImage(NULL, "resources/SETTINGS_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmSettingsHoverMask = (HBITMAP)LoadImage(NULL, "resources/SETTINGS_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmArrowHover = (HBITMAP)LoadImage(NULL, "resources/ARROW_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmArrowHoverMask = (HBITMAP)LoadImage(NULL, "resources/ARROW_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hCursorCustom = (HCURSOR)LoadImage(NULL, "resources/cursor.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
        SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursorCustom);

        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdcOriginal = BeginPaint(hwnd, &ps);

        HDC hdc = CreateCompatibleDC(hdcOriginal);
        HBITMAP hbmBUFFER = CreateCompatibleBitmap(hdcOriginal, ps.rcPaint.right, ps.rcPaint.bottom);
        HBITMAP hbmBUFFEROLD = (HBITMAP)SelectObject(hdc, hbmBUFFER);

        HDC hdcMem = CreateCompatibleDC(hdc);
        HDC hdcMask = CreateCompatibleDC(hdc);

        if (hbmBackground)
        {
            BITMAP bmpBackground;
            GetObject(hbmBackground, sizeof(BITMAP), &bmpBackground);
            RECT rect;
            GetClientRect(hwnd, &rect);
            HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hbmBackground);
            StretchBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcMem, 0, 0, bmpBackground.bmWidth, bmpBackground.bmHeight, SRCCOPY);
            SelectObject(hdcMem, hOldBitmap);
        }

        if (hoveringNewGame && hbmNewGameHover && hbmNewGameHoverMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmNewGameHover);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmNewGameHoverMask);
            GetObject(hbmNewGameHover, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.39);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.39 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        else if (hbmNewGame && hbmNewGameMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmNewGame);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmNewGameMask);
            GetObject(hbmNewGame, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.39);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.39 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }

        if (hoveringContinue && hbmContinueHover && hbmContinueHoverMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmContinueHover);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmContinueHoverMask);
            GetObject(hbmContinueHover, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.39);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.39 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        else if (hbmContinue && hbmContinueMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmContinue);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmContinueMask);
            GetObject(hbmContinue, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.39);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.39 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }

        if (hoveringUpgrades && hbmUpgradesHover && hbmUpgradesHoverMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmUpgradesHover);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmUpgradesHoverMask);
            GetObject(hbmUpgradesHover, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.53);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.53 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        else if (hbmUpgrades && hbmUpgradesMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmUpgrades);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmUpgradesMask);
            GetObject(hbmUpgrades, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.53);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.53 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        if (hoveringSettings && hbmSettingsHover && hbmSettingsHoverMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmSettingsHover);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmSettingsHoverMask);
            GetObject(hbmSettingsHover, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.53);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.53 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        else if (hbmSettings && hbmSettingsMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmSettings);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmSettingsMask);
            GetObject(hbmSettings, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.53);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.53 + 0.2);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        if (hoveringArrow && hbmArrowHover && hbmArrowHoverMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmArrowHover);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmArrowHoverMask);
            GetObject(hbmArrowHover, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        else if (hbmArrow && hbmArrowMask)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmArrow);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmArrowMask);
            GetObject(hbmArrow, sizeof(BITMAP), &bm);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }

        DeleteDC(hdcMem);
        DeleteDC(hdcMask);

        BitBlt(hdcOriginal, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, hdc, 0, 0, SRCCOPY);

        SelectObject(hdc, hbmBUFFEROLD);
        DeleteObject(hbmBUFFER);
        DeleteDC(hdc);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_SIZE:
        InvalidateRect(hwnd, 0, 0);
        break;
    case WM_MOUSEMOVE:
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        bool prevHoverNewGame = hoveringNewGame;
        bool prevHoverContinue = hoveringContinue;
        bool prevHoverUpgrades = hoveringUpgrades;
        bool prevHoverSettings = hoveringSettings;
        bool prevHoverArrow = hoveringArrow;

        POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.44);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.44 + 0.08);
        RECT newGameRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.51, 0.44);
        right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.44 + 0.08);
        RECT continueRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.235, 0.58);
        right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.58 + 0.08);
        RECT upgradesRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.51, 0.58);
        right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.58 + 0.08);
        RECT settingsRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
        right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
        RECT arrowRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};

        hoveringNewGame = PtInRect(&newGameRect, pt);
        hoveringContinue = PtInRect(&continueRect, pt);
        hoveringUpgrades = PtInRect(&upgradesRect, pt);
        hoveringSettings = PtInRect(&settingsRect, pt);
        hoveringArrow = PtInRect(&arrowRect, pt);

        if (hoveringNewGame != prevHoverNewGame ||
            hoveringContinue != prevHoverContinue ||
            hoveringUpgrades != prevHoverUpgrades ||
            hoveringSettings != prevHoverSettings || hoveringArrow != prevHoverArrow)
        {
            InvalidateRect(hwnd, NULL, NULL);
        }
        break;
    }

    case WM_LBUTTONDOWN:
    {
        POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.44);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.44 + 0.08);
        RECT newGameRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.51, 0.44);
        right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.44 + 0.08);
        RECT continueRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.235, 0.58);
        right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.275, 0.58 + 0.08);
        RECT upgradesRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.51, 0.58);
        right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.58 + 0.08);
        RECT settingsRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
        right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
        RECT arrowRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (PtInRect(&arrowRect, pt))
        {
            *nextStatePtr = new Profil_Menu(nextStatePtr, hInstance, music_on);
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        if (PtInRect(&settingsRect, pt))
        {
            *nextStatePtr = new Settings_Menu(nextStatePtr, hInstance, player_data, music_on);
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        if (PtInRect(&upgradesRect, pt))
        {
            *nextStatePtr = new Upgrades_Menu(nextStatePtr, player_data, music_on);
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        if (PtInRect(&newGameRect, pt))
        {
            mciSendString("stop mydev", NULL, 0, NULL);
            mciSendString("close mydev", NULL, 0, NULL);
            player_data.last_level_played = -1;
            DB_Helper::update_profile_in_DB(player_data);
            *nextStatePtr = new Level_01(nextStatePtr, player_data, player_data.last_level_played + 1, music_on);
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        if (PtInRect(&continueRect, pt))
        {
            if (player_data.last_level_played != 3)
            {
                mciSendString("stop mydev", NULL, 0, NULL);
                mciSendString("close mydev", NULL, 0, NULL);
                *nextStatePtr = new Level_01(nextStatePtr, player_data, player_data.last_level_played + 1, music_on);
                PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
        }

        break;
    }

    case WM_DESTROY:
    {

        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
