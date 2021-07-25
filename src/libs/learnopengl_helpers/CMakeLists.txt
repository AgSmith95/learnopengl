FILE(
    GLOB
    SRC_DIR_CPP_FILES
    "src/*.cpp"
)

FILE(
    GLOB
    HEADER_FILES
    "include/*.h"
    "include/*.hpp"
)

# library for helpers
add_library(
    learnopengl_helpers
    ${SRC_DIR_CPP_FILES}
    ${HEADER_FILES}
)
target_link_libraries(
    learnopengl_helpers
    OpenGL::GL
    glfw
    glad
    stb
)
target_include_directories(
    learnopengl_helpers
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE src
)

if(MSVC)
    target_compile_options(learnopengl_helpers PRIVATE /W4 /WX)
else()
    target_compile_options(learnopengl_helpers PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
