set(ROTATING_CUBES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
add_definitions(-DROTATING_CUBES_DIR="${ROTATING_CUBES_DIR}")

option(BUILD_ROTATING_CUBE1
        "Build blue cube"
        ON)
option(BUILD_BLUE_CUBE
        "Build blue cube"
        ON)
option(BUILD_LOGO_CUBE
        "Build logo cube"
        ON)
option(BUILD_CHALLENGE_CUBES
        "Build logo cube"
        ON)

if(BUILD_ROTATING_CUBE1)
    set(ROTATING_CUBES rotating_cubes)
    add_executable(
        ${ROTATING_CUBES}
        rotating_cubes.cpp
    )
    target_link_libraries(
        ${ROTATING_CUBES}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
        stb
    )
    if(MSVC)
        target_compile_options(${ROTATING_CUBES} PRIVATE /W4 /WX)
    else()
        target_compile_options(${ROTATING_CUBES} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()

if(BUILD_BLUE_CUBE)
    set(ROTATING_BLUE_CUBE rotate_blue_cube)
    add_executable(
            ${ROTATING_BLUE_CUBE}
            rotating_blue_cube.cpp
    )
    target_link_libraries(
            ${ROTATING_BLUE_CUBE}
            OpenGL::GL
            glfw
            glad
            learnopengl_helpers
            shaders_lib
            stb
    )
    if(MSVC)
        target_compile_options(${ROTATING_BLUE_CUBE} PRIVATE /W4 /WX)
    else()
        target_compile_options(${ROTATING_BLUE_CUBE} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()

if(BUILD_LOGO_CUBE)
    set(ROTATING_LOGO_CUBE rotate_logo_cube)
    add_executable(
            ${ROTATING_LOGO_CUBE}
            ROTATING_LOGO_CUBE.cpp
    )
    target_link_libraries(
            ${ROTATING_LOGO_CUBE}
            OpenGL::GL
            glfw
            glad
            learnopengl_helpers
            shaders_lib
            stb
    )
    if(MSVC)
        target_compile_options(${ROTATING_LOGO_CUBE} PRIVATE /W4 /WX)
    else()
        target_compile_options(${ROTATING_LOGO_CUBE} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()

if (BUILD_CHALLENGE_CUBES)
    add_subdirectory(challenge_cubes)
    add_subdirectory(traffic_lights)
endif()