# FINAL
set(BL_EX1_EXE basic_lighting_ex1)
add_executable(
    ${BL_EX1_EXE}
    bl_ex1.cpp
)
target_link_libraries(
    ${BL_EX1_EXE}
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
    target_compile_options(${BL_EX1_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${BL_EX1_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
