//==========================================================//
//    Наложение изображения (BMP) на видео-поток (YUV420)   //
//==========================================================//
#include <iostream>
#include <filesystem>

#include <vector>

#include "BMPReader.h"
#include "YUVConverter.h"
#include "YUVOverlay.h"

int main()
{
//главный поток
    std::cout << "Текущая директория: " << std::filesystem::current_path() << std::endl;
    const std::string resourcePath = "../../Resources";
    const std::string videoStreamFile = "vieostream.yuv";

    YUVOverlay video(videoStreamFile);
// Вектор для новых файлов:
    std::vector<std::string> BMPFiles;

// Начальное сканирование папки:
    for (const auto& entry : std::filesystem::directory_iterator(resourcePath)) {
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
        video.add_YUVframe(yuv);
    }
    return 0;
}

