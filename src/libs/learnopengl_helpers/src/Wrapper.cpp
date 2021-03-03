#include <iostream>

#include <Wrapper.h>
#include <callbacks.h>

Wrapper::Wrapper() {
    // GLFW initialization
    glfwInit();
    // OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // OpenGL Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS

    // create window
    window = glfwCreateWindow(static_cast<int>(m_width), static_cast<int>(m_height), "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    // create window end

    // window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD: load OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

Wrapper::~Wrapper() {
    // properly clean all GLFW resources
    glfwTerminate();
}

Wrapper& Wrapper::getInstance() {
    static Wrapper instance;
    return instance;
}

GLFWwindow* Wrapper::getWindow() {
    return window;
}

float Wrapper::getWidth() const {
    return m_width;
}

float Wrapper::getHeight() const {
    return m_height;
}

float Wrapper::getAspect() const {
    return m_width / m_height;
}

// Get Wrapper's GLFWwindow
GLFWwindow* window() {
    return Wrapper::getInstance().getWindow();
}
