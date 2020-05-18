# TODO: agsmith95 19 May 2020
# TODO: add options to build only final target

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
        shaders_attributes.cpp
)
target_link_libraries(
        ${SHADERS_ATTR_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
)
# "shaders library" part
set(SHADERS_USE_LIB_EXE shaders_use_lib)
add_definitions(-DSHADERS_DIRECTORY="${SHADERS_DIRECTORY}")
add_executable(
        ${SHADERS_USE_LIB_EXE}
        shaders_using_lib.cpp
)
target_link_libraries(
        ${SHADERS_USE_LIB_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
)

if(MSVC)
    target_compile_options(${SHADERS_EXE} PRIVATE /W4 /WX)
    target_compile_options(${SHADERS_ATTR_EXE} PRIVATE /W4 /WX)
    target_compile_options(${SHADERS_USE_LIB_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${SHADERS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(${SHADERS_ATTR_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(${SHADERS_USE_LIB_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()