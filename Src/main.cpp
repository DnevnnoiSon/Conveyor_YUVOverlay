//==========================================================//
//    Наложение изображения (BMP) на видео-поток (YUV420)   //
//==========================================================//
#include <iostream>
#include <filesystem>

#include <vector>
#include <set>


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
    for(const auto &el : BMPFiles){
        std::cout << el << std::endl;
    }

    while(1

    return 0;
}

