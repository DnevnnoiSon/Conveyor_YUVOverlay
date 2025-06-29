#include <fstream>
#include <array>
#include <string.h>

#include "BMPReader.h"

#define HEADER_SIZE 54

BMPReader::BMPImage BMPReader::loadBMPImage(const std::string& filepath)
{
    int width, height;
    short bits_per_pixel;
    int compression;

    std::ifstream file(filepath, std::ios::binary);
    if (!file){ throw std::runtime_error("Ошибка открытия BMP: " + filepath); }

    // Чтение заголовка:
    std::array<char, HEADER_SIZE> header;
    if( !file.read(header.data(), header.size()) ){
        throw std::runtime_error("Некорректный BMP заголовок");
    }
    // Чтение сигнатуры:
    if (header[0] != 'B' || header[1] != 'M') {
        throw std::runtime_error("Некорректная BMP сигнатура");
    }

    // Чтение размерностей:
    memcpy(&width, &header[18], sizeof(int) );
    memcpy(&height, &header[22], sizeof(int) );
    // Проверка формата:
    memcpy(&bits_per_pixel, &header[28], sizeof(short));
    memcpy(&compression, &header[30], sizeof(int));

    if (bits_per_pixel != 24 || compression != 0) {
        throw std::runtime_error("Поддерживаются только 24-битные несжатые BMP");
    }

    // Расчет выравнивания:
    int row_size = (width * 3 + 3) & ~3;
    //int padding = row_size - width * 3;

    // Подготовка изображения:
    BMPImage image;
    image.width = width;
    image.height = height;
    image.rgb_data.resize(width * height * 3);

    std::vector<char> row_buffer(row_size);

    // Чтение данных - [снизу вверх]
    for (int y = height - 1; y >= 0; --y) {
        if (!file.read(row_buffer.data(), row_size)) {
            throw std::runtime_error("Преждевременное окончание BMP");
        }
        uint8_t* dest_row = image.rgb_data.data() + y * width * 3;
        // BGR->RGB:
        for (int x = 0; x < width; ++x) {
            const char* pixel = row_buffer.data() + x * 3;
            dest_row[x*3 + 0] = static_cast<uint8_t>(pixel[2]); // R
            dest_row[x*3 + 1] = static_cast<uint8_t>(pixel[1]); // G
            dest_row[x*3 + 2] = static_cast<uint8_t>(pixel[0]); // B
        }
    }
    return image;
}
