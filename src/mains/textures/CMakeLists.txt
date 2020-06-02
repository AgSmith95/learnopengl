# FINAL
set(TEXTURES_EXE textures)
add_executable(
        ${TEXTURES_EXE}
        textures.cpp
)
target_link_libraries(
        ${TEXTURES_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
)
if(MSVC)
    target_compile_options(${TEXTURES_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${TEXTURES_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
