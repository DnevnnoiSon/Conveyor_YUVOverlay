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
/**
* @brief BMPImage - формат BMP */
    struct BMPImage {
        int width = 0;
        int height = 0;
        std::vector<uint8_t> rgb_data;
    };
 /**
* @brief Выгрузка изображения: BMP --> YUV
* @arg string filepath - путь к BMP файлу
* @return  BMPImage - формат BMP */
    static BMPImage loadBMPImage(const std::string& filepath);

  //  static checkBMPFile
};

#endif // BMPREADER_H
