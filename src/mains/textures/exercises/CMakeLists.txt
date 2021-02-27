# mirror awesomeface
set(MIRROR_FACE mirror_face_textures_ex1)
add_executable(
    ${MIRROR_FACE}
    textures_exc1.cpp
)
target_link_libraries(
    ${MIRROR_FACE}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${MIRROR_FACE} PRIVATE /W4 /WX)
else()
    target_compile_options(${MIRROR_FACE} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# four faces
set(FOUR_FACES four_faces_textures_ex2)
add_executable(
    ${FOUR_FACES}
    textures_exc2.cpp
)
target_link_libraries(
    ${FOUR_FACES}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${FOUR_FACES} PRIVATE /W4 /WX)
else()
    target_compile_options(${FOUR_FACES} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# mix textures
set(MIX_TEXTURES mix_textures_ex3)
add_executable(
    ${MIX_TEXTURES}
    textures_exc3.cpp
)
target_link_libraries(
    ${MIX_TEXTURES}
    OpenGL::GL
    glfw
    glad
    learnopengl_helpers
    shaders_lib
    stb
)
if(MSVC)
    target_compile_options(${MIX_TEXTURES} PRIVATE /W4 /WX)
else()
    target_compile_options(${MIX_TEXTURES} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
