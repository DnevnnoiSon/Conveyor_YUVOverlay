#include "YUVConverter.h"
#include "BMPReader.h"

//#include <iostream>
//#include <filesystem>

using namespace std;
/* Наложение изображения (BMP) на видео (YUV420) */



int main()
{
// 1. Вычитывание BMP:
    //cout << "Текущая директория: " << filesystem::current_path() << endl;
    string file_name = "input.bmp";
    BMPReader::BMPImage bmp = BMPReader::load(file_name);
// 2. Конвертация BMP --> YUV420
    YUVConverter BMPConvert(bmp);

    return 0;
}

