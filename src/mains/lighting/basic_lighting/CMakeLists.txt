option(BUILD_BASIC_LIGHTING_EXERCISES
    "Build exercises for Basic lighting tutorial"
    OFF)

# FINAL
set(BASIC_LIGHTING_EXE basic_lighting)
add_executable(
    ${BASIC_LIGHTING_EXE}
    basic_lighting.cpp
)
target_link_libraries(
    ${BASIC_LIGHTING_EXE}
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
    target_compile_options(${BASIC_LIGHTING_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${BASIC_LIGHTING_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Exercises
if(BUILD_BASIC_LIGHTING_EXERCISES)
    add_subdirectory(exercises)
endif()