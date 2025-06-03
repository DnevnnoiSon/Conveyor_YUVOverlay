#include <stdexcept>
#include <iostream>

#include "YUVOverlay.h"

#define LIMIT_YUVFRAME_COUNT 100000

YUVOverlay::YUVOverlay(const std::string& outputPath) {
    outputStream.open(outputPath, std::ios::binary | std::ios::out);
    if(!outputStream) {
        throw std::runtime_error("Failed to open output file: " + outputPath);
    }
}

YUVOverlay::~YUVOverlay() {
    if(outputStream.is_open()) {
        outputStream.close();
        std::cout << "В видео поток записано: " << YUVframeCounter << " bmp" << std::endl;
    }
}


void YUVOverlay::add_YUVframe(const YUVConverter::YUVImage &yuv)
{
    if(!outputStream.is_open()) {
        throw std::runtime_error("Ошибка открытия выходного потока");
    }

    // Установка/Проверка эталонного кадра
    if(YUVframeCounter == 0) { // первый кадр - эталонный
        frame_width = yuv.width;
        frame_height = yuv.height;
    }
    else{
        if(frame_width != yuv.width || frame_height != yuv.height) {
            throw std::runtime_error("Разрешение кадра не соответствует первому кадру!");
        }
    }

    //расчет размера YUV420:
    const size_t y_size = static_cast<size_t>(yuv.width) * yuv.height;
    const size_t uv_size = y_size / 4;
    const size_t expected_size = y_size + 2 * uv_size;

    //проверка соотв. размера:
    if (yuv.YUV.size() != expected_size) {
        throw std::invalid_argument("Недопустимый размер фрейма YUV. Ожидается: " +
        std::to_string(expected_size) +
        " Текущий размер: " +
        std::to_string(yuv.YUV.size()));
    }

    // Прямая запись данных в бинарном режиме:
    outputStream.write(reinterpret_cast<const char*>(yuv.YUV.data()),
                       static_cast<std::streamsize>(yuv.YUV.size()));

    if(YUVframeCounter < LIMIT_YUVFRAME_COUNT){
        YUVframeCounter++;
    }
}





