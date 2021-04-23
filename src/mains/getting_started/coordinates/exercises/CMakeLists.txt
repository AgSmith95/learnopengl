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

# View matrix tweaks
set(VIEW_MATR coordinates_ex2)
add_executable(
    ${VIEW_MATR}
    coordinates_ex2.cpp
)
target_link_libraries(
    ${VIEW_MATR}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${VIEW_MATR} PRIVATE /W4 /WX)
else()
    target_compile_options(${VIEW_MATR} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Rotate only 1 cube
set(ROTATE_ONE coordinates_ex3)
add_executable(
    ${ROTATE_ONE}
    coordinates_ex3.cpp
)
target_link_libraries(
    ${ROTATE_ONE}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${ROTATE_ONE} PRIVATE /W4 /WX)
else()
    target_compile_options(${ROTATE_ONE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
