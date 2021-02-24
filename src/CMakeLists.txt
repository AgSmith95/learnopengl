set(
    SHADERS_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/
)
add_definitions(-DSHADERS_DIRECTORY="${SHADERS_DIRECTORY}")

add_subdirectory(mains)
add_subdirectory(libs)
