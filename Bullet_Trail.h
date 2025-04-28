#ifndef BULLET_TRAIL_H
#define BULLET_TRAIL_H

#include "includes.h"

struct Bullet_Trail
{
    POINT_DECIMAL begin_point;
    POINT_DECIMAL end_point;
    static const int FRAMES_PER_ANIM = 5;
    int current_frame = 0;
    int current_width = 5;
    void calculate_end_point(const std::vector<RECT> &walls);
};

#endif // BULLET_TRAIL_H
