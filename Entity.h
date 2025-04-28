#ifndef ENTITY_H
#define ENTITY_H

#include "includes.h"

struct Entity
{
    double hitbox_width = 15;
    double hitbox_height = 15;
    POINT_DECIMAL position;
    POINT_DECIMAL rotation_vector;
};

#endif // ENTITY_H
