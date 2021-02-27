# rotate transform
set(ROTATE_TRANSFORM rotate_transform_ex1)
add_executable(
    ${ROTATE_TRANSFORM}
    transformations_ex1.cpp
)
target_link_libraries(
    ${ROTATE_TRANSFORM}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${ROTATE_TRANSFORM} PRIVATE /W4 /WX)
else()
    target_compile_options(${ROTATE_TRANSFORM} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# second container
set(SECOND_CONTAINER second_container_ex2)
add_executable(
    ${SECOND_CONTAINER}
    transformations_ex2.cpp
)
target_link_libraries(
    ${SECOND_CONTAINER}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${SECOND_CONTAINER} PRIVATE /W4 /WX)
else()
    target_compile_options(${SECOND_CONTAINER} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
