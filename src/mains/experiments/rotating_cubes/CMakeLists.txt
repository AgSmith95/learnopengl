set(ROTATING_CUBES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
add_definitions(-DROTATING_CUBES_DIR="${ROTATING_CUBES_DIR}")

set(ROTAATING_CUBES rotating_cubes)
add_executable(
    ${ROTAATING_CUBES}
    rotating_cubes.cpp
)
target_link_libraries(
    ${ROTAATING_CUBES}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${ROTAATING_CUBES} PRIVATE /W4 /WX)
else()
    target_compile_options(${ROTAATING_CUBES} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
