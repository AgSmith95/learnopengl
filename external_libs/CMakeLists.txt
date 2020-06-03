cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# cloning dependencies
find_package(Git REQUIRED)

# LIBS_DIR
set(
    LIBS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# GLFW 3.3
# git clone glfw branch 3.3-stable
set(
    GLFW33_COMMIT
    0ac01338
#    d9924933
)
message(
    "CHECKING OUT 'GLFW' 3.3-stable ${GLFW33_COMMIT}"
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} clone
    -b 3.3-stable https://github.com/glfw/glfw
    ${LIBS_DIR}/glfw
)
# git reset to correct branch/commit
execute_process(
    WORKING_DIRECTORY ${LIBS_DIR}/glfw
    COMMAND ${GIT_EXECUTABLE} reset --hard ${GLFW33_COMMIT}
)

# do not build GLFW-related stuff
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF)
add_subdirectory(glfw)
# GLFW 3.3

# stb
message(
    "CHECKING OUT 'stb' 3.3-stable f54acd4"
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} clone
    https://github.com/nothings/stb.git
    ${LIBS_DIR}/stb/tmp
)
execute_process(
    WORKING_DIRECTORY ${LIBS_DIR}/stb/tmp
    COMMAND ${GIT_EXECUTABLE} reset --hard f54acd4
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
#target_sources(stb INTERFACE ${STB_HEADER_FILES})
# https://github.com/nothings/stb.git
# stb

add_subdirectory(glad)
