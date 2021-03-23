set(TRAFFIC_LIGHTS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/
    )
add_definitions(-DTRAFFIC_LIGHTS_DIR="${TRAFFIC_LIGHTS_DIR}")

set(TRAFFIC_LIGHTS_CUBES traffic_lights_cube)
add_executable(
        ${TRAFFIC_LIGHTS_CUBES}
        traffic_lights.cpp
)
target_link_libraries(
        ${TRAFFIC_LIGHTS_CUBES}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
        stb
        camera_lib
)
if(MSVC)
    target_compile_options(${TRAFFIC_LIGHTS_CUBES} PRIVATE /W4 /WX)
else()
    target_compile_options(${TRAFFIC_LIGHTS_CUBES} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
