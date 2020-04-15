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
        OpenGL::GL
        glfw
        glad
)

if(MSVC)
  target_compile_options(${EXECUTABLE} PRIVATE /W4 /WX)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXECUTABLE})
else()
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
