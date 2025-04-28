#include "Enemy_Group.h"

bool Enemy_Group::is_node_free(const POINT &p)
{
    for (Enemy &e : alive_enemies)
    {
        POINT enemy_pos = {e.position.x, e.position.y};
        if (points_equal(enemy_pos, p))
            return false;
        if (e.next_node != nullptr && points_equal(*(e.next_node), p))
            return false;
    }
    return true;
}

bool Enemy_Group::are_nodes_adjacent(POINT p1, POINT p2)
{
    Path_Connection pc{&p1, &p2};
    for (Path_Connection i : path_connections)
    {
        if (pc == i)
            return true;
    }
    return false;
}

std::vector<POINT *> Enemy_Group::get_available_nodes(const Enemy &e)
{
    std::vector<POINT *> ret;
    POINT current_pos = {e.position.x, e.position.y};
    for (POINT &p : path_nodes)
    {
        if (!are_nodes_adjacent(p, current_pos))
            continue;
        if (!is_node_free(p))
            continue;
        ret.push_back(&p);
    }
    return ret;
}

void Enemy_Group::order_new_positions()
{
    if (in_combat)
        return;
    for (Enemy &e : alive_enemies)
    {
        if (e.next_node != nullptr)
            continue;
        std::vector<POINT *> possibilities = get_available_nodes(e);
        double r = rand_range(0, 1);
        if (r < 0.4 && possibilities.size() != 0)
        {
            e.next_node = possibilities[(int)(r * possibilities.size() / 0.4)];
        }
    }
}

void Enemy_Group::step_all_towards_nodes()
{
    static double SPEED = 0.5;
    for (Enemy &e : alive_enemies)
    {
        if (e.next_node == nullptr)
            continue;
        if (abs(e.next_node->x - e.position.x) < SPEED && abs(e.next_node->y - e.position.y) < SPEED)
        {
            e.position.x = e.next_node->x;
            e.position.y = e.next_node->y;
            e.next_node = nullptr;
            continue;
        }
        if (e.is_running == false)
        {
            e.is_running = true;
            e.current_anim_feet.current_sprite_index = 0;
            e.current_anim_feet.frames_per_sprite = 10;
            e.current_anim_feet.frame_counter = 0;
            e.current_anim_feet.sprites = &e.feet_forward;
        }
        else
        {
            e.current_anim_feet.frame_counter += 1;
            if (e.current_anim_feet.frame_counter == e.current_anim_feet.frames_per_sprite)
            {
                e.current_anim_feet.frame_counter = 0;
                e.current_anim_feet.current_sprite_index = (e.current_anim_feet.current_sprite_index + 1) % e.current_anim_feet.sprites->size();
            }
        }
        e.rotation_vector = {e.next_node->x - e.position.x, e.next_node->y - e.position.y};
        double d = sqrt(e.rotation_vector.x * e.rotation_vector.x + e.rotation_vector.y * e.rotation_vector.y);
        e.position.x += SPEED * (e.rotation_vector.x / d);
        e.position.y += SPEED * (e.rotation_vector.y / d);
    }
}

void Enemy_Group::attack()
{
    Entity player;
    player.position = player_percieved_pos;
    for (Enemy &e : alive_enemies)
    {
        if (are_characters_blocked_by_walls(e, player, high_rects))
            continue;
        e.rotation_vector = {player.position.x - e.position.x, player.position.y - e.position.y};
        e.frames_until_fire--;
        if (e.frames_until_fire == 0)
        {
            e.frames_until_fire = e.FRAMES_PER_FIRE;
            e.fired_bullet = true;
        }
    }
}

void Enemy_Group::detect_death_for_player_slash(const Entity &player)
{
    static double MAX_KILL_DISTANCE = 20;
    for (int i = 0; i < alive_enemies.size(); ++i)
    {
        double dx = alive_enemies[i].position.x - player.position.x;
        double dy = alive_enemies[i].position.y - player.position.y;
        double distance = sqrt(dx * dx + dy * dy);
        if (distance > MAX_KILL_DISTANCE)
            continue;
        // ensures proper rotation
        // if (!does_character_see_character(player, alive_enemies[i], high_rects))
        //     continue;
        // but makes it unnecessarily hard to hit your opponent
        Enemy killed = alive_enemies[i];
        alive_enemies.erase(alive_enemies.begin() + i);
        i--;
        killed.current_anim_body.current_sprite_index = 0;
        killed.current_anim_body.frames_per_sprite = killed.FRAMES_PER_FLICKER_DYING;
        killed.current_anim_body.frame_counter = 0;
        killed.current_anim_body.sprites = &killed.body_dying;
        dead_enemies.push_back(killed);
    }
}

void Enemy_Group::increment_dead_enemies_anims()
{
    for (int i = 0; i < dead_enemies.size(); ++i)
    {
        dead_enemies[i].current_anim_body.frame_counter++;
        if (dead_enemies[i].current_anim_body.frame_counter == dead_enemies[i].current_anim_body.frames_per_sprite)
        {
            dead_enemies[i].current_anim_body.frame_counter = 0;
            dead_enemies[i].current_anim_body.current_sprite_index++;
            if (dead_enemies[i].current_anim_body.current_sprite_index == dead_enemies[i].current_anim_body.sprites->size())
            {
                dead_enemies.erase(dead_enemies.begin() + i);
                i--;
            }
        }
    }
}
