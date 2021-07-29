#ifndef LEARNOPENGL_HELPERS_H
#define LEARNOPENGL_HELPERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window);

struct DrawInfo {
    unsigned int m_VAO{};
    // number of vertices
    GLsizei m_num{};
    // mode param for glPolygonMode
    GLenum m_mode{GL_TRIANGLES};
    // face param for glPolygonMode
    GLenum m_face{GL_FRONT_AND_BACK};

    DrawInfo(unsigned int vao, GLsizei n);
    DrawInfo(unsigned int vao, GLsizei n, GLenum mode);
    DrawInfo(unsigned int vao, GLsizei n, GLenum mode, GLenum face);
};

void DrawElements(const DrawInfo& di);
void DrawTriangles(const DrawInfo& di);

unsigned int loadTexture(char const * path);

#endif //LEARNOPENGL_HELPERS_H
