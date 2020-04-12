set(EXECUTABLE learnopengl)

include_directories(include)

FILE(
        GLOB
        SRC_DIR_CPP_FILES
        "src/*.cpp"
)

add_executable(
        ${EXECUTABLE}
        main.cpp
        ${SRC_DIR_CPP_FILES}
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
