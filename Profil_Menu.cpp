#include "Profil_Menu.h"
#include "App_State.h"
#include "Main_Menu.h"
#include <windowsx.h>
#include <windows.h>
#include <Mmsystem.h>
#include "sqlite3.h"

Profil_Menu::Profil_Menu(App_State **nextState, HINSTANCE hInstance, bool music_on)
{
    this->music_on = music_on;
    this->nextStatePtr = nextState;
    this->hInstance = hInstance;
    hbmButton = hbmMask = NULL;
    hbmSelect = hbmSelectMask = NULL;
    hbmCreate = hbmCreateMask = NULL;
    hbmSelectHover = hbmSelectHoverMask = NULL;
    hbmCreateHover = hbmCreateHoverMask = NULL;
    hbmButtonHover = hbmButtonHoverMask = NULL;
}

Profil_Menu::~Profil_Menu()
{

    DeleteObject(hbmSelect);
    DeleteObject(hbmSelectMask);
    DeleteObject(hbmCreate);
    DeleteObject(hbmCreateMask);
    DeleteObject(hbmButton);
    DeleteObject(hbmMask);
    DeleteObject(hbmSelectHover);
    DeleteObject(hbmSelectHoverMask);
    DeleteObject(hbmCreateHover);
    DeleteObject(hbmCreateHoverMask);
    DeleteObject(hbmButtonHover);
    DeleteObject(hbmButtonHoverMask);
    DeleteObject(hCursorCustom);
}

void Profil_Menu::run(HWND hwnd) {}

std::string wstringToString(const std::wstring &wstr)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &str[0], size_needed, NULL, NULL);
    return str;
}

void Profil_Menu::dodajProfilUBazu(const wchar_t *ime)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int rc = sqlite3_open("game_data.db", &db);

    if (rc != SQLITE_OK)
    {
        MessageBox(NULL, "Ne mogu otvoriti bazu!", "Greška", MB_OK | MB_ICONERROR);
        return;
    }

    const char *sql = "INSERT INTO Player_Data (name, health_upgrades, stamina_upgrades, unspent_upgrades, levels_finished_count, last_level_played) "
                      "VALUES (?, 0, 0, 0, 0, -1);";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        MessageBox(NULL, "Neuspješan upit!", "Greška", MB_OK | MB_ICONERROR);
        sqlite3_close(db);
        return;
    }

    std::string imeStr = wstringToString(ime);

    sqlite3_bind_text(stmt, 1, imeStr.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        MessageBox(NULL, "Greška pri unosu podataka!", "Greška", MB_OK | MB_ICONERROR);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Profil_Menu::ucitajProfile(HWND hListBox)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("game_data.db", &db);

    if (rc != SQLITE_OK)
    {
        MessageBox(NULL, "Ne mogu otvoriti bazu!", "Greška", MB_OK | MB_ICONERROR);
        return;
    }

    const char *sql = "SELECT name FROM Player_Data;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        MessageBox(NULL, "Neuspješan upit!", "Greška", MB_OK | MB_ICONERROR);
        sqlite3_close(db);
        return;
    }

    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char *imeProfila = sqlite3_column_text(stmt, 0);
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)imeProfila);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

LRESULT CALLBACK AntiFlickerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam,
                                 UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (msg)
    {
    case WM_ERASEBKGND:
        return TRUE; // Sprečava automatsko brisanje pozadine

    default:
        return DefSubclassProc(hwnd, msg, wParam, lParam);
    }
}

