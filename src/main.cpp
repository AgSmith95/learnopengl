#include <iostream>

#include <glad/glad.h> // WARNING! INCLUDE BEFORE GLFW!!!
#include <GLFW/glfw3.h>

#include <helpers.h>

#include <Wrapper.h>

int main()
{
    // Init GL by initializing Wrapper singleton
    window(); // not very elegant, yeah

    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    // GENERATE VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // GENERATE EBO
    // to draw 2 triangles - a rectangle
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // GENERATE VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // BIND BUFFERS
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // SHADERS
    // temporary variables for status
    int  success;
    char infoLog[512];
    // VERTEX SHADER
    // define
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0"
        ;
    // create
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check compile status
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 1;
    }
    // VERTEX SHADER end

    // FRAGMENT SHADER
    // define
    unsigned int fragmentShader;
    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n"
        ;
    // create
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // compile
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check compile status
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 1;
    }
    // FRAGMENT SHADER end

    // SHADER PROGRAM - linked shaders
    // create
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // link
    glLinkProgram(shaderProgram);
    // check status
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 1;
    }
    // use
    glUseProgram(shaderProgram);
    // SHADER PROGRAM end

    // Delete shaders, because they've already compiled into a program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // RENDER LOOP
    while(!glfwWindowShouldClose(window()))
    {
        // processing input
        processInput(window());

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        // render end

        // swap buffers
        glfwSwapBuffers(window());
        // check and call events
        glfwPollEvents();
    }
    // RENDER LOOP end

    glDeleteProgram(shaderProgram);

    return 0;
}