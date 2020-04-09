cmake_minimum_required(VERSION 3.15)
project(opengl_tutorials)

set(CMAKE_CXX_STANDARD 17)

#find_package(OpenGL REQUIRED)

add_subdirectory(libs)
include_directories(libs/glfw/include/)

get_property(
        incdir
        DIRECTORY
        PROPERTY INCLUDE_DIRECTORIES
        )
message("TOP " ${incdir})

add_subdirectory(src)
