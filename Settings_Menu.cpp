#include "Settings_Menu.h"
#include "Main_Menu.h"
#include <windows.h>

Settings_Menu::Settings_Menu(App_State **next_state, HINSTANCE hInstance, const Player_Data &player_data, bool music_on)
{
    this->music_on = music_on;
    this->nextStatePtr = next_state;
    this->hInstance = hInstance;
    this->onCounter = 0;
    this->offCounter = 0;
    this->player_data = player_data;
}

void Settings_Menu::run(HWND hwnd) {}

HBITMAP LoadBitmapFromFile(const char *filename)
{
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    return hBitmap;
}
Settings_Menu::~Settings_Menu()
{
    if (hBackgroundBitmap)
        DeleteObject(hBackgroundBitmap);
    if (hMusicBitmap)
        DeleteObject(hMusicBitmap);
    if (hMusicMaskBitmap)
        DeleteObject(hMusicMaskBitmap);
    if (hOnBitmap)
        DeleteObject(hOnBitmap);
    if (hOnMaskBitmap)
        DeleteObject(hOnMaskBitmap);
    if (hOffBitmap)
        DeleteObject(hOffBitmap);
    if (hOffMaskBitmap)
        DeleteObject(hOffMaskBitmap);
    if (hArrowBitmap)
        DeleteObject(hArrowBitmap);
    if (hArrowMaskBitmap)
        DeleteObject(hArrowMaskBitmap);
    if (hONHoverBitmap)
        DeleteObject(hONHoverBitmap);
    if (hONHoverMaskBitmap)
        DeleteObject(hONHoverMaskBitmap);
    if (hOFFHoverBitmap)
        DeleteObject(hOFFHoverBitmap);
    if (hOFFHoverMaskBitmap)
        DeleteObject(hOFFHoverMaskBitmap);
    if (hArrowHoverBitmap)
        DeleteObject(hArrowHoverBitmap);
    if (hArrowHoverMaskBitmap)
        DeleteObject(hArrowHoverMaskBitmap);
    if (hCursorCustom)
        DeleteObject(hCursorCustom);
}

