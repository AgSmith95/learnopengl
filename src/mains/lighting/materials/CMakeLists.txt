option(BUILD_MATERIALS_EXERCISES
    "Build exercises for Materials tutorial"
    OFF)

# FINAL
set(MATERIALS_EXE materials)
add_executable(
    ${MATERIALS_EXE}
    materials.cpp
)
target_link_libraries(
    ${MATERIALS_EXE}
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
    target_compile_options(${MATERIALS_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${MATERIALS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Exercises
if(MATERIALS_EXERCISES)
    add_subdirectory(exercises)
endif()