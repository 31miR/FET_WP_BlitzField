#include "Upgrades_Menu.h"

Upgrades_Menu::Upgrades_Menu(App_State **nextStatePtr, const Player_Data &player_data, bool music_on)
{
    this->nextStatePtr = nextStatePtr;
    this->music_on = music_on;
    this->player_data = player_data;
}

void Upgrades_Menu::run(HWND hwnd)
{
}
Upgrades_Menu::~Upgrades_Menu()
{
    DeleteObject(hbmBackground);
    DeleteObject(hbmUnspentPointsMask);
    DeleteObject(hbmUnspentPoints);
    DeleteObject(hbmHealthPoints);
    DeleteObject(hbmHealthPointsMask);
    DeleteObject(hbmStaminaPointsMask);
    DeleteObject(hbmStaminaPoints);
    DeleteObject(hbmManje);
    DeleteObject(hbmManjeMask);
    DeleteObject(hbmVece);
    DeleteObject(hbmVeceMask);
    DeleteObject(hArrowBitmap);
    DeleteObject(hArrowMaskBitmap);
}

LRESULT Upgrades_Menu::winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hbmBackground = (HBITMAP)LoadImage(NULL, "resources/BACKGROUND.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmUnspentPointsMask = (HBITMAP)LoadImage(NULL, "resources/unspent_points.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmUnspentPoints = (HBITMAP)LoadImage(NULL, "resources/unspent_points_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmHealthPoints = (HBITMAP)LoadImage(NULL, "resources/health_points.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmHealthPointsMask = (HBITMAP)LoadImage(NULL, "resources/health_points_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmStaminaPointsMask = (HBITMAP)LoadImage(NULL, "resources/stamina_points.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmStaminaPoints = (HBITMAP)LoadImage(NULL, "resources/stamina_points_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmManje = (HBITMAP)LoadImage(NULL, "resources/manje.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmManjeMask = (HBITMAP)LoadImage(NULL, "resources/manje_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmVece = (HBITMAP)LoadImage(NULL, "resources/vece.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmVeceMask = (HBITMAP)LoadImage(NULL, "resources/vece_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hArrowBitmap = (HBITMAP)LoadImage(NULL, "resources/ARROW.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hArrowMaskBitmap = (HBITMAP)LoadImage(NULL, "resources/ARROW_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    case WM_SIZE:
        InvalidateRect(hwnd, 0, 0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC hdcmem = CreateCompatibleDC(hdc);
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBITMAP hbmpmem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        HBITMAP hbmpstari = (HBITMAP)SelectObject(hdcmem, hbmpmem);


        HDC hdcTMP = CreateCompatibleDC(hdc);
        BITMAP bmp;
        GetObject(hbmBackground, sizeof(BITMAP), &bmp);
        HBITMAP hbmpTMP = (HBITMAP)SelectObject(hdcTMP, hbmBackground);


        StretchBlt(hdcmem, 0, 0, rect.right, rect.bottom,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);


        POINT left_top = get_screen_from_relative(hwnd, 0.25, 0.3);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.6, 0.53);

        GetObject(hbmUnspentPoints, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, hbmUnspentPointsMask);

        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hbmUnspentPoints);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);

        left_top = get_screen_from_relative(hwnd, 0.25, 0.33);
        right_bottom = get_screen_from_relative(hwnd, 0.6, 0.46);

        GetObject(hbmStaminaPoints, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, hbmStaminaPoints);
        StretchBlt(hdcmem, left_top.x, right_bottom.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);
        SelectObject(hdcTMP, hbmStaminaPointsMask);
        StretchBlt(hdcmem, left_top.x, right_bottom.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hbmpTMP);
        left_top = get_screen_from_relative(hwnd, 0.6, 0.56);
        right_bottom = get_screen_from_relative(hwnd, 0.7, 0.66);
        GetObject(hbmManje, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, hbmManje);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hbmManjeMask);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);

        left_top = get_screen_from_relative(hwnd, 0.7, 0.56);
        right_bottom = get_screen_from_relative(hwnd, 0.8, 0.66);
        GetObject(hbmVece, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, hbmVece);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hbmVeceMask);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);

        left_top = get_screen_from_relative(hwnd, 0.25, 0.56);
        right_bottom = get_screen_from_relative(hwnd, 0.6, 0.69);
        GetObject(hbmHealthPoints, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, hbmHealthPoints);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hbmHealthPointsMask);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);
        left_top = get_screen_from_relative(hwnd, 0.6, 0.47);
        right_bottom = get_screen_from_relative(hwnd, 0.7, 0.57);
        GetObject(hbmManje, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, hbmManje);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hbmManjeMask);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);

        left_top = get_screen_from_relative(hwnd, 0.7, 0.47);
        right_bottom = get_screen_from_relative(hwnd, 0.8, 0.57);
        GetObject(hbmVece, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, hbmVece);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hbmVeceMask);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);

        GetObject(hArrowBitmap, sizeof(BITMAP), &bmp);
        left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
        right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
        SelectObject(hdcTMP, hArrowBitmap);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, hArrowMaskBitmap);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);

        SelectObject(hdcTMP, hbmpTMP);

        DeleteDC(hdcTMP);

        int fontSize = rect.bottom / 16;
        HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                 ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                                 ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");

        hFont = (HFONT)SelectObject(hdcmem, hFont);
        SetBkMode(hdcmem, TRANSPARENT);
        SetTextColor(hdcmem, RGB(255, 255, 255));

        left_top = get_screen_from_relative(hwnd, 0.69, 0.4);
        RECT textRect = {left_top.x, left_top.y, left_top.x + fontSize * 3, right_bottom.y + fontSize};
        DrawText(hdcmem, std::to_string(player_data.unspent_upgrades).c_str(), -1, &textRect, DT_SINGLELINE);

        left_top = get_screen_from_relative(hwnd, 0.69, 0.5);
        textRect = {left_top.x, left_top.y, left_top.x + fontSize * 3, right_bottom.y + fontSize};
        DrawText(hdcmem, std::to_string(player_data.stamina_upgrades).c_str(), -1, &textRect, DT_SINGLELINE);

        left_top = get_screen_from_relative(hwnd, 0.69, 0.6);
        textRect = {left_top.x, left_top.y, left_top.x + fontSize * 3, right_bottom.y + fontSize};
        DrawText(hdcmem, std::to_string(player_data.health_upgrades).c_str(), -1, &textRect, DT_SINGLELINE);

        hFont = (HFONT)SelectObject(hdcmem, hFont);

        DeleteObject(hFont);


        BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcmem, 0, 0, SRCCOPY);

        SelectObject(hdcmem, hbmpstari);
        DeleteDC(hdcmem);
        DeleteObject(hbmpmem);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
        RECT arrowRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};

        left_top = get_screen_from_relative(hwnd, 0.628827, 0.506239);
        right_bottom = get_screen_from_relative(hwnd, 0.663265, 0.547237);
        RECT decrementStamina = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.729592, 0.511586);
        right_bottom = get_screen_from_relative(hwnd, 0.757653, 0.543672);
        RECT incrementStamina = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.632653, 0.604278);
        right_bottom = get_screen_from_relative(hwnd, 0.663265, 0.638146);
        RECT decrementHealth = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.732143, 0.602496);
        right_bottom = get_screen_from_relative(hwnd, 0.755102, 0.632799);
        RECT incrementHealth = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};

        if (PtInRect(&arrowRect, pt))
        {
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            *nextStatePtr = new Main_Menu(nextStatePtr, (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), player_data, music_on);
        }
        if (PtInRect(&decrementHealth, pt))
        {
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (player_data.health_upgrades > 0)
            {
                player_data.health_upgrades--;
                player_data.unspent_upgrades++;
                DB_Helper::update_profile_in_DB(player_data);
            }
        }
        if (PtInRect(&incrementHealth, pt))
        {
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (player_data.unspent_upgrades > 0)
            {
                player_data.health_upgrades++;
                player_data.unspent_upgrades--;
                DB_Helper::update_profile_in_DB(player_data);
            }
        }
        if (PtInRect(&decrementStamina, pt))
        {
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (player_data.stamina_upgrades > 0)
            {
                player_data.stamina_upgrades--;
                player_data.unspent_upgrades++;
                DB_Helper::update_profile_in_DB(player_data);
            }
        }
        if (PtInRect(&incrementStamina, pt))
        {
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (player_data.unspent_upgrades > 0)
            {
                player_data.stamina_upgrades++;
                player_data.unspent_upgrades--;
                DB_Helper::update_profile_in_DB(player_data);
            }
        }
        InvalidateRect(hwnd, 0, 0);
        break;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
