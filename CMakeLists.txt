cmake_minimum_required(VERSION 3.10.0)
project(SDLShooter VERSION 0.1.0 LANGUAGES C CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    # Visual Studio 编译器
    add_compile_options(/W4 /WX)
else()
    # GCC 或 Clang 编译器
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE})

# 跨平台的简单写法
# 查找并载入预设
find_package(SDL2 REQUIRED)

# if (WIN32)
#     include_directories("C:/SDL2/include")
# elseif(APPLE)
#     include_directories("/opt/homebrew/Cellar/sdl2/2.32.8/include/SDL2")
#     link_directories("/opt/homebrew/Cellar/sdl2/2.32.8/lib")
#     link_directories("/opt/homebrew/Cellar/sdl2_image/2.8.8/lib")
#     link_directories("/opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/lib")
#     link_directories("/opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib")
# elseif(UNIX)
#     include_directories("/usr/include/SDL2")
# endif()

# 添加可执行文件
add_executable(${TARGET} main.cpp)

# 链接库
target_link_libraries(${TARGET} ${SDL2_LIBRARIES})
