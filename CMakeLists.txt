cmake_minimum_required(VERSION 3.13)
project(learnopengl)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL 3.3 REQUIRED)

add_subdirectory(external_libs)
add_subdirectory(src)
