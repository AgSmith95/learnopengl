option(BUILD_SHADERS_UNIFORM
    "Build first part of Shaders training materials - uniform location"
    OFF)
option(BUILD_SHADERS_ATTRIBUTES
    "Build second part of Shaders training materials - more attributes"
    OFF)
option(BUILD_SHADERS_USE_LIB
    "Build third part of Shaders training materials - using shaders lib"
    OFF)
option(BUILD_SHADERS_EXERCISES
    "Build exercises for Shaders tutorial"
    ON)

add_definitions(-DSHADERS_DIRECTORY="${SHADERS_DIRECTORY}")

# "uniform location" part
if(BUILD_SHADERS_UNIFORM)
    set(SHADERS_UNIFORM_EXE shaders_uniform)
    add_executable(
        ${SHADERS_UNIFORM_EXE}
        shaders.cpp
    )
    target_link_libraries(
        ${SHADERS_UNIFORM_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
    )
    if(MSVC)
        target_compile_options(${SHADERS_UNIFORM_EXE} PRIVATE /W4 /WX)
    else()
        target_compile_options(${SHADERS_UNIFORM_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()
# "more attributes" part
if(BUILD_SHADERS_ATTRIBUTES)
    set(SHADERS_ATTR_EXE shaders_attributes)
    add_executable(
        ${SHADERS_ATTR_EXE}
        shaders_attributes.cpp
    )
    target_link_libraries(
        ${SHADERS_ATTR_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
    )
    if(MSVC)
        target_compile_options(${SHADERS_ATTR_EXE} PRIVATE /W4 /WX)
    else()
        target_compile_options(${SHADERS_ATTR_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()
# "shaders library" part
if(BUILD_SHADERS_USE_LIB)
    set(SHADERS_USE_LIB_EXE shaders_use_lib)
    add_executable(
        ${SHADERS_USE_LIB_EXE}
        shaders_using_lib.cpp
    )
    target_link_libraries(
        ${SHADERS_USE_LIB_EXE}
        OpenGL::GL
        glfw
        glad
        learnopengl_helpers
        shaders_lib
    )
    if(MSVC)
        target_compile_options(${SHADERS_USE_LIB_EXE} PRIVATE /W4 /WX)
    else()
        target_compile_options(${SHADERS_USE_LIB_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()

# FINAL: "uniform location" and using library
set(SHADERS_EXE shaders)
add_executable(
    ${SHADERS_EXE}
    shaders_uniform_lib.cpp
)
target_link_libraries(
    ${SHADERS_EXE}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
)
if(MSVC)
    target_compile_options(${SHADERS_EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${SHADERS_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Exercises
if(BUILD_SHADERS_EXERCISES)
    add_subdirectory(exercises)
endif()