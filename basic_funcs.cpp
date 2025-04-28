#include "basic_funcs.h"

#include "includes.h"

bool points_equal(const POINT &p1, const POINT &p2)
{
    if (p1.x != p2.x)
        return false;
    if (p1.y != p2.y)
        return false;
    return true;
}

double rand_range(double b, double e)
{
    return (e - b) * ((double)rand() / RAND_MAX) + b;
}

// detection stuff
bool does_character_see_character(const Entity &seer, const Entity &seen, const std::vector<RECT> &walls)
{
    static int MAX_DISTANCE = 100;
    double towards_seen_x = seen.position.x - seer.position.x;
    double towards_seen_y = seen.position.y - seer.position.y;
    double d_towards_seen = sqrt(towards_seen_x * towards_seen_x + towards_seen_y * towards_seen_y);
    double d_rotation_vec = sqrt(seer.rotation_vector.x * seer.rotation_vector.x + seer.rotation_vector.y * seer.rotation_vector.y);
    double cosANGLE = (towards_seen_x * seer.rotation_vector.x + towards_seen_y * seer.rotation_vector.y) / (d_towards_seen * d_rotation_vec);
    if (cosANGLE < 0)
        return false;
    double dx = seer.position.x - seen.position.x;
    double dy = seer.position.y - seen.position.y;
    double d = sqrt(dx * dx + dy * dy);
    if (d > MAX_DISTANCE)
        return false;
    return !are_characters_blocked_by_walls(seer, seen, walls);
}

bool are_characters_blocked_by_walls(const Entity &c1, const Entity &c2, const std::vector<RECT> &walls)
{
    for (RECT r : walls)
    {
        if (is_wall_between_characters(c1, c2, r))
            return true;
    }
    return false;
}
bool is_wall_between_characters(const Entity &c1, const Entity &c2, const RECT &wall)
{
    if (c1.position.x == c2.position.x)
        return is_wall_between_characters_vertical(c1, c2, wall);
    double x_greater = c2.position.x > c1.position.x ? c2.position.x : c1.position.x;
    double x_smaller = c2.position.x > c1.position.x ? c1.position.x : c2.position.x;
    double y_greater = c2.position.y > c1.position.y ? c2.position.y : c1.position.y;
    double y_smaller = c2.position.y > c1.position.y ? c1.position.y : c2.position.y;
    if (wall.left > x_greater || wall.right < x_smaller)
        return false;
    if (wall.top > y_greater || wall.bottom < y_smaller)
        return false;
    double K = (c2.position.y - c1.position.y) / (c2.position.x - c1.position.x);
    double N = c1.position.y - c1.position.x * K;
    if (is_point_above_line(K, N, {wall.left, wall.top}) != is_point_above_line(K, N, {wall.left, wall.bottom}))
        return true;
    if (is_point_above_line(K, N, {wall.left, wall.bottom}) != is_point_above_line(K, N, {wall.right, wall.bottom}))
        return true;
    if (is_point_above_line(K, N, {wall.right, wall.bottom}) != is_point_above_line(K, N, {wall.right, wall.top}))
        return true;
    if (is_point_above_line(K, N, {wall.right, wall.top}) != is_point_above_line(K, N, {wall.left, wall.top}))
        return true;
}
bool is_wall_between_characters_vertical(const Entity &c1, const Entity &c2, const RECT &wall)
{
    if (wall.right < c1.position.x || wall.left > c1.position.x)
        return false;
    double y_greater = c2.position.y > c1.position.y ? c2.position.y : c1.position.y;
    double y_smaller = c2.position.y > c1.position.y ? c1.position.y : c2.position.y;
    if (wall.top > y_greater || wall.bottom < y_smaller)
        return false;
    return true;
}

bool is_point_above_line(double k, double n, const POINT &p)
{
    double y_actual = k * p.x + n;
    return p.y > y_actual;
}

bool did_bullet_hit(const Entity &shooter, const Entity &target, const std::vector<RECT> &walls)
{
    if (are_characters_blocked_by_walls(shooter, target, walls))
        return false;
    double cosMAX_ANGLE;
    double sinMAX_ANGLE;
    double cosACTUAL;

    double d_shooter_target = sqrt((shooter.position.x - target.position.x) * (shooter.position.x - target.position.x) + (shooter.position.y - target.position.y) * (shooter.position.y - target.position.y));

    sinMAX_ANGLE = target.hitbox_width / d_shooter_target;
    cosMAX_ANGLE = sqrt(1 - sinMAX_ANGLE * sinMAX_ANGLE);

    double towards_target_x = target.position.x - shooter.position.x;
    double towards_target_y = target.position.y - shooter.position.y;

    double d_rot_vec = sqrt(shooter.rotation_vector.x * shooter.rotation_vector.x + shooter.rotation_vector.y * shooter.rotation_vector.y);

    cosACTUAL = (towards_target_x * shooter.rotation_vector.x + towards_target_y * shooter.rotation_vector.y) / (d_shooter_target * d_rot_vec);

    if (cosACTUAL > cosMAX_ANGLE)
        return true;
    return false;
}

// tools for main menu
POINT get_screen_from_relative(HWND hwnd, const POINT_DECIMAL &p)
{
    return get_screen_from_relative(hwnd, p.x, p.y);
}
POINT get_screen_from_relative(HWND hwnd, double x, double y)
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    return {rect.right * x, rect.bottom * y};
}
POINT_DECIMAL get_relative_from_screen(HWND hwnd, const POINT &p)
{
    return get_relative_from_screen(hwnd, p.x, p.y);
}
POINT_DECIMAL get_relative_from_screen(HWND hwnd, int x, int y)
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    return {(double)x / rect.right, (double)y / rect.bottom};
}
