FILE(
        GLOB
        SRC_DIR_CPP_FILES
        "src/*.cpp"
)

# library for helpers
add_library(
        learnopengl_helpers
        ${SRC_DIR_CPP_FILES}
)
target_link_libraries(
        learnopengl_helpers
        OpenGL::GL
        glfw
        glad
)
target_include_directories(
        learnopengl_helpers
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE src
)
