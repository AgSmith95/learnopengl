#option(LIGHTING_MAPS_EXERCISES
#    "Build exercises for Basic lighting tutorial"
#    OFF)

# FINAL
set(LIGHTING_MAPS_EXE lighting_maps)
add_executable(
    ${LIGHTING_MAPS_EXE}
    lighting_maps.cpp
)
target_link_libraries(
    ${LIGHTING_MAPS_EXE}
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
    target_compile_options(${LIGHTING_MAPS_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${LIGHTING_MAPS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Exercises
#if(LIGHTING_MAPS_EXERCISES)
#    add_subdirectory(exercises)
#endif()