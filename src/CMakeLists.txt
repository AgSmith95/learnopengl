set(EXECUTABLE learnopengl)

include_directories(include)

add_executable(
        ${EXECUTABLE}
        main.cpp
        src/callbacks.cpp
        src/helpers.cpp
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
