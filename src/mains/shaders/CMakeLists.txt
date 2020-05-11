set(SHADERS_EXE shaders)

add_executable(
        ${SHADERS_EXE}
        ${SRC_DIR_CPP_FILES}
        shaders.cpp
)
target_link_libraries(
        ${SHADERS_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
)

if(MSVC)
    target_compile_options(${SHADERS_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${SHADERS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()