LRESULT Profil_Menu::winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE:
    {
        if (music_on)
        {
            mciSendString("open resources/muzika.wav type waveaudio alias mydev", NULL, 0, NULL);
            mciSendString("play mydev notify", NULL, 0, NULL);
        }
        POINT left_top = get_screen_from_relative(hwnd, 0.25, 0.48);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.25 + 0.235, 0.48 + 0.04);
        hEditBox = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                                 left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hwnd, (HMENU)1000, hInstance, NULL);
        SetWindowSubclass(hEditBox, AntiFlickerProc, 0, 0);
        left_top = get_screen_from_relative(hwnd, 0.502, 0.369);
        right_bottom = get_screen_from_relative(hwnd, 0.502 + 0.255, 0.369 + 0.376);
        hListBox = CreateWindowW(L"LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_STANDARD,
                                 left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hwnd, (HMENU)1001, hInstance, NULL);
        SetWindowSubclass(hEditBox, AntiFlickerProc, 0, 0);
        ucitajProfile(hListBox);

        if (!hListBox || !hEditBox)
        {
            MessageBox(hwnd, "Failed to create controls!", "Error", MB_OK | MB_ICONERROR);
            return -1;
        }
        hbmBackground = (HBITMAP)LoadImage(NULL, "resources/BACKGROUND.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmSelect = (HBITMAP)LoadImage(NULL, "resources/SELECTPROFILE.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmSelectMask = (HBITMAP)LoadImage(NULL, "resources/SELECTPROFILE_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmCreate = (HBITMAP)LoadImage(NULL, "resources/CREATEPROFILE.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmCreateMask = (HBITMAP)LoadImage(NULL, "resources/CREATEPROFILE_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmButton = (HBITMAP)LoadImage(NULL, "resources/EXIT_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "resources/EXIT_1_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        hbmSelectHover = (HBITMAP)LoadImage(NULL, "resources/SELECT_PROFILE_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmSelectHoverMask = (HBITMAP)LoadImage(NULL, "resources/SELECT_PROFILE_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmCreateHover = (HBITMAP)LoadImage(NULL, "resources/CREATEPROFILE_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmCreateHoverMask = (HBITMAP)LoadImage(NULL, "resources/CREATEPROFILE_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmButtonHover = (HBITMAP)LoadImage(NULL, "resources/EXIT_HOVER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmButtonHoverMask = (HBITMAP)LoadImage(NULL, "resources/EXIT_HOVER_mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hCursorCustom = (HCURSOR)LoadImage(NULL, "resources/cursor.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
        SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursorCustom);

        break;
    }
    case WM_SIZE:
    {
        POINT left_top = get_screen_from_relative(hwnd, 0.25, 0.48);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.25 + 0.235, 0.48 + 0.04);
        SetWindowPos(hEditBox, HWND_TOP, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, 0);
        left_top = get_screen_from_relative(hwnd, 0.502, 0.369);
        right_bottom = get_screen_from_relative(hwnd, 0.502 + 0.255, 0.369 + 0.376);
        SetWindowPos(hListBox, HWND_TOP, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, 0);
        InvalidateRect(hwnd, 0, 0);
        break;
    }
    case WM_MOUSEMOVE:
    {
        POINT pt = {LOWORD(lParam), HIWORD(lParam)};

        POINT left_top = get_screen_from_relative(hwnd, 0.225, 0.55);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.55 + 0.08);
        RECT selectRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.225, 0.37);
        right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.37 + 0.08);
        RECT createRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.225, 0.65);
        right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.65 + 0.08);
        RECT exitRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};

        bool prevHoverSelect = hoverSelect;
        bool prevHoverCreate = hoverCreate;
        bool prevHoverExit = hoverExit;

        hoverSelect = PtInRect(&selectRect, pt);
        hoverCreate = PtInRect(&createRect, pt);
        hoverExit = PtInRect(&exitRect, pt);

        if (prevHoverSelect != hoverSelect || prevHoverCreate != hoverCreate || prevHoverExit != hoverExit)
        {
            InvalidateRect(hwnd, NULL, NULL);
        }
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
        BITMAP bm;
        if (hbmBackground)
        {
            HBITMAP oldBmp = (HBITMAP)SelectObject(hdcMem, hbmBackground);
            GetObject(hbmBackground, sizeof(BITMAP), &bm);
            StretchBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
            SelectObject(hdcMem, oldBmp);
        }

        HBITMAP imgSelect = hoverSelect ? hbmSelectHover : hbmSelect;
        HBITMAP imgSelectMask = hoverSelect ? hbmSelectHoverMask : hbmSelectMask;
        HBITMAP imgCreate = hoverCreate ? hbmCreateHover : hbmCreate;
        HBITMAP imgCreateMask = hoverCreate ? hbmCreateHoverMask : hbmCreateMask;
        HBITMAP imgExit = hoverExit ? hbmButtonHover : hbmButton;
        HBITMAP imgExitMask = hoverExit ? hbmButtonHoverMask : hbmMask;

        SelectObject(hdcMem, imgSelect);
        SelectObject(hdcMask, imgSelectMask);
        GetObject(imgSelect, sizeof(BITMAP), &bm);
        POINT left_top = get_screen_from_relative(hwnd, 0.225, 0.5);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.5 + 0.2);
        StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
        StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);

        SelectObject(hdcMem, imgCreate);
        SelectObject(hdcMask, imgCreateMask);
        GetObject(imgCreate, sizeof(BITMAP), &bm);
        left_top = get_screen_from_relative(hwnd, 0.225, 0.32);
        right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.32 + 0.2);
        StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
        StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);

        SelectObject(hdcMem, imgExit);
        SelectObject(hdcMask, imgExitMask);
        GetObject(imgExit, sizeof(BITMAP), &bm);
        left_top = get_screen_from_relative(hwnd, 0.225, 0.6);
        right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.6 + 0.2);
        StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCPAINT);
        StretchBlt(hdc, left_top.x, left_top.y, right_bottom.x - left_top.x, right_bottom.y - left_top.y, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCAND);

        DeleteDC(hdcMem);
        DeleteDC(hdcMask);

        BitBlt(hdcOriginal, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, hdc, 0, 0, SRCCOPY);

        SelectObject(hdc, hbmBUFFEROLD);
        DeleteObject(hbmBUFFER);
        DeleteDC(hdc);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        POINT left_top = get_screen_from_relative(hwnd, 0.225, 0.55);
        POINT right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.55 + 0.08);
        RECT selectRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.225, 0.37);
        right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.37 + 0.08);
        RECT createRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        left_top = get_screen_from_relative(hwnd, 0.225, 0.65);
        right_bottom = get_screen_from_relative(hwnd, 0.225 + 0.275, 0.65 + 0.08);
        RECT exitRect = {left_top.x, left_top.y, right_bottom.x, right_bottom.y};
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (PtInRect(&createRect, pt))
        {
            wchar_t buffer[256];
            GetWindowTextW(hEditBox, buffer, 256);

            if (wcslen(buffer) > 0)
            {
                SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
                SetWindowTextW(hEditBox, L"");
                dodajProfilUBazu(buffer);
                ucitajProfile(hListBox);
                PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            break;
        }
        if (PtInRect(&selectRect, pt))
        {
            int index = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            if (index != LB_ERR)
            {
                char selectedProfile[256];
                ListBox_GetText(hListBox, index, &selectedProfile);

                PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);

                std::string name = std::string(selectedProfile);

                Player_Data player_data = DB_Helper::get_profile_from_username_in_DB(name);

                *nextStatePtr = new Main_Menu(nextStatePtr, hInstance, player_data, music_on);
            }
            break;
        }

        if (PtInRect(&exitRect, pt))
        {
            PlaySound(TEXT("resources/mouse.wav"), NULL, SND_FILENAME | SND_ASYNC);
            PostQuitMessage(0);
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
