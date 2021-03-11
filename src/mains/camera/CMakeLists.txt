option(BUILD_CAMERA_EXERCISES
    "Build exercises for Camera tutorial"
    ON)

# FINAL
set(CAMERA_EXE camera)
add_executable(
    ${CAMERA_EXE}
    camera.cpp
)
target_link_libraries(
    ${CAMERA_EXE}
    OpenGL::GL
    glfw
    glm
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${CAMERA_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${CAMERA_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Exercises
if(BUILD_CAMERA_EXERCISES)
    add_subdirectory(exercises)
endif()
