cmake_minimum_required(VERSION 3.10)
project(Rasterizer)

list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\Eigen3")

list(APPEND CMAKE_PREFIX_PATH "C:\\Software\\opencv\\build")

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# include_directories(/usr/local/include)

add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp)
target_link_libraries(Rasterizer ${OpenCV_LIBRARIES} Eigen3::Eigen)
