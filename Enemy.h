#ifndef ENEMY_H
#define ENEMY_H

#include "includes.h"

struct Enemy : public Entity
{
    double health_points;
    bool is_running = false;
    POINT *next_node = nullptr;
    static const unsigned int frames_per_sprite_running_legs = 10;
    // enemy specific bitmaps for each state
    static std::vector<TEXTURE> feet_idle;
    static std::vector<TEXTURE> feet_forward;
    static std::vector<TEXTURE> body_idle;
    static std::vector<TEXTURE> body_dying;
    ANIM_DATA current_anim_body = {1, 0, 0, &body_idle};
    ANIM_DATA current_anim_feet = {1, 0, 0, &feet_idle};
    static const int FRAMES_PER_FLICKER_DYING = 5;
    static const int FRAMES_PER_FIRE = 38;
    int frames_until_fire = FRAMES_PER_FIRE;
    bool fired_bullet = false;
    static void load_enemy_bitmaps_from_default();
    static void destroy_all_bitmaps();
};

#endif // ENEMY_H
