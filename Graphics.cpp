#include "Graphics.h"

void draw_transformed_texture(HDC hdc, int centerX, int centerY, HBITMAP texture,
                              HBITMAP texture_mask = 0, POINT_DECIMAL rotation_vector = {1, 0},
                              double scale = 1)
{
    if (rotation_vector.y == 0)
        rotation_vector.y += 0.0001;
    double d = sqrt(rotation_vector.x * rotation_vector.x + rotation_vector.y * rotation_vector.y);
    double sin = rotation_vector.y / d;
    double cos = rotation_vector.x / d;

    BITMAP bmp_data;
    GetObject(texture, sizeof(bmp_data), &bmp_data);

    POINT paralelogram[3] = {
        {centerX + scale * (-0.5 * bmp_data.bmWidth * cos + 0.5 * bmp_data.bmHeight * sin),
         centerY + scale * (-0.5 * bmp_data.bmWidth * sin - 0.5 * bmp_data.bmHeight * cos)},
        {centerX + scale * (+0.5 * bmp_data.bmWidth * cos + 0.5 * bmp_data.bmHeight * sin),
         centerY + scale * (+0.5 * bmp_data.bmWidth * sin - 0.5 * bmp_data.bmHeight * cos)},
        {centerX + scale * (-0.5 * bmp_data.bmWidth * cos - 0.5 * bmp_data.bmHeight * sin),
         centerY + scale * (-0.5 * bmp_data.bmWidth * sin + 0.5 * bmp_data.bmHeight * cos)}};

    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP bmpStari = (HBITMAP)SelectObject(hdcMem, texture);

    PlgBlt(hdc, paralelogram, hdcMem, 0, 0, bmp_data.bmWidth, bmp_data.bmHeight, texture_mask, 0, 0);

    SelectObject(hdcMem, bmpStari);
    DeleteDC(hdcMem);
}

void load_textures_to_vector_from_folder(std::vector<TEXTURE> &vec, const std::string &folder_path, int count)
{
    for (int i = 0; i < count; ++i)
    {
        std::string bmp = folder_path + "/" + std::to_string(i) + ".bmp";
        std::string bmp_mask = folder_path + "/" + std::to_string(i) + "_mask.bmp";
        TEXTURE t = {
            (HBITMAP)LoadImage(NULL, bmp.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
            (HBITMAP)LoadImage(NULL, bmp_mask.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)};
        vec.push_back(t);
    }
}

void draw_bitmap_scaled(HDC hdc, HBITMAP hbmp, int x, int y, double scale)
{
    BITMAP bmp;
    GetObject(hbmp, sizeof(BITMAP), &bmp);
    HDC hdcmem = CreateCompatibleDC(hdc);
    HBITMAP hbmpmem = (HBITMAP)SelectObject(hdcmem, hbmp);

    StretchBlt(hdc, x, y, scale * bmp.bmWidth, scale * bmp.bmHeight, hdcmem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

    SelectObject(hdcmem, hbmpmem);
    DeleteDC(hdcmem);
}
