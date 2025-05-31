#ifndef YUVCONVERTER_H
#define YUVCONVERTER_H

#include <vector>
#include <cstdint>

#include"BMPReader.h"


class YUVConverter {
public:
// Структурв сконвертированных YUV данных.
    struct YUVImage {
        int width;
        int height;
        std::vector<uint8_t> YUV; //помещение последовательно: Y-U-V
    };
    static YUVImage BMPConvert(const BMPReader::BMPImage& bmp);
};
#endif // YUVCONVERTER_H
