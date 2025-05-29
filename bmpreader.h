#ifndef BMPREADER_H
#define BMPREADER_H

#include <string>
#include <vector>
#include <cstdint>
//============================//
//  МОДУЛЬ ЧТЕНИЯ BMP ФАЙЛА   //
//============================//
using namespace std;
class BMPReader
{
public:
    struct BMPImage {
        int width = 0;
        int height = 0;
        vector<uint8_t> rgb_data;
    };
    static BMPImage load(const std::string& filepath);
};

#endif // BMPREADER_H