LRESULT CALLBACK Settings_Menu::winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static HINSTANCE hInstance = GetModuleHandle(NULL);
    static RECT onRect1 = {450, 280, 450 + 150, 280 + 50};
    static RECT arrowRect = {150, 380, 150 + 150, 380 + 50};

    switch (message)
    {
    case WM_CREATE:
    {
        hBackgroundBitmap = LoadBitmapFromFile("resources/BACKGROUND.bmp");
        hMusicBitmap = LoadBitmapFromFile("resources/MUSIC.bmp");
        hMusicMaskBitmap = LoadBitmapFromFile("resources/MUSIC_mask.bmp");
        hOnBitmap = LoadBitmapFromFile("resources/ON.bmp");
        hOnMaskBitmap = LoadBitmapFromFile("resources/ON_mask.bmp");
        hOffBitmap = LoadBitmapFromFile("resources/OFF.bmp");
        hOffMaskBitmap = LoadBitmapFromFile("resources/OFF_mask.bmp");
        hArrowBitmap = LoadBitmapFromFile("resources/ARROW.bmp");
        hArrowMaskBitmap = LoadBitmapFromFile("resources/ARROW_mask.bmp");
        hONHoverBitmap = LoadBitmapFromFile("resources/ON_HOVER.bmp");
        hONHoverMaskBitmap = LoadBitmapFromFile("resources/ON_HOVER_mask.bmp");
        hOFFHoverBitmap = LoadBitmapFromFile("resources/OFF_HOVER.bmp");
        hOFFHoverMaskBitmap = LoadBitmapFromFile("resources/OFF_HOVER_mask.bmp");
        hArrowHoverBitmap = LoadBitmapFromFile("resources/ARROW_HOVER.bmp");
        hArrowHoverMaskBitmap = LoadBitmapFromFile("resources/ARROW_HOVER_mask.bmp");
        hCursorCustom = (HCURSOR)LoadImage(NULL, "resources/cursor.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
        SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursorCustom);

        POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.44);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.44 + 0.08);
        onRect1 = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
        right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
        arrowRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdcOriginal = BeginPaint(hwnd, &ps);

        HDC hdc = CreateCompatibleDC(hdcOriginal);
        HBITMAP hbmBUFFER = CreateCompatibleBitmap(hdcOriginal, ps.rcPaint.right, ps.rcPaint.bottom);
        HBITMAP hbmBUFFEROLD = (HBITMAP)SelectObject(hdc, hbmBUFFER);

        hdcMem = CreateCompatibleDC(hdc);
        hdcMask = CreateCompatibleDC(hdc);

        if (hBackgroundBitmap)
        {
            BITMAP bmpBackground;
            GetObject(hBackgroundBitmap, sizeof(BITMAP), &bmpBackground);
            RECT rect;
            GetClientRect(hwnd, &rect);
            HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBackgroundBitmap);
            StretchBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcMem, 0, 0, bmpBackground.bmWidth, bmpBackground.bmHeight, SRCCOPY);
            SelectObject(hdcMem, hOldBitmap);
        }

        BITMAP bmpOn, bmpOff, bmpArrow, bmpMusic;
        GetObject(hMusicBitmap, sizeof(BITMAP), &bmpMusic);
        GetObject(hOnBitmap, sizeof(BITMAP), &bmpOn);
        GetObject(hOffBitmap, sizeof(BITMAP), &bmpOff);
        GetObject(hArrowBitmap, sizeof(BITMAP), &bmpArrow);

        if (hMusicBitmap && hMusicMaskBitmap)
        {
            HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hMusicBitmap);
            HBITMAP hOldMask = (HBITMAP)SelectObject(hdcMask, hMusicMaskBitmap);
            POINT left_top = get_screen_from_relative(hwnd, 0.239, 0.43);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.239 + 0.275, 0.43 + 0.1);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bmpMusic.bmWidth, bmpMusic.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bmpMusic.bmWidth, bmpMusic.bmHeight, SRCAND);
            SelectObject(hdcMem, hOldBitmap);
            SelectObject(hdcMask, hOldMask);
        }

        if (isHoverOn1)
        {
            if (onCounter1 % 2 == 0)
            {
                HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hONHoverBitmap);
                HBITMAP hOldMask = (HBITMAP)SelectObject(hdcMask, hONHoverMaskBitmap);
                POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.39);
                POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.39 + 0.2);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCPAINT);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCAND);
                SelectObject(hdcMem, hOldBitmap);
                SelectObject(hdcMask, hOldMask);
                mciSendString("open resources/muzika.wav type waveaudio alias mydev", NULL, 0, NULL);
                mciSendString("play mydev notify", NULL, 0, NULL);
                music_on = true;
            }
            else
            {
                HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hOFFHoverBitmap);
                HBITMAP hOldMask = (HBITMAP)SelectObject(hdcMask, hOFFHoverMaskBitmap);
                POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.39);
                POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.39 + 0.2);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCPAINT);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCAND);
                SelectObject(hdcMem, hOldBitmap);
                SelectObject(hdcMask, hOldMask);
                mciSendString("stop mydev", NULL, 0, NULL);
                mciSendString("close mydev", NULL, 0, NULL);
                music_on = false;
            }
        }
        else
        {
            if (onCounter1 % 2 == 0)
            {
                HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hOnBitmap);
                HBITMAP hOldMask = (HBITMAP)SelectObject(hdcMask, hOnMaskBitmap);
                POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.39);
                POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.39 + 0.2);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCPAINT);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCAND);
                SelectObject(hdcMem, hOldBitmap);
                SelectObject(hdcMask, hOldMask);
            }
            else
            {
                HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hOffBitmap);
                HBITMAP hOldMask = (HBITMAP)SelectObject(hdcMask, hOffMaskBitmap);
                POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.39);
                POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.39 + 0.2);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCPAINT);
                StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bmpOn.bmWidth, bmpOn.bmHeight, SRCAND);
                SelectObject(hdcMem, hOldBitmap);
                SelectObject(hdcMask, hOldMask);
            }
        }

        if (hoveringArrow && hArrowHoverBitmap && hArrowHoverMaskBitmap)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hArrowHoverBitmap);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hArrowHoverMaskBitmap);
            GetObject(hArrowHoverBitmap, sizeof(BITMAP), &bmpArrow);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bmpArrow.bmWidth, bmpArrow.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bmpArrow.bmWidth, bmpArrow.bmHeight, SRCAND);
            SelectObject(hdcMem, oldBmp);
            SelectObject(hdcMask, oldMask);
        }
        else if (hArrowBitmap && hArrowMaskBitmap)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hArrowBitmap);
            HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hArrowMaskBitmap);
            GetObject(hArrowBitmap, sizeof(BITMAP), &bmpArrow);
            POINT left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
            POINT right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bmpArrow.bmWidth, bmpArrow.bmHeight, SRCPAINT);
            StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bmpArrow.bmWidth, bmpArrow.bmHeight, SRCAND);
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
    {
        POINT left_top = get_screen_from_relative(hwnd, 0.51, 0.44);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.51 + 0.275, 0.44 + 0.08);
        onRect1 = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.235, 0.69);
        right_bottom = get_screen_from_relative(hwnd, 0.235 + 0.09, 0.69 + 0.1);
        arrowRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        InvalidateRect(hwnd, 0, 0);
        break;
    }
    case WM_MOUSEMOVE:
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        bool prevHoverON = isHoverOn;
        bool prevHoverOF = isHoverOn1;
        bool prevHoverArrow = hoveringArrow;

        isHoverOn1 = PtInRect(&onRect1, pt);
        isHoverArrow = PtInRect(&arrowRect, pt);
        hoveringArrow = PtInRect(&arrowRect, pt);
        if (isHoverOn1 != prevHoverOF || hoveringArrow != prevHoverArrow)
        {
            InvalidateRect(hwnd, NULL, NULL);
        }
        break;
    }

    case WM_LBUTTONDOWN:
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (PtInRect(&onRect1, pt))
        {
            onCounter1++;
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            InvalidateRect(hwnd, NULL, NULL);
        }
        if (PtInRect(&arrowRect, pt))
        {
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            *nextStatePtr = new Main_Menu(nextStatePtr, hInstance, player_data, music_on);
        }
        break;
    }

    case WM_DESTROY:
    {

        PostQuitMessage(0);
        break;
    }

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
