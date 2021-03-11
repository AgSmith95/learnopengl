# FPS Camera
set(FPS_CAMERA camera_ex1)
add_executable(
    ${FPS_CAMERA}
    camera_ex1.cpp
)
target_link_libraries(
    ${FPS_CAMERA}
    OpenGL::GL
    glfw
    glm
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${FPS_CAMERA} PRIVATE /W4 /WX)
else()
    target_compile_options(${FPS_CAMERA} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
