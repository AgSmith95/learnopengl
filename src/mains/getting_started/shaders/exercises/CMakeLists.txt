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

# horizontal offset
set(HORIZONTAL_OFFSET shaders_horizontal_offset)
add_executable(
        ${HORIZONTAL_OFFSET}
        2_horizontal_offset.cpp
)
target_link_libraries(
        ${HORIZONTAL_OFFSET}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
)
if(MSVC)
    target_compile_options(${HORIZONTAL_OFFSET} PRIVATE /W4 /WX)
else()
    target_compile_options(${HORIZONTAL_OFFSET} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# vertex out fragment in
set(VSH_OUT_FSH_IN 3_vertex_out_fragment_in)
add_executable(
        ${VSH_OUT_FSH_IN}
        3_vertex_out_fragment_in.cpp
)
target_link_libraries(
        ${VSH_OUT_FSH_IN}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
)
if(MSVC)
    target_compile_options(${VSH_OUT_FSH_IN} PRIVATE /W4 /WX)
else()
    target_compile_options(${VSH_OUT_FSH_IN} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
