# FoV aspect ratio tweaks
set(FOV_ASPECT coordinates_ex1)
add_executable(
    ${FOV_ASPECT}
    coordinates_ex1.cpp
)
target_link_libraries(
    ${FOV_ASPECT}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${FOV_ASPECT} PRIVATE /W4 /WX)
else()
    target_compile_options(${FOV_ASPECT} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
