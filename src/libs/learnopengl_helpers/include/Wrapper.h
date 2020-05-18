#ifndef LEARNOPENGL_WRAPPER_H
#define LEARNOPENGL_WRAPPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Should be Singleton in theory
class Wrapper {
public:
    static Wrapper& getInstance();
    GLFWwindow* getWindow();

    // delete copy constructor/assignment
    Wrapper(Wrapper&) = delete;
    Wrapper& operator=(Wrapper&) = delete;
    // delete move constructor/assignment
    Wrapper(Wrapper&&) = delete;
    Wrapper& operator=(Wrapper&&) = delete;

private:
    GLFWwindow* window;

    Wrapper();
    ~Wrapper();
};

GLFWwindow* window();

#endif //LEARNOPENGL_WRAPPER_H
