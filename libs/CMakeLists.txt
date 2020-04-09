cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(glfw)

add_subdirectory(glad)
