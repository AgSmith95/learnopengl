#include <iostream>

#include <glad/glad.h> // WARNING! INCLUDE BEFORE GLFW!!!
#include <GLFW/glfw3.h>

#include <helpers.h>

#include <Wrapper.h>

int main()
{
    // RENDER LOOP
    while(!glfwWindowShouldClose(window()))
    {
        // processing input
        processInput(window());

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // render end

        // swap buffers
        glfwSwapBuffers(window());
        // check and call events
        glfwPollEvents();
    }
    // RENDER LOOP end

    return 0;
}