#ifndef END_GAME_H
#define END_GAME_H

#include "includes.h"
#include "App_State.h"
#include "Level_01.h"
#include "Main_Menu.h"

class End_Game : public App_State
{
public:
    End_Game(App_State **p_next_state, const Player_Data &player_data, int level_index, int enemy_count, const POINT_DECIMAL &initial_player_position, bool music_on, bool success);
    void run(HWND hwnd) override;
    LRESULT winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
    void write_out_options(HWND hwnd, HDC hdc);
    ~End_Game();

private:
    App_State **p_next_state;
    Player_Data player_data;
    int level_index;
    int enemy_count;
    POINT_DECIMAL initial_player_position;
    HBITMAP title;
    HBITMAP title_mask;
    HBITMAP level;
    HBITMAP level_mask;
    HBITMAP main;
    HBITMAP main_mask;
    bool music_on;
    bool success;
};

#endif // END_GAME_H
