cmake_minimum_required (VERSION 2.8.11)
project (Transformation)


list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\Eigen3")



find_package(Eigen3 REQUIRED)
# include_directories("C:\\Program Files (x86)\\Eigen3\\include")
# include_directories(${EIGEN3_INCLUDE_DIR})
message(${EIGEN3_INCLUDE_DIR})

add_executable (Transformation main.cpp)
target_link_libraries (Transformation Eigen3::Eigen)
