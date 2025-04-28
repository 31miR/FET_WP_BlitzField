#ifndef BASIC_FUNCS_H
#define BASIC_FUNCS_H

#include "includes.h"

bool points_equal(const POINT &p1, const POINT &p2);
double rand_range(double b, double e);

bool does_character_see_character(const Entity &seer, const Entity &seen, const std::vector<RECT> &walls);
bool are_characters_blocked_by_walls(const Entity &c1, const Entity &c2, const std::vector<RECT> &walls);
bool is_wall_between_characters(const Entity &c1, const Entity &c2, const RECT &wall);
bool is_wall_between_characters_vertical(const Entity &c1, const Entity &c2, const RECT &wall);
bool is_point_above_line(double k, double n, const POINT &p);

bool did_bullet_hit(const Entity &shooter, const Entity &target, const std::vector<RECT> &walls);

POINT get_screen_from_relative(HWND hwnd, const POINT_DECIMAL &p);
POINT get_screen_from_relative(HWND hwnd, double x, double y);
POINT_DECIMAL get_relative_from_screen(HWND hwnd, const POINT &p);
POINT_DECIMAL get_relative_from_screen(HWND hwnd, int x, int y);

#endif // BASIC_FUNCS_H
