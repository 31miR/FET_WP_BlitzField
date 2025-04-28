#include "Level_01.h"
#include <chrono>

const std::vector<POINT_DECIMAL> Level_01::initial_player_position_per_level = {{480, 790}, {990, 1000}, {680, 850}, {220, 700}};
const std::vector<int> Level_01::initial_enemy_count_per_level = {6, 9, 7, 8};

void Level_01::fail_level_end_game()
{
    *p_next_state = new End_Game(p_next_state, player_data, level_index, initial_enemy_count, initial_player_position, music_on, false);
}

void Level_01::finish_level_end_game()
{
    *p_next_state = new End_Game(p_next_state, player_data, level_index, initial_enemy_count, initial_player_position, music_on, true);
}

Level_01::~Level_01()
{
    Player::destroy_all_bitmaps();
    Enemy::destroy_all_bitmaps();
    DeleteObject(hCursorCustom);
    std::string dummy1 = "stop level_music";
    dummy1 += std::to_string(level_index);
    std::string dummy2 = "close level_music";
    dummy2 += std::to_string(level_index);
    mciSendString(dummy1.c_str(), NULL, 0, NULL);
    mciSendString(dummy2.c_str(), NULL, 0, NULL);
}

Level_01::Level_01(App_State **p_next_state, const Player_Data &player_data, int level_index, bool music_on)
    : p_next_state{p_next_state}, music_on{music_on}, player_data{player_data}, level_index{level_index}
{

    player.max_health_points = 100 + player_data.health_upgrades * 25;
    player.max_stamina = 100 + player_data.stamina_upgrades * 25;
    player.health_points = player.max_health_points;
    player.stamina = player.max_stamina;
    player.position = initial_player_position_per_level[level_index];
    player.rotation_vector = {1, 0};
    Player::load_player_bitmaps_from_default();
    Enemy::load_enemy_bitmaps_from_default();

    load_map(level_index);

    enemies.path_nodes = this->path_nodes;
    enemies.path_connections = this->path_connections;
    enemies.high_rects = this->high_rects;
    enemies.low_rects = this->low_rects;

    std::vector<POINT> available_positions = path_nodes;
    for (int i = 0; i < initial_enemy_count_per_level[level_index]; ++i)
    {
        int index = (int)rand_range(0, available_positions.size());
        Enemy e;
        e.position.x = available_positions[index].x;
        e.position.y = available_positions[index].y;
        enemies.alive_enemies.push_back(e);
        available_positions.erase(available_positions.begin() + index);
    }

    // LAST 10 frames are remembered ok
    for (int i = 0; i < 10; ++i)
    {
        player_position_history.push(player.position);
    }

    if (music_on)
    {
        std::string dummy1 = "open resources/maps/";
        dummy1 += std::to_string(level_index) + ".wav type waveaudio alias level_music" + std::to_string(level_index);
        std::string dummy2 = "play level_music";
        dummy2 += std::to_string(level_index) + " notify";
        mciSendString(dummy1.c_str(), NULL, 0, NULL);
        mciSendString(dummy2.c_str(), NULL, 0, NULL);
    }
}

