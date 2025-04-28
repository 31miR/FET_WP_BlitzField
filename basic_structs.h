#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H

bool points_equal(const POINT &p1, const POINT &p2);
double rand_range(double b, double e);
#include "includes.h"

struct Player_Data
{
    std::string name;
    int health_upgrades;
    int stamina_upgrades;
    int unspent_upgrades;
    int levels_finished_count;
    int last_level_played;
};

struct Path_Connection
{
    POINT *pt1;
    POINT *pt2;
    Path_Connection(POINT *pt1, POINT *pt2) : pt1{pt1}, pt2{pt2} {}
    bool operator==(const Path_Connection &other)
    {
        if (points_equal(*pt1, *other.pt1) && points_equal(*pt2, *other.pt2))
            return true;
        if (points_equal(*pt2, *other.pt1) && points_equal(*pt1, *other.pt2))
            return true;
        return false;
    }
    bool operator!=(const Path_Connection &other)
    {
        return !(*this == other);
    }
    bool is_point_in_path(POINT *p)
    {
        if (points_equal(*pt1, *p))
            return true;
        if (points_equal(*pt2, *p))
            return true;
        return false;
    }
};

struct TEXTURE
{
    HBITMAP hbmp;
    HBITMAP hbmp_mask;
};

struct ANIM_DATA
{
    int frames_per_sprite;
    int frame_counter;
    int current_sprite_index;
    std::vector<TEXTURE> *sprites;
};

struct POINT_DECIMAL
{
    double x;
    double y;
};

struct RECT_DECIMAL
{
    double left;
    double top;
    double right;
    double bottom;
};

#endif // BASIC_STRUCTS_H
