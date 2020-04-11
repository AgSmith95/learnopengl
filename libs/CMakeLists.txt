cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# cloning dependencies
find_package(Git REQUIRED)

# GLFW 3.3
# git clone glfw branch 3.3-stable
set(
        GLFW33_COMMIT
        0ac01338
#        d9924933
)
message(
        "CHECKING OUT GLFW 3.3-stable ${GLFW33_COMMIT}"
)
execute_process(
        COMMAND ${GIT_EXECUTABLE} clone
        -b 3.3-stable https://github.com/glfw/glfw
        ${LIBS_DIR}/glfw
)
# git reset to correct branch/commit
execute_process(
        WORKING_DIRECTORY ${LIBS_DIR}/glfw
        COMMAND ${GIT_EXECUTABLE} reset --hard ${GLFW33_COMMIT}
)
# GLFW 3.3

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(glfw)

add_subdirectory(glad)
