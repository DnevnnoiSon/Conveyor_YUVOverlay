cmake_minimum_required(VERSION 3.14)

project(YUVOverlay LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========== Файловая структура проекта ==========
set(SOURCES
    Src/main.cpp
    Src/BMPReader.cpp
    Src/YUVConverter.cpp
    Src/YUVOverlay.cpp
)

set(HEADERS
    Inc/BMPReader.h
    Inc/YUVConverter.h
    Inc/YUVOverlay.h
)

# Автоматический сбор файлов из Resources:
file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/*"
)

foreach(file ${SOURCES} ${HEADERS})
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file})
        message(FATAL_ERROR "File not found: ${CMAKE_CURRENT_SOURCE_DIR}/${file}")
    endif()
endforeach()

# Исполняемый файл:
add_executable(YUVOverlay ${SOURCES} ${HEADERS})


# Подключение заголовков:
target_include_directories(YUVOverlay PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

# Копирование ресурсов в выходную директорию:
add_custom_command(TARGET YUVOverlay POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources
        $<TARGET_FILE_DIR:YUVOverlay>
    COMMENT "Copying resources to output directory"
)


# Линковка с системными библиотеками:
find_package(Threads REQUIRED)
target_link_libraries(YUVOverlay PRIVATE
    Threads::Threads
)

# Установка только RUNTIME для исполняемого файла:
include(GNUInstallDirs)
install(TARGETS YUVOverlay
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${RESOURCES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/YUVOverlay
)
