#ifndef YUVCONVERTER_H
#define YUVCONVERTER_H

#include <vector>
#include <cstdint>

#include"BMPReader.h"

using namespace std;

class YUVConverter {
public:
    YUVConverter(const BMPReader::BMPImage& bmp);
    struct YUVImage {
        int width;
        int height;
        vector<uint8_t> YUV; //помещение последовательно: Y-U-V
    };
// Получение результата:
    const YUVImage& getResult() const;
private:
// Результат: Сконвертированные данные:
    YUVImage result;
};
#endif // YUVCONVERTER_H
