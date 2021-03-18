set(CHALLENGE_CUBES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/
    )
add_definitions(-DCHALLENGE_CUBES_DIR="${CHALLENGE_CUBES_DIR}")

set(CHALLENGE_CUBES challenge_cubes)
add_executable(
        ${CHALLENGE_CUBES}
        rotating_challenge_cubes.cpp
)
target_link_libraries(
        ${CHALLENGE_CUBES}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
        stb
        camera_lib
)
if(MSVC)
    target_compile_options(${CHALLENGE_CUBES} PRIVATE /W4 /WX)
else()
    target_compile_options(${CHALLENGE_CUBES} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
