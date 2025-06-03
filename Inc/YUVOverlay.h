#ifndef YUVOVERLAY_H
#define YUVOVERLAY_H

#include <fstream>
#include <string>
#include <vector>

#include "YUVConverter.h"
//===================================//
//   МОДУЛЬ НАЛОЖЕНИЯ В ВИДЕО-ПОТОК  //
//===================================//

class YUVOverlay
{
public:
    YUVOverlay(const std::string& outputPath);

/**
* @brief Добавление YUV в видеопоток
* @arg YUVImage - формат YUV
* @return Нет */
    void add_YUVframe(const YUVConverter::YUVImage &yuv);

    ~YUVOverlay();

/**
* @brief Защита от дурака */
    YUVOverlay(const YUVOverlay&) = delete;
    YUVOverlay& operator=(const YUVOverlay&) = delete;
private:
    std::ofstream outputStream;
    int YUVframeCounter = 0;
 // размерности кадра:
    int frame_width = 0;
    int frame_height = 0;
};

#endif // YUVOVERLAY_H
