#include <iostream>
#include <cmath>

#include <glad/glad.h> // WARNING! INCLUDE BEFORE GLFW!!!
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <helpers.h>
#include <Shape.h>
#include <Wrapper.h>

#include <Shaders.h>

int main()
{
    // Init GL by initializing Wrapper singleton
    window(); // not very elegant, yeah

    // SHAPE
    Shape shape(
            {
                    -0.5f, -0.5f, 0.0f,
                     0.0f,  0.5f, 0.0f,
                     0.5f, -0.5f, 0.0f
            },
            {
                    0, 1, 2
            }
    );

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

        // swap buffers
        glfwSwapBuffers(window());
        // check and call events
        glfwPollEvents();
    }

    return 0;
}
