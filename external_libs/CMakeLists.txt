cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# cloning dependencies
find_package(Git REQUIRED)

# LIBS_DIR
set(
    LIBS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# GLFW 3.3
clone_git(
    ${LIBS_DIR}/glfw
    https://github.com/glfw/glfw
    "3.3-stable"
    "0ac01338"
)

# do not build GLFW-related stuff
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF)
add_subdirectory(${LIBS_DIR}/glfw)
# GLFW 3.3

# stb
clone_git(
    ${LIBS_DIR}/stb/tmp
    https://github.com/nothings/stb.git
    ""
    "f54acd4"
)

copyfiles(
    ${CMAKE_CURRENT_SOURCE_DIR}/stb/tmp
    ${CMAKE_CURRENT_SOURCE_DIR}/stb/include
    "*.h"
)
copyfiles(
    ${CMAKE_CURRENT_SOURCE_DIR}/stb/tmp
    ${CMAKE_CURRENT_SOURCE_DIR}/stb/src
    "*.c"
)

FILE(
    GLOB
    STBLIB_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/stb/src/*.c
)
add_library(
    stb
    ${STBLIB_SRC_FILES}
)
target_include_directories(
    stb
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stb/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/stb/src
)
# stb

# glm
clone_git(
    ${LIBS_DIR}/glm/
    https://github.com/g-truc/glm.git
    ""
    "6347f62261da5be4e27a256e28aef6abc0ba884d"
)
add_subdirectory(${LIBS_DIR}/glm)
# glm

add_subdirectory(glad)
