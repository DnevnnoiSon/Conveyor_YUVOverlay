#ifndef BMPREADER_H
#define BMPREADER_H

#include <string>
#include <vector>
#include <cstdint>
//============================//
//  МОДУЛЬ ЧТЕНИЯ BMP ФАЙЛА   //
//============================//

#define  HEADER_SIZE  54

class BMPReader
{
public:
// Структурв выгруженных BMP данных.
    struct BMPImage {
        int width = 0;
        int height = 0;
        std::vector<uint8_t> rgb_data;
    };
    static BMPImage loadBMPImage(const std::string& filepath);
};

#endif // BMPREADER_H
