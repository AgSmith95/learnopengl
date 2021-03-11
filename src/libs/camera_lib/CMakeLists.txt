# library for camera
add_library(
    camera_lib
    INTERFACE
)
target_link_libraries(
    camera_lib
    INTERFACE
    OpenGL::GL
    glfw
    glm
    glad
)
target_include_directories(
    camera_lib
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
