cmake_minimum_required(VERSION 3.13)
project(learnopengl)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL 3.3 REQUIRED)

set(
        LIBS_DIR
        ${PROJECT_SOURCE_DIR}/libs
)

add_subdirectory(libs)
include_directories(libs/glfw/include/)

add_subdirectory(src)
