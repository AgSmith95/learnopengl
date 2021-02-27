# FINAL
set(TRANSFORMATIONS_EXE transformations)
add_executable(
    ${TRANSFORMATIONS_EXE}
    transformations.cpp
)
target_link_libraries(
        ${TRANSFORMATIONS_EXE}
        OpenGL::GL
        glfw
        glm
        glad
        learnopengl_helpers
        shaders_lib
        stb
)
if(MSVC)
    target_compile_options(${TRANSFORMATIONS_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${TRANSFORMATIONS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
