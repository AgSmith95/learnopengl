# Exercise 1: light cube color
set(MATERIALS_EX1_EXE materials_ex1)
add_executable(
    ${MATERIALS_EX1_EXE}
    materials_ex1.cpp
)
target_link_libraries(
    ${MATERIALS_EX1_EXE}
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
    target_compile_options(${MATERIALS_EX1_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${MATERIALS_EX1_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
