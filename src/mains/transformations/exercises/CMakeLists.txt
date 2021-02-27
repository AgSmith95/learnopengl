# rotate transform
set(ROTATE_TRANSFORM rotate_transform_ex1)
add_executable(
    ${ROTATE_TRANSFORM}
    transformations_ex1.cpp
)
target_link_libraries(
    ${ROTATE_TRANSFORM}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${ROTATE_TRANSFORM} PRIVATE /W4 /WX)
else()
    target_compile_options(${ROTATE_TRANSFORM} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
