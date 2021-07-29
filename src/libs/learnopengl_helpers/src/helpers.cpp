#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <helpers.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

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

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format{};
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, (int)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << '\n';
        stbi_image_free(data);
    }

    return textureID;
}
