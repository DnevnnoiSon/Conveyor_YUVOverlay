//==========================================================//
//    Наложение изображения (BMP) на видео-поток (YUV420)   //
//==========================================================//
#include <iostream>
#include <filesystem>

#include <vector>

#include "YUVConverter.h"
#include "BMPReader.h"

int main()
{
//главный поток
    std::cout << "Текущая директория: " << std::filesystem::current_path() << std::endl;
    std::string path = "../../Resources";

// Вектор для новых файлов:
    std::vector<std::string> BMPFiles;

// Начальное сканирование папки:
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".bmp") {  
            BMPFiles.emplace_back(entry.path().filename());
        }
    }

//Последовательная конвертация:
    for(const auto &el : BMPFiles) {
    /// 1. Выгрузка BMP:
        BMPReader::BMPImage bmp = BMPReader::loadBMPImage(el);
    /// 2. Конвертация: BMP --> YUV420
        YUVConverter::YUVImage yuv = YUVConverter::BMPConvert(bmp);
    /// 3. Добавление в видео-поток:
        //YUVOverlay(yuv);
    }

    return 0;
}

