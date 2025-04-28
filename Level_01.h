#ifndef LEVEL_01_
#define LEVEL_01_

#include "includes.h"
#include "Enemy_Group.h"
#include "End_Game.h"

/* This class is a test program for another project
 * which will implement a class similar to Level_01
 * among other classes. All other algorithms, funcs
 * structs, etc. written here will not, in the real
 * project, be written all in one file. I refuse to
 * put much effort into readability for one example
 * project. For now, it only matters the code works
 */

class Level_01 : public App_State
{
public:
    Level_01(App_State **p_next_state, const Player_Data &player_data, int level_index, bool music_on);
    void run(HWND hwnd) override;
    LRESULT winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
    void load_map(int level_index);
    void move_camera_to_player(HWND hwnd);
    POINT world_to_screen(const POINT_DECIMAL &coord);
    POINT_DECIMAL screen_to_world(const POINT &coord);
    void update_world_passive();
    void react_to_controls(HWND hwnd);
    void player_WASD();
    void player_DASH(HWND hwnd);
    void render(HWND hwnd); // implements double buffering
    void draw_current_frame(HDC hdc);
    void draw_HUD(HDC hdc);
    bool inside_any_object(const Entity &e);
    static bool inside_object(const Entity &e, const RECT &r);
    // bool inside_object(const Entity& e, const RECT_DECIMAL& r);
    void finish_level_end_game();
    void fail_level_end_game();
    void reset();
    ~Level_01();

private:
    Player player;
    HBITMAP map_image;
    std::queue<POINT_DECIMAL> player_position_history;
    std::vector<POINT> path_nodes;
    std::vector<Path_Connection> path_connections;
    std::vector<RECT> high_rects;
    std::vector<RECT> low_rects;
    Enemy_Group enemies;
    std::vector<Bullet_Trail> bullets_in_air;
    POINT_DECIMAL camera_position; // top-left corner of camera, (0,0) on the screen
    double camera_zoom = 5;
    double map_scale = 1;
    App_State **p_next_state;
    // std::vector<TEXTURE> enemy_feet_idle;
    // std::vector<TEXTURE> enemy_feet_forward;
    // std::vector<TEXTURE> enemy_body_idle;
    bool music_on;
    Player_Data player_data;
    POINT_DECIMAL initial_player_position;
    int initial_enemy_count;
    int level_index;
    HCURSOR hCursorCustom;

    static const std::vector<POINT_DECIMAL> initial_player_position_per_level;
    static const std::vector<int> initial_enemy_count_per_level;
};

#endif // LEVEL_01_
