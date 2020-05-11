#include <iostream>
#include <cmath>

#include <glad/glad.h> // WARNING! INCLUDE BEFORE GLFW!!!
#include <GLFW/glfw3.h>

#include <helpers.h>

#include <Wrapper.h>

// define vertex shader code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
})";

// define fragment shader code
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
})";

int main()
{
    // Init GL by initializing Wrapper singleton
    window(); // not very elegant, yeah

    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // top
    };

    // GENERATE VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // GENERATE VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // BIND BUFFERS
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    // 3.1. set position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // 3.2. set color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
    // attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object
    // IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO,
    // but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways
    // so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // SHADERS
    // temporary variables for status
    int  success;
    char infoLog[512];
    // VERTEX SHADER
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
    // create
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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
    unsigned int shaderProgram = glCreateProgram();
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

        // use our shader
        glUseProgram(shaderProgram);

        // as we only have a single VAO there's no need to bind it every time,
        // but we'll do so to keep things a bit more organized
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // drawing triangles
        // glBindVertexArray(0); // no need to unbind it every time
        glBindVertexArray(0);
        // render end

        // swap buffers
        glfwSwapBuffers(window());
        // check and call events
        glfwPollEvents();
    }
    // RENDER LOOP end

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    return 0;
}