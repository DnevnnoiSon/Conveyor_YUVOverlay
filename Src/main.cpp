//====================================================//
//    Наложение изображения (BMP) на видео (YUV420)   //
//====================================================//
#include "YUVConverter.h"
#include "BMPReader.h"

#include <iostream>
#include <filesystem>

using namespace std;

int main()
{
    cout << "Текущая директория: " << filesystem::current_path() << endl;


    string file_name = "input.bmp";
// 1. Выгрузка BMP:
    BMPReader::BMPImage bmp = BMPReader::loadBMPImage(file_name);

// 2. Конвертация BMP --> YUV420:
    YUVConverter::YUVImage yuv = YUVConverter::BMPConvert(bmp);
// Проверка конвертации:

// 3. Добавление в видео-поток:

    return 0;
}

