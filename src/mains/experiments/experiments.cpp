#include <iostream>
#include <cmath>

#include <glad/glad.h> // WARNING! INCLUDE BEFORE GLFW!!!
#include <GLFW/glfw3.h>

#include <helpers.h>
#include <Shape.h>
#include <Wrapper.h>

#include <Shaders.h>

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

    Shape shape(vertices, sizeof(vertices), indices, sizeof(indices));

//    // GENERATE VBO
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);
//
//    // GENERATE EBO
//    // to draw 2 triangles - a rectangle
//    unsigned int EBO;
//    glGenBuffers(1, &EBO);
//
//    // GENERATE VAO
//    unsigned int VAO;
//    glGenVertexArrays(1, &VAO);
//
//    // BIND BUFFERS
//    // 1. bind Vertex Array Object
//    glBindVertexArray(VAO);
//    // 2. copy our vertices array in a buffer for OpenGL to use
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    // 3. copy our index array in a element buffer for OpenGL to use
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    // 4. then set our vertex attributes pointers
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
//    glEnableVertexAttribArray(0);
//
//    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
//    // attribute's bound vertex buffer object so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object
//    // IS stored in the VAO; keep the EBO bound.
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO,
//    // but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways
//    // so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // SHADERS
    Shader ourShader(
            SHADERS_DIRECTORY "shaders/vertex2.vsh",
            SHADERS_DIRECTORY "shaders/fragment2.fsh"
    );

    // tmp values
    double timeValue = 0.0f;
    float  greenValue = 0.0f;
    // RENDER LOOP
    while(!glfwWindowShouldClose(window()))
    {
        // use our shader
        ourShader.use();

        // update the uniform color
        timeValue = glfwGetTime();
        greenValue = static_cast<float>(sin(timeValue)) / 2.0f + 0.5f;
        ourShader.setFloat4("ourColor", {0.0f, greenValue, 1.0f - greenValue, 1.0f});

        // processing input
        processInput(window());

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shape.Draw();

        // as we only have a single VAO there's no need to bind it every time,
        // but we'll do so to keep things a bit more organized
//        glBindVertexArray(VAO);
//        //glDrawArrays(GL_TRIANGLES, 0, 6); // drawing triangles
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // drawing elements
        // glBindVertexArray(0); // no need to unbind it every time
//        glBindVertexArray(0);
        // render end

        // swap buffers
        glfwSwapBuffers(window());
        // check and call events
        glfwPollEvents();
    }
    // RENDER LOOP end

    // optional: de-allocate all resources once they've outlived their purpose:
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);

    return 0;
}