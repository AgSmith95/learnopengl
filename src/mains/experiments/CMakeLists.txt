# try new things here
add_definitions(-DSHADERS_DIRECTORY="${SHADERS_DIRECTORY}")

set(EXPERIMENTS experiments)
add_executable(
        ${EXPERIMENTS}
        experiments.cpp
)
target_link_libraries(
        ${EXPERIMENTS}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
)
if(MSVC)
    target_compile_options(${EXPERIMENTS} PRIVATE /W4 /WX)
else()
    target_compile_options(${EXPERIMENTS} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
