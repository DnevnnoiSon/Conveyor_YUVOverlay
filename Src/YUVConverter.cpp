#include <stdexcept>
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
            ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16,
            ((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128,
            ((112 * R - 94 * G - 18 * B + 128) >> 8) + 128
        };
    }
// Ограничение значения в диапазоне: [min_val, max_val]
    int clamp_value(int value, int min_val, int max_val) {
        return (value < min_val) ? min_val : (value > max_val) ? max_val : value;
    }
}

// Оптимальный способ конвертации:
YUVConverter::YUVImage YUVConverter::BMPConvert(const BMPReader::BMPImage& bmp)
{
    int width = bmp.width;
    int height = bmp.height;

    if (width % 2 != 0 || height % 2 != 0) {
        throw std::runtime_error("Ошибка размера изображения");
    }

    const int uv_width = width / 2;
    const int uv_height = height / 2;
    const int y_plane_size = width * height;
    const int uv_plane_size = uv_width * uv_height;

    YUVImage image;
    image.width = width;
    image.height = height;
    image.YUV.resize(y_plane_size + 2 * uv_plane_size);
// Формирование результирующего буфера через указатели:
    uint8_t* Y_ptr = image.YUV.data();
    uint8_t* U_ptr = Y_ptr + y_plane_size;
    uint8_t* V_ptr = U_ptr + uv_plane_size;

    std::vector<uint16_t> U_sum(uv_plane_size, 0);
    std::vector<uint16_t> V_sum(uv_plane_size, 0);

    const uint8_t* rgb = bmp.rgb_data.data();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const int rgb_index = (y * width + x) * 3;
            auto yuv = rgb_to_yuv(rgb[rgb_index], rgb[rgb_index+1], rgb[rgb_index+2]);

            // Запись Y с проверки диапозона:
            Y_ptr[y * width + x] = clamp_value(yuv.Y, 0, 255);

            // Проверка Диапозона U/V и суммирование:
            uint8_t u_val = clamp_value(yuv.U, 0, 255);
            uint8_t v_val = clamp_value(yuv.V, 0, 255);
            const int block_idx = (y / 2) * uv_width + (x / 2);
            U_sum[block_idx] += u_val;
            V_sum[block_idx] += v_val;
        }
    }

// Усреднение и запись UV компонент:
    for (int i = 0; i < uv_plane_size; i++) {
        // Округление:
        U_ptr[i] = (U_sum[i] + 2) / 4;
        V_ptr[i] = (V_sum[i] + 2) / 4;
    }
    return image;
}


