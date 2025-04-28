#include "Bullet_Trail.h"

void Bullet_Trail::calculate_end_point(const std::vector<RECT> &walls)
{
    // we assume that initial end_point is already set on the line of the bullet trajectory
    POINT_DECIMAL new_end_point = end_point;
    double new_distance = 1024;          // max distance that a bullet will be fired
    double next_jump = new_distance / 2; // we will attempt to find optimal end point with binary search

    POINT_DECIMAL rotation = {end_point.x - begin_point.x, end_point.y - begin_point.y};

    for (int i = 0; i < 10; ++i) // 10 iterations will be probably enough because by then we will already be at 1024 / 2^10 pixel precision
    {
        double dx = new_end_point.x - begin_point.x;
        double dy = new_end_point.y - begin_point.y;
        double current_distance = sqrt(dx * dx + dy * dy);
        new_end_point = {begin_point.x + new_distance * dx / current_distance, begin_point.y + new_distance * dy / current_distance};

        Entity dummy1;
        dummy1.position = begin_point;
        Entity dummy2;
        dummy2.position = new_end_point;
        if (are_characters_blocked_by_walls(dummy1, dummy2, walls))
            new_distance -= next_jump;
        else
            new_distance += next_jump;

        next_jump = next_jump / 2;
    }

    end_point = new_end_point;
}
