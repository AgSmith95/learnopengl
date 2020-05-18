FILE(
        GLOB
        SRC_DIR_CPP_FILES
        "src/*.cpp"
)

# library for shaders
add_library(
        shaders_lib
        ${SRC_DIR_CPP_FILES}
)
target_link_libraries(
        shaders_lib
        OpenGL::GL
        glfw
        glad
)
target_include_directories(
        shaders_lib
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE src
)

if(MSVC)
    target_compile_options(shaders_lib PRIVATE /W4 /WX)
else()
    target_compile_options(shaders_lib PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
