//==========================================================//
//    Наложение изображения (BMP) на видео-поток (YUV420)   //
//==========================================================//
#include <iostream>
#include <filesystem>

#include "YUVConverter.h"
#include "BMPReader.h"

using namespace std;

int main()
{
    cout << "Текущая директория: " << filesystem::current_path() << endl;

    string file_name = "input.bmp";
// 1. Выгрузка BMP:
    BMPReader::BMPImage bmp = BMPReader::loadBMPImage(file_name);

// 2. Конвертация: BMP --> YUV420
    YUVConverter::YUVImage yuv = YUVConverter::BMPConvert(bmp);
// Проверка конвертации:

// 3. Добавление в видео-поток:
    //.... потом сам допишу, пусть будет назваться YUVOverlay();

    return 0;
}

