cmake_minimum_required(VERSION 3.10.0)
project(SDLShooter VERSION 0.1.0 LANGUAGES C CXX)


if (WIN32)
    include_directories("C:/SDL2/include")
elseif(APPLE)
    include_directories("/opt/homebrew/Cellar/sdl2/2.32.8/include/SDL2")
    link_directories("/opt/homebrew/Cellar/sdl2/2.32.8/lib")
    link_directories("/opt/homebrew/Cellar/sdl2_image/2.8.8/lib")
    link_directories("/opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/lib")
    link_directories("/opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib")
elseif(UNIX)
    include_directories("/usr/include/SDL2")
endif()

add_executable(SDLShooter main.cpp)

target_link_libraries(SDLShooter SDL2 SDL2_image sdl2_mixer SDL2_ttf)
