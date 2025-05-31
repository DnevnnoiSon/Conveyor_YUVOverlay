#include <stdexcept>
#include <algorithm>

#include "YUVConverter.h"

namespace {
    struct YUVValues{
        int Y;
        int U;
        int V;
    };
// Преобразование RGB в YUV:
    YUVValues rgb_to_yuv(uint8_t R, uint8_t G, uint8_t B) {
        return {
            ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16,   //->Y
            ((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128, //->U
            ((112 * R - 94 * G - 18 * B + 128) >> 8) + 128   //->V
        };
    }
}

// Оптимальный способ конвертации:
YUVConverter::YUVImage YUVConverter::BMPConvert(const BMPReader::BMPImage& bmp)
{
    if (bmp.width % 2 != 0 || bmp.height % 2 != 0) {
        throw std::runtime_error("Ошибка размера изображения");
    }
// Рассчет размеров плоскостей:
    const int uv_width = bmp.width / 2;
    const int uv_height = bmp.height / 2;

    const int y_plane_size = bmp.width * bmp.height ;
    const int uv_plane_size = uv_width * uv_height;

    YUVImage image = {
        bmp.width,
        bmp.height,
        std::vector<uint8_t>(y_plane_size + 2 * uv_plane_size) // Y + U + V
    };
// Формирование результирующего буфера через указатели:
    uint8_t *pY = image.YUV.data();
    uint8_t *pU = pY + y_plane_size;
    uint8_t *pV = pU + uv_plane_size;
// Буферы для сборки:
    std::vector<uint16_t> U_sum(uv_plane_size, 0);
    std::vector<uint16_t> V_sum(uv_plane_size, 0);

    const uint8_t* rgb = bmp.rgb_data.data();
    // x_pixel, y_pixel - оси
    for (int y_pixel = 0; y_pixel < bmp.height; y_pixel++) {
        for (int x_pixel = 0; x_pixel < bmp.width; x_pixel++) {
            const int rgb_idx = (y_pixel * bmp.width + x_pixel) * 3;

            auto yuv = rgb_to_yuv(
            rgb[rgb_idx],      // R
            rgb[rgb_idx + 1],  // G
            rgb[rgb_idx + 2]); // B

         // Запись Y с проверки диапозона:
            pY[y_pixel * bmp.width + x_pixel] = std::clamp(yuv.Y, 0, 255);

            const int block_idx = (y_pixel / 2) * uv_width + (x_pixel / 2);
         // Ограничение в диапазоне: [min_val, max_val] + суммирование U/V
            U_sum[block_idx] += std::clamp(yuv.U, 0, 255);
            V_sum[block_idx] += std::clamp(yuv.V, 0, 255);
        }
    }
// Усреднение и запись UV компонент:
    for (int idx = 0; idx < uv_plane_size; idx++) {
    // Округление:
        pU[idx] = (U_sum[idx] + 2) / 4;
        pV[idx] = (V_sum[idx] + 2) / 4;
    }
    return image;
}


