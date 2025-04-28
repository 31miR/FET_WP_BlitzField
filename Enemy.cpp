#include "Enemy.h"

void Enemy::load_enemy_bitmaps_from_default()
{
    static std::string main_folder_path = "./resources/basic_enemy_anims";
    load_textures_to_vector_from_folder(feet_idle, main_folder_path + "/feet/idle", 1);
    load_textures_to_vector_from_folder(feet_forward, main_folder_path + "/feet/running", 4);
    load_textures_to_vector_from_folder(body_idle, main_folder_path + "/body/idle", 1);
    load_textures_to_vector_from_folder(body_dying, main_folder_path + "/body/dying", 6);
}

void Enemy::destroy_all_bitmaps()
{
    for (auto &i : feet_idle)
    {
        DeleteObject(i.hbmp);
        DeleteObject(i.hbmp_mask);
    }
    feet_idle.clear();
    for (auto &i : feet_forward)
    {
        DeleteObject(i.hbmp);
        DeleteObject(i.hbmp_mask);
    }
    feet_forward.clear();
    for (auto &i : body_idle)
    {
        DeleteObject(i.hbmp);
        DeleteObject(i.hbmp_mask);
    }
    body_idle.clear();
    for (auto &i : body_dying)
    {
        DeleteObject(i.hbmp);
        DeleteObject(i.hbmp_mask);
    }
    body_dying.clear();
}

std::vector<TEXTURE> Enemy::feet_idle;
std::vector<TEXTURE> Enemy::feet_forward;
std::vector<TEXTURE> Enemy::body_idle;
std::vector<TEXTURE> Enemy::body_dying;
