# Exercise 4: emission map
set(LIGHTING_MAPS_EX4_EXE lighting_maps_ex4)
add_executable(
    ${LIGHTING_MAPS_EX4_EXE}
    lighting_maps_ex4.cpp
)
target_link_libraries(
    ${LIGHTING_MAPS_EX4_EXE}
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
    target_compile_options(${LIGHTING_MAPS_EX4_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${LIGHTING_MAPS_EX4_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
