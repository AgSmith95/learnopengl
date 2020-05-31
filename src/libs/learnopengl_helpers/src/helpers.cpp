#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <helpers.h>

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

DrawInfo::DrawInfo(unsigned int vao, GLsizei n) : m_VAO{vao}, m_num{n} {}

DrawInfo::DrawInfo(unsigned int vao, GLsizei n, GLenum mode) : m_VAO{vao}, m_num{n}, m_mode{mode} {}

DrawInfo::DrawInfo(unsigned int vao, GLsizei n, GLenum mode, GLenum face) : m_VAO{vao}, m_num{n},
                                                                            m_mode{mode},
                                                                            m_face{face} {}

void DrawElements(const DrawInfo& di) {
    glPolygonMode(di.m_face, di.m_mode);
    glBindVertexArray(di.m_VAO);
    glDrawElements(GL_TRIANGLES, di.m_num, GL_UNSIGNED_INT, nullptr); // drawing elements
}

void DrawTriangles(const DrawInfo& di) {
    glPolygonMode(di.m_face, di.m_mode);
    glBindVertexArray(di.m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, di.m_num);
}
