#ifndef ENEMY_GROUP_H
#define ENEMY_GROUP_H

#include <vector>
#include "includes.h"

struct Enemy_Group
{
    void attack();
    void detect_death_for_player_slash(const Entity &player);
    void increment_dead_enemies_anims();
    void order_new_positions();
    void step_all_towards_nodes();
    std::vector<POINT *> get_available_nodes(const Enemy &e);
    bool are_nodes_adjacent(POINT p1, POINT p2);
    bool is_node_free(const POINT &p);
    bool in_combat = false;
    POINT_DECIMAL player_percieved_pos;
    std::vector<POINT> path_nodes;
    std::vector<Path_Connection> path_connections;
    std::vector<RECT> high_rects;
    std::vector<RECT> low_rects;
    std::vector<Enemy> alive_enemies;
    std::vector<Enemy> dead_enemies; // just for drawing purposes
};

#endif // ENEMY_GROUP_H
