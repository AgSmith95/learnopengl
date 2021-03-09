#ifndef LEARNOPENGL_WRAPPER_H
#define LEARNOPENGL_WRAPPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Should be Singleton in theory
class Wrapper {
public:
    static Wrapper& getInstance();
    GLFWwindow* getWindow();

    float getWidth() const;
    float getHeight() const;
    float getAspect() const;

    // change window size
    void setWindowSize(int width, int height);

    // delete copy constructor/assignment
    Wrapper(Wrapper&) = delete;
    Wrapper& operator=(Wrapper&) = delete;
    // delete move constructor/assignment
    Wrapper(Wrapper&&) = delete;
    Wrapper& operator=(Wrapper&&) = delete;

private:
    GLFWwindow* window;

    float m_width = 800.0;
    float m_height = 600.0;

    Wrapper();
    ~Wrapper();
};

GLFWwindow* window();

#endif //LEARNOPENGL_WRAPPER_H
