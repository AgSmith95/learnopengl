# turn triangle upside down
set(UPSIDE_DOWN shaders_upside_down)
add_executable(
        ${UPSIDE_DOWN}
        1_turn_triangle_down.cpp
)
target_link_libraries(
        ${UPSIDE_DOWN}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
)
if(MSVC)
    target_compile_options(${UPSIDE_DOWN} PRIVATE /W4 /WX)
else()
    target_compile_options(${UPSIDE_DOWN} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
