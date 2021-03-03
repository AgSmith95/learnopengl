option(BUILD_COORDINATES_EXERCISES
    "Build exercises for Coordinates tutorial"
    ON)

# FINAL
set(COORDINATES_EXE coordinates)
add_executable(
    ${COORDINATES_EXE}
    coordinates.cpp
)
target_link_libraries(
    ${COORDINATES_EXE}
    OpenGL::GL
    glfw
    glm
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${COORDINATES_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${COORDINATES_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Exercises
if(BUILD_COORDINATES_EXERCISES)
    add_subdirectory(exercises)
endif()