void Level_01::load_map(int level_index)
{
    std::string map_location = "./resources/maps/";
    map_location += std::to_string(level_index); // eg: ./resources/maps/0 <-- missing extension
    map_image = (HBITMAP)LoadImage(NULL, (map_location + ".bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    std::ifstream file(map_location + ".mp");
    char dispose_char; // dummy variable
    /*get all high rects*/
    while (!file.eof())
    {
        while (file.peek() == ' ' || file.peek() == '\n')
            file.ignore();
        if (file.peek() == ';')
        {
            file >> dispose_char;
            break;
        }
        int a, b, c, d;
        file >> a >> b >> c >> d;
        high_rects.push_back({map_scale * a, map_scale * b, map_scale * c, map_scale * d});
    }
    /*get all low rects*/
    while (!file.eof())
    {
        while (file.peek() == ' ' || file.peek() == '\n')
            file.ignore();
        if (file.peek() == ';')
        {
            file >> dispose_char;
            break;
        }
        int a, b, c, d;
        file >> a >> b >> c >> d;
        low_rects.push_back({map_scale * a, map_scale * b, map_scale * c, map_scale * d});
    }
    /*get all nodes*/
    while (!file.eof())
    {
        while (file.peek() == ' ' || file.peek() == '\n')
            file.ignore();
        if (file.peek() == ';')
        {
            file >> dispose_char;
            break;
        }
        int a, b;
        file >> a >> b;
        path_nodes.push_back({map_scale * a, map_scale * b});
    }
    /*get all node connections*/
    while (!file.eof())
    {
        while (file.peek() == ' ' || file.peek() == '\n')
            file.ignore();
        if (file.peek() == ';')
        {
            file >> dispose_char;
            break;
        }
        int a, b;
        file >> a >> b;
        path_connections.push_back(Path_Connection{&path_nodes[a], &path_nodes[b]});
    }
    file.close();
}

POINT Level_01::world_to_screen(const POINT_DECIMAL &coord)
{
    POINT ret;
    ret.x = coord.x;
    ret.y = coord.y;
    ret.x -= camera_position.x;
    ret.y -= camera_position.y;
    ret.x *= camera_zoom;
    ret.y *= camera_zoom;
    return ret;
}

POINT_DECIMAL Level_01::screen_to_world(const POINT &coord)
{
    POINT_DECIMAL ret;
    ret.x = coord.x;
    ret.y = coord.y;
    ret.x /= camera_zoom;
    ret.y /= camera_zoom;
    ret.x += camera_position.x;
    ret.y += camera_position.y;
    return ret;
}

void Level_01::move_camera_to_player(HWND hwnd)
{
    RECT client_rect;
    GetClientRect(hwnd, &client_rect);

    RECT_DECIMAL camera_view;
    camera_view.bottom = client_rect.bottom;
    camera_view.left = 0;
    camera_view.right = client_rect.right;
    camera_view.top = 0;

    camera_view.bottom /= camera_zoom;
    // camera_view.left /= camera_zoom;
    camera_view.right /= camera_zoom;
    // camera_view.top /= camera_zoom;

    double width = camera_view.right;
    double height = camera_view.bottom;

    camera_view.bottom += player.position.y - height / 2;
    camera_view.left += player.position.x - width / 2;
    camera_view.right += player.position.x - width / 2;
    camera_view.top += player.position.y - height / 2;

    camera_position.x = camera_view.left;
    camera_position.y = camera_view.top;
}

void Level_01::update_world_passive()
{
    static double STAMINA_REGEN_VALUE = 0.1;
    player.current_anim_feet.frame_counter++;
    if (player.current_anim_feet.frame_counter == player.current_anim_feet.frames_per_sprite)
    {
        player.current_anim_feet.frame_counter = 0;
        player.current_anim_feet.current_sprite_index = (player.current_anim_feet.current_sprite_index + 1) % player.current_anim_feet.sprites->size();
    }
    if (player.is_slashing)
    {
        player.current_anim_body.frame_counter++;
        if (player.current_anim_body.frame_counter == player.current_anim_body.frames_per_sprite)
        {
            player.current_anim_body.frame_counter = 0;
            player.current_anim_body.current_sprite_index++;
        }
        if (player.current_anim_body.current_sprite_index == player.current_anim_body.sprites->size())
        {
            player.current_anim_body.sprites = &player.body_idle;
            player.current_anim_body.frame_counter = 0;
            player.current_anim_body.frames_per_sprite = 1;
            player.current_anim_body.current_sprite_index = 0;
            player.is_slashing = false;
        }
    }
    else if (player.is_dashing)
    {
        player.current_anim_body.frame_counter++;
        if (player.current_anim_body.frame_counter == player.current_anim_body.frames_per_sprite)
        {
            player.current_anim_body.frame_counter = 0;
            player.current_anim_body.current_sprite_index++;
        }
        if (player.current_anim_body.current_sprite_index == player.current_anim_body.sprites->size())
        {
            player.current_anim_body.sprites = &player.body_idle;
            player.current_anim_body.frame_counter = 0;
            player.current_anim_body.frames_per_sprite = 1;
            player.current_anim_body.current_sprite_index = 0;
            player.is_dashing = false;
        }
    }
    else
    {
        player.current_anim_body.frame_counter++;
        if (player.current_anim_body.frame_counter == player.current_anim_body.frames_per_sprite)
        {
            player.current_anim_body.frame_counter = 0;
            player.current_anim_body.current_sprite_index = (player.current_anim_body.current_sprite_index + 1) % player.current_anim_body.sprites->size();
        }
    }

    if (player.is_dashing)
    {
        player.position.x += player.dash_per_frame_x;
        player.position.y += player.dash_per_frame_y;
    }
    if (player.max_stamina > player.stamina)
    {
        player.stamina += STAMINA_REGEN_VALUE;
        if (player.max_stamina < player.stamina)
            player.stamina = player.max_stamina;
    }
    if (!enemies.in_combat)
    {
        enemies.order_new_positions();
        enemies.step_all_towards_nodes();
    }
    else
    {
        enemies.attack();
        for (Enemy &e : enemies.alive_enemies)
        {
            if (e.fired_bullet == false)
                continue;
            e.fired_bullet = false;
            PlaySound(TEXT("resources/ak47.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Bullet_Trail new_bullet;
            new_bullet.begin_point = e.position;
            new_bullet.end_point = {e.position.x + e.rotation_vector.x, e.position.y + e.rotation_vector.y};
            new_bullet.calculate_end_point(high_rects);
            bullets_in_air.push_back(new_bullet);
            if (did_bullet_hit(e, player, high_rects))
                player.health_points -= 10;
        }
    }

    for (int i = 0; i < bullets_in_air.size(); ++i)
    {
        bullets_in_air[i].current_frame++;
        if (bullets_in_air[i].current_frame == bullets_in_air[i].FRAMES_PER_ANIM)
        {
            bullets_in_air[i].current_frame = 0;
            bullets_in_air[i].current_width--;
            if (bullets_in_air[i].current_width == 0)
            {
                bullets_in_air.erase(bullets_in_air.begin() + i);
                i--;
            }
        }
    }

    player_position_history.push(player.position);
    bool is_seen = false;
    Entity player_past;
    player_past.position = player_position_history.front();
    for (Enemy &e : enemies.alive_enemies)
    {
        if (does_character_see_character(e, player_past, high_rects))
        {
            is_seen = true;
            break;
        }
    }
    enemies.player_percieved_pos = player_past.position;
    enemies.in_combat = is_seen;
    player_position_history.pop();

    if (player.health_points <= 0)
    {
        fail_level_end_game();
    }
    if (enemies.alive_enemies.size() == 0 && enemies.dead_enemies.size() == 0)
    {
        finish_level_end_game();
    }

    enemies.increment_dead_enemies_anims();
}

/* HELPER FUNCTIONS FOR CONTROL */
void Level_01::player_WASD()
{
    static const double SPEED = 3;
    if (player.is_dashing)
        return;
    POINT_DECIMAL saved = player.rotation_vector;
    player.rotation_vector = {0, 0};
    if (GetAsyncKeyState('W') & 0x8001)
    {
        player.position.y -= SPEED;
        if (inside_any_object(player))
            player.position.y += SPEED;
        else
            player.rotation_vector.y -= 1;
    }
    if (GetAsyncKeyState('S') & 0x8001)
    {
        player.position.y += SPEED;
        if (inside_any_object(player))
            player.position.y -= SPEED;
        else
            player.rotation_vector.y += 1;
    }
    if (GetAsyncKeyState('A') & 0x8001)
    {
        player.position.x -= SPEED;
        if (inside_any_object(player))
            player.position.x += SPEED;
        else
            player.rotation_vector.x -= 1;
    }
    if (GetAsyncKeyState('D') & 0x8001)
    {
        player.position.x += SPEED;
        if (inside_any_object(player))
            player.position.x -= SPEED;
        else
            player.rotation_vector.x += 1;
    }
    if (player.rotation_vector.x == 0 && player.rotation_vector.y == 0)
    {
        player.is_running = false;
        player.current_anim_feet.frames_per_sprite = 1;
        player.current_anim_feet.frame_counter = 0;
        player.current_anim_feet.current_sprite_index = 0;
        player.current_anim_feet.sprites = &player.feet_idle;
        player.current_anim_feet.sprites = &player.feet_idle;
        player.rotation_vector = saved;
        return;
    }
    if (!player.is_running)
    {
        player.current_anim_feet.frames_per_sprite = player.frames_per_sprite_running_legs;
        player.current_anim_feet.frame_counter = 0;
        player.current_anim_feet.current_sprite_index = 0;
        player.current_anim_feet.sprites = &player.feet_forward;
    }
    player.is_running = true;
}

void Level_01::player_DASH(HWND hwnd)
{
    static int DASH_COST = 25;
    static double DASH_LIMIT = 100;
    if ((GetAsyncKeyState(VK_LBUTTON) & 0x8001) && (!player.is_dashing) && (!player.is_slashing))
    {
        if (player.stamina < DASH_COST)
            return;
        POINT mouse_screen;
        RECT client_rect;
        GetClientRect(hwnd, &client_rect);
        GetCursorPos(&mouse_screen);
        ScreenToClient(hwnd, &mouse_screen);
        if (mouse_screen.x < 0 || mouse_screen.y < 0 || mouse_screen.x > client_rect.right || mouse_screen.y > client_rect.bottom)
            return;
        POINT_DECIMAL new_pos = screen_to_world(mouse_screen);
        POINT_DECIMAL direction_vector = {new_pos.x - player.position.x, new_pos.y - player.position.y};
        double distance = sqrt(direction_vector.x * direction_vector.x + direction_vector.y * direction_vector.y);
        if (distance > DASH_LIMIT)
        {
            direction_vector.x *= DASH_LIMIT / distance;
            direction_vector.y *= DASH_LIMIT / distance;
            new_pos = {player.position.x + direction_vector.x, player.position.y + direction_vector.y};
        }
        Entity dummy;
        dummy.hitbox_width = player.hitbox_width;
        dummy.hitbox_height = player.hitbox_height;
        dummy.position = new_pos;
        dummy.rotation_vector = {-player.rotation_vector.x, -player.rotation_vector.y};
        if (inside_any_object(dummy))
            return;
        if (are_characters_blocked_by_walls(dummy, player, high_rects))
            return;
        player.dash_per_frame_x = direction_vector.x / player.body_dash.size() / player.frames_per_sprite_dashing;
        player.dash_per_frame_y = direction_vector.y / player.body_dash.size() / player.frames_per_sprite_dashing;
        if (player.dash_per_frame_x == 0 && player.dash_per_frame_y == 0)
            return;
        player.stamina -= DASH_COST;
        player.rotation_vector = direction_vector;
        player.is_dashing = true;
        player.current_anim_body.frames_per_sprite = player.frames_per_sprite_dashing;
        player.current_anim_body.frame_counter = 0;
        player.current_anim_body.current_sprite_index = 0;
        player.current_anim_body.sprites = &player.body_dash;
    }
}

void Level_01::react_to_controls(HWND hwnd)
{
    player_WASD();
    player_DASH(hwnd);
    if ((GetAsyncKeyState(VK_SPACE) & 0x8001) && (!player.is_dashing) && (!player.is_slashing))
    {
        enemies.detect_death_for_player_slash(player);
        player.is_slashing = true;
        player.current_anim_body.frames_per_sprite = player.frames_per_sprite_slashing;
        player.current_anim_body.frame_counter = 0;
        player.current_anim_body.current_sprite_index = 0;
        player.current_anim_body.sprites = &player.body_attack;
    }
}

bool Level_01::inside_any_object(const Entity &e)
{
    for (auto &i : high_rects)
        if (inside_object(e, i))
            return true;
    for (auto &i : low_rects)
        if (inside_object(e, i))
            return true;
    return false;
}

bool Level_01::inside_object(const Entity &e, const RECT &r)
{
    RECT entity_rect;
    entity_rect.top = e.position.y - e.hitbox_height / 2;
    entity_rect.bottom = e.position.y + e.hitbox_height / 2;
    entity_rect.left = e.position.x - e.hitbox_width / 2;
    entity_rect.right = e.position.x + e.hitbox_width / 2;

    if (entity_rect.top >= r.bottom)
        return false;
    if (entity_rect.bottom <= r.top)
        return false;
    if (entity_rect.left >= r.right)
        return false;
    if (entity_rect.right <= r.left)
        return false;
    return true;
}

void Level_01::render(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    HDC hdcmem = CreateCompatibleDC(hdc);
    RECT rect;
    GetClientRect(hwnd, &rect);
    HBITMAP hbmpmem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
    HBITMAP hbmpstari = (HBITMAP)SelectObject(hdcmem, hbmpmem);

    draw_current_frame(hdcmem);

    BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcmem, 0, 0, SRCCOPY);

    SelectObject(hdcmem, hbmpstari);
    DeleteDC(hdcmem);
    DeleteObject(hbmpmem);
    ReleaseDC(hwnd, hdc);
}

void Level_01::draw_HUD(HDC hdc)
{
    static int PIXELS_PER_POINT = 1;
    static int PIXELS_HEIGHT = 10;
    HBITMAP hbmpmem = (HBITMAP)GetCurrentObject(hdc, OBJ_BITMAP);
    BITMAP bmp_data;
    GetObject(hbmpmem, sizeof(bmp_data), &bmp_data);
    int screen_width = bmp_data.bmWidth;
    int screen_height = bmp_data.bmHeight;
    RECT rect;
    HBRUSH brush;
    // draw current health
    int health_width = player.health_points * PIXELS_PER_POINT;
    brush = CreateSolidBrush(RGB(0, 0, 255));
    rect.right = bmp_data.bmWidth - 30;
    rect.top = bmp_data.bmHeight - 30 - PIXELS_HEIGHT - 10 - PIXELS_HEIGHT;
    rect.bottom = rect.top + PIXELS_HEIGHT;
    rect.left = rect.right - health_width;
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
    // draw current stamina
    int stamina_width = player.stamina * PIXELS_PER_POINT;
    brush = CreateSolidBrush(RGB(0, 255, 0));
    rect.top = bmp_data.bmHeight - 30 - PIXELS_HEIGHT;
    rect.bottom = rect.top + PIXELS_HEIGHT;
    rect.left = rect.right - stamina_width;
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
    // draw detection marker
    bool seen = enemies.in_combat;
    if (seen)
        brush = CreateSolidBrush(RGB(255, 0, 0));
    else
        brush = CreateSolidBrush(RGB(0, 255, 0));
    rect.top = bmp_data.bmHeight - 30 - PIXELS_HEIGHT - 10 - PIXELS_HEIGHT - 10 - PIXELS_HEIGHT;
    rect.bottom = rect.top + PIXELS_HEIGHT;
    rect.left = rect.right - PIXELS_HEIGHT;
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
    // write out how many enemies left:
    std::string to_write = "Enemies left: ";
    to_write += std::to_string(enemies.alive_enemies.size());
    TextOut(hdc, 0, 0, to_write.c_str(), to_write.size());
}

void Level_01::draw_current_frame(HDC hdc)
{
    /* DRAW BACKGROUND */
    draw_bitmap_scaled(hdc, map_image, -camera_position.x * camera_zoom,
                       -camera_position.y * camera_zoom, camera_zoom * map_scale);
    /* DRAW PLAYER */
    POINT player_screen = world_to_screen(player.position);
    draw_transformed_texture(hdc, player_screen.x, player_screen.y,
                             (*player.current_anim_feet.sprites)[player.current_anim_feet.current_sprite_index].hbmp,
                             (*player.current_anim_feet.sprites)[player.current_anim_feet.current_sprite_index].hbmp_mask,
                             player.rotation_vector,
                             camera_zoom / 10);
    draw_transformed_texture(hdc, player_screen.x, player_screen.y,
                             (*player.current_anim_body.sprites)[player.current_anim_body.current_sprite_index].hbmp,
                             (*player.current_anim_body.sprites)[player.current_anim_body.current_sprite_index].hbmp_mask,
                             player.rotation_vector,
                             camera_zoom / 10);
    /* DRAW ALIVE ENEMIES */
    for (Enemy &e : enemies.alive_enemies)
    {
        POINT e_screen = world_to_screen(e.position);
        draw_transformed_texture(hdc, e_screen.x, e_screen.y,
                                 (*e.current_anim_feet.sprites)[e.current_anim_feet.current_sprite_index].hbmp,
                                 (*e.current_anim_feet.sprites)[e.current_anim_feet.current_sprite_index].hbmp_mask,
                                 e.rotation_vector,
                                 camera_zoom / 10);
        draw_transformed_texture(hdc, e_screen.x, e_screen.y,
                                 (*e.current_anim_body.sprites)[e.current_anim_body.current_sprite_index].hbmp,
                                 (*e.current_anim_body.sprites)[e.current_anim_body.current_sprite_index].hbmp_mask,
                                 e.rotation_vector,
                                 camera_zoom / 10);
    }
    /* DRAW DEAD ENEMIES */
    for (Enemy &e : enemies.dead_enemies)
    {
        POINT e_screen = world_to_screen(e.position);
        draw_transformed_texture(hdc, e_screen.x, e_screen.y,
                                 (*e.current_anim_feet.sprites)[e.current_anim_feet.current_sprite_index].hbmp,
                                 (*e.current_anim_feet.sprites)[e.current_anim_feet.current_sprite_index].hbmp_mask,
                                 e.rotation_vector,
                                 camera_zoom / 10);
        draw_transformed_texture(hdc, e_screen.x, e_screen.y,
                                 (*e.current_anim_body.sprites)[e.current_anim_body.current_sprite_index].hbmp,
                                 (*e.current_anim_body.sprites)[e.current_anim_body.current_sprite_index].hbmp_mask,
                                 e.rotation_vector,
                                 camera_zoom / 10);
    }
    /* DRAW BULLETS */
    for (Bullet_Trail &bullet : bullets_in_air)
    {
        POINT begin_screen = world_to_screen(bullet.begin_point);
        POINT end_screen = world_to_screen(bullet.end_point);
        // DRAW THE LINE
        HPEN pen = (HPEN)CreatePen(PS_SOLID, bullet.current_width, RGB(150, 150, 150));
        pen = (HPEN)SelectObject(hdc, pen);

        MoveToEx(hdc, begin_screen.x, begin_screen.y, NULL);
        LineTo(hdc, end_screen.x, end_screen.y);
        MoveToEx(hdc, 0, 0, NULL);

        pen = (HPEN)SelectObject(hdc, pen);
        DeleteObject(pen);
    }
    draw_HUD(hdc);
}

void Level_01::run(HWND hwnd)
{
    static const DWORD MS_PER_FRAME = 1000 / 120;

    DWORD start_time = GetTickCount();
    react_to_controls(hwnd);
    update_world_passive();
    move_camera_to_player(hwnd);
    render(hwnd);
    while (GetTickCount() - start_time < MS_PER_FRAME)
        continue;
}
LRESULT Level_01::winproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        hCursorCustom = (HCURSOR)LoadImage(NULL, "resources/gameplay_cursor.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
        SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursorCustom);
        break;
    default: /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}
