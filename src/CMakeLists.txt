FILE(GLOB CPP_FILES *.cpp)
FILE(GLOB HPP_FILES *.hpp)
FILE(GLOB C_FILES *.c)
FILE(GLOB H_FILES *.h)

set(EXECUTABLE learnopengl)

add_executable(
        ${EXECUTABLE}
        ${CPP_FILES}
        ${HPP_FILES}
        ${C_FILES}
        ${H_FILES}
)

target_link_libraries(
        ${EXECUTABLE}
        glfw
        glad
)

if(MSVC)
  target_compile_options(${EXECUTABLE} PRIVATE /W4 /WX)
else()
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
