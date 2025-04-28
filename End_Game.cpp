#include "End_Game.h"

End_Game::End_Game(App_State **p_next_state, const Player_Data &player_data, int level_index, int enemy_count, const POINT_DECIMAL &initial_player_position, bool music_on, bool success)
    : p_next_state{p_next_state}, music_on{music_on}, player_data{player_data}, level_index{level_index}, enemy_count{enemy_count}, initial_player_position{initial_player_position}, success{success}
{
    if (success)
    {
        title = (HBITMAP)LoadImage(NULL, "resources/end_game_success_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        title_mask = (HBITMAP)LoadImage(NULL, "resources/end_game_success.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        level = (HBITMAP)LoadImage(NULL, "resources/next_level_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        level_mask = (HBITMAP)LoadImage(NULL, "resources/next_level.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        main = (HBITMAP)LoadImage(NULL, "resources/main_menu_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        main_mask = (HBITMAP)LoadImage(NULL, "resources/main_menu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    else
    {
        title = (HBITMAP)LoadImage(NULL, "resources/end_game_fail_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        title_mask = (HBITMAP)LoadImage(NULL, "resources/end_game_fail.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        level = (HBITMAP)LoadImage(NULL, "resources/restart_level_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        level_mask = (HBITMAP)LoadImage(NULL, "resources/restart_level.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        main = (HBITMAP)LoadImage(NULL, "resources/main_menu_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        main_mask = (HBITMAP)LoadImage(NULL, "resources/main_menu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }

    if (success)
    {
        this->player_data.last_level_played++;
        if (this->player_data.last_level_played == this->player_data.levels_finished_count)
        {
            this->player_data.levels_finished_count++;
            this->player_data.unspent_upgrades++;
        }
        DB_Helper::update_profile_in_DB(this->player_data);
    }
}

End_Game::~End_Game()
{
    DeleteObject(title);
    DeleteObject(title_mask);
    DeleteObject(level);
    DeleteObject(level_mask);
    DeleteObject(main);
    DeleteObject(main_mask);
}

void End_Game::run(HWND hwnd)
{
    // EMPTY
}

void End_Game::write_out_options(HWND hwnd, HDC hdc)
{
    // TODO
}

LRESULT End_Game::winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
        InvalidateRect(hwnd, 0, 0);
        break;
    case WM_KEYDOWN:
        if (wParam == VK_SPACE && level_index < 3)
        {
            *p_next_state = new Level_01(p_next_state, player_data, level_index + (success ? 1 : 0), music_on);
        }
        if (wParam == VK_RETURN)
        {
            if (music_on)
            {
                mciSendString("open resources/muzika.wav type waveaudio alias mydev", NULL, 0, NULL);
                mciSendString("play mydev notify", NULL, 0, NULL);
            }
            *p_next_state = new Main_Menu(p_next_state, (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), player_data, music_on);
        }
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

        POINT left_top = get_screen_from_relative(hwnd, 0.3, 0.2);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.7, 0.5);

        BITMAP bmp;
        HDC hdcTMP = CreateCompatibleDC(hdc);


        GetObject(title, sizeof(BITMAP), &bmp);
        HBITMAP hbmpTMP = (HBITMAP)SelectObject(hdcTMP, title_mask);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, title);
        StretchBlt(hdcmem, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);


        if (level_index < 3)
        {
            left_top = get_screen_from_relative(hwnd, 0.55, 0.15);
            right_bottom = get_screen_from_relative(hwnd, 0.95, 0.39);
            GetObject(level, sizeof(BITMAP), &bmp);
            SelectObject(hdcTMP, level_mask);
            StretchBlt(hdcmem, left_top.x, right_bottom.y, right_bottom.x - left_top.x, bmp.bmHeight,
                       hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
            SelectObject(hdcTMP, level);
            StretchBlt(hdcmem, left_top.x, right_bottom.y, right_bottom.x - left_top.x, bmp.bmHeight,
                       hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);
        }


        left_top = get_screen_from_relative(hwnd, 0.05, 0.15);
        right_bottom = get_screen_from_relative(hwnd, 0.45, 0.39);
        GetObject(main, sizeof(BITMAP), &bmp);
        SelectObject(hdcTMP, main_mask);
        StretchBlt(hdcmem, left_top.x, right_bottom.y, right_bottom.x - left_top.x, bmp.bmHeight,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
        SelectObject(hdcTMP, main);
        StretchBlt(hdcmem, left_top.x, right_bottom.y, right_bottom.x - left_top.x, bmp.bmHeight,
                   hdcTMP, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);

        SelectObject(hdcTMP, hbmpTMP);
        DeleteDC(hdcTMP);

        BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcmem, 0, 0, SRCCOPY);

        SelectObject(hdcmem, hbmpstari);
        DeleteDC(hdcmem);
        DeleteObject(hbmpmem);
        EndPaint(hwnd, &ps);
        break;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
