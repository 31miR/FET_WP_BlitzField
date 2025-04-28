#ifndef PLAYER_H
#define PLAYER_H

#include "includes.h"

struct Player : public Entity
{
    double max_health_points;
    double health_points;
    double max_stamina;
    double stamina;
    bool is_running = false;
    bool is_slashing = false;
    bool is_dashing = false;
    static const unsigned int frames_per_sprite_running_legs = 10;
    static const unsigned int frames_per_sprite_slashing = 2;
    static const unsigned int frames_per_sprite_dashing = 1;
    double dash_per_frame_x = 0;
    double dash_per_frame_y = 0;
    // player specific bitmaps for each state
    static std::vector<TEXTURE> feet_idle;
    static std::vector<TEXTURE> feet_forward;
    static std::vector<TEXTURE> body_idle;
    static std::vector<TEXTURE> body_attack;
    static std::vector<TEXTURE> body_dash;
    ANIM_DATA current_anim_body = {1, 0, 0, &body_idle};
    ANIM_DATA current_anim_feet = {1, 0, 0, &feet_idle};
    static void load_player_bitmaps_from_default();
    static void destroy_all_bitmaps();
};

#endif // PLAYER_H
