# FINAL
set(COLORS_EXE colors)
add_executable(
    ${COLORS_EXE}
    colors.cpp
)
target_link_libraries(
    ${COLORS_EXE}
    OpenGL::GL
    glfw
    glm
    glad
    learnopengl_helpers
    shaders_lib
    camera_lib
    stb
)
if(MSVC)
    target_compile_options(${COLORS_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${COLORS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
