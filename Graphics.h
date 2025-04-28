#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "includes.h"

void draw_transformed_texture(HDC hdc, int centerX, int centerY, HBITMAP texture,
                              HBITMAP texture_mask, POINT_DECIMAL rotation_vector,
                              double scale);

void load_textures_to_vector_from_folder(std::vector<TEXTURE> &vec, const std::string &folder_path, int count);

void draw_bitmap_scaled(HDC hdc, HBITMAP hbmp, int x, int y, double scale);

#endif // GRAPHICS_H
