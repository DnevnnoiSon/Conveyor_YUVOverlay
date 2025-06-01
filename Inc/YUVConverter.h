#ifndef YUVCONVERTER_H
#define YUVCONVERTER_H

#include <vector>
#include <cstdint>

#include"BMPReader.h"
//================================//
//  МОДУЛЬ КОНВЕРТАЦИИ RGB-->YUV  //
//================================//

class YUVConverter {
public:
/**
* @brief UVImage - формат YUV */
    struct YUVImage {
        int width;
        int height;
        std::vector<uint8_t> YUV; //помещение последовательно: Y-U-V
    };
/**
* @brief Конвертация изображения: BMP --> YUV420
* @arg BMPImage - формат BMP
* @return YUVImage - формат YUV */
    static YUVImage BMPConvert(const BMPReader::BMPImage& bmp);

// Добавить проверку конвертации: прогнать через тесты.
// ...
};
#endif // YUVCONVERTER_H
