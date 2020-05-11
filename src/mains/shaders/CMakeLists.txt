# "uniform location" part
set(SHADERS_EXE shaders_uniform)
add_executable(
        ${SHADERS_EXE}
        shaders.cpp
)
target_link_libraries(
        ${SHADERS_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
)
# "more attributes" part
set(SHADERS_ATTR_EXE shaders_attributes)
add_executable(
        ${SHADERS_ATTR_EXE}
        ${SRC_DIR_CPP_FILES}
        shaders_attributes.cpp
)
target_link_libraries(
        ${SHADERS_ATTR_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
)

if(MSVC)
    target_compile_options(${SHADERS_EXE} PRIVATE /W4 /WX)
    target_compile_options(${SHADERS_ATTR_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${SHADERS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(${SHADERS_ATTR_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()