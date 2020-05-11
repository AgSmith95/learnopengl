set(HELLO_TRIANGLE_EXE hello_triangle)

add_executable(
        ${HELLO_TRIANGLE_EXE}
        hello_triangle.cpp
)
target_link_libraries(
        ${HELLO_TRIANGLE_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${HELLO_TRIANGLE_EXE})
    target_compile_options(${HELLO_TRIANGLE_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${HELLO_TRIANGLE_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
