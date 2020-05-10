set(HELLO_TRIANGLE_EXE hello_triangle)
set(SHADERS_EXE shaders)

include_directories(include)

FILE(
        GLOB
        SRC_DIR_CPP_FILES
        "src/*.cpp"
)

# up until changing color in lesson "Shaders"
add_executable(
        ${HELLO_TRIANGLE_EXE}
        mains/hello_triangle.cpp
        ${SRC_DIR_CPP_FILES}
)
target_link_libraries(
        ${HELLO_TRIANGLE_EXE}
        OpenGL::GL
        glfw
        glad
)
# from now on...
# Shaders:
add_executable(
        ${SHADERS_EXE}
        mains/shaders/shaders.cpp
        ${SRC_DIR_CPP_FILES}
)
target_link_libraries(
        ${SHADERS_EXE}
        OpenGL::GL
        glfw
        glad
)
#

if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${HELLO_TRIANGLE_EXE})
  target_compile_options(${HELLO_TRIANGLE_EXE} PRIVATE /W4 /WX)
  target_compile_options(${SHADERS_EXE} PRIVATE /W4 /WX)
else()
  target_compile_options(${HELLO_TRIANGLE_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
  target_compile_options(${SHADERS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
