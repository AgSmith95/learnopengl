project(glad)

add_library(
        glad
        src/glad.c
)

target_include_directories(
        glad
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE src
)
