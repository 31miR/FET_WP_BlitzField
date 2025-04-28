#ifndef PROFIL_MENU_H
#define PROFIL_MENU_H

#include "App_State.h"
#include <vector>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#include <vector>
using namespace Gdiplus;

class Profil_Menu : public App_State
{
private:
    App_State **nextStatePtr;
    HINSTANCE hInstance;
    HWND hListBox, hEditBox;

    HBITMAP hbmButton;
    HBITMAP hbmMask;
    HBITMAP hbmSelect, hbmSelectMask;
    HBITMAP hbmCreate, hbmCreateMask, hbmBackground;
    HBITMAP hbmSelectHover, hbmSelectHoverMask;
    HBITMAP hbmCreateHover, hbmCreateHoverMask;
    HBITMAP hbmButtonHover, hbmButtonHoverMask;
    bool hoverSelect, hoverCreate, hoverExit, music_on;
    HCURSOR hCursorCustom;

public:
    Profil_Menu(App_State **nextState, HINSTANCE hInstance, bool music_on = true);
    void dodajProfilUBazu(const wchar_t *ime);
    void deleteProfilIzBaze(const wchar_t *ime);
    ~Profil_Menu();
    void run(HWND hwnd) override;
    LRESULT CALLBACK winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
    void ucitajProfile(HWND hListBox);
};

#endif
