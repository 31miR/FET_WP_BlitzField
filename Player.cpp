#include "Player.h"

void Player::load_player_bitmaps_from_default()
{
    static std::string main_folder_path = "./resources/player_anims";
    load_textures_to_vector_from_folder(feet_idle, main_folder_path + "/feet/idle", 1);
    load_textures_to_vector_from_folder(feet_forward, main_folder_path + "/feet/running", 4);
    load_textures_to_vector_from_folder(body_idle, main_folder_path + "/body/idle", 1);
    load_textures_to_vector_from_folder(body_attack, main_folder_path + "/body/slash", 8);
    load_textures_to_vector_from_folder(body_dash, main_folder_path + "/body/dash", 10);
}

void Player::destroy_all_bitmaps()
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
    for (auto &i : body_attack)
    {
        DeleteObject(i.hbmp);
        DeleteObject(i.hbmp_mask);
    }
    body_attack.clear();
    for (auto &i : body_dash)
    {
        DeleteObject(i.hbmp);
        DeleteObject(i.hbmp_mask);
    }
    body_dash.clear();
}

std::vector<TEXTURE> Player::feet_idle;
std::vector<TEXTURE> Player::feet_forward;
std::vector<TEXTURE> Player::body_idle;
std::vector<TEXTURE> Player::body_attack;
std::vector<TEXTURE> Player::body_dash;
