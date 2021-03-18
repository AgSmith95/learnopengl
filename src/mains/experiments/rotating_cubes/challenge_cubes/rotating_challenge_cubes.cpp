#include <vector>
#include <map>
#include <algorithm>

#include <iostream>
#include <cmath>

#include <glad/glad.h> // WARNING! INCLUDE BEFORE GLFW!!!
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Shape.h>
#include <Wrapper.h>

#include <Shaders.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

void processInput(GLFWwindow *window);

float lastX = 400.0f;
float lastY = 300.0f;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float fov = 45.0f;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Rectangle {
public:
    Rectangle(glm::vec3 A, glm::vec3 B,
              glm::vec3 C, glm::vec3 D): a(A), b(B), c(C), d(D) {
        float vertices[] = {
            // coordinates // texture coordinates
            a.x, a.y, a.z, 0.0f, 1.0f,
            b.x, b.y, b.z, 1.0f, 1.0f,
            c.x, c.y, c.z, 0.0f, 0.0f,

            b.x, b.y, b.z, 1.0f, 1.0f,
            c.x, c.y, c.z, 0.0f, 0.0f,
            d.x, d.y, d.z, 1.0f, 0.0f
        };

        glGenBuffers(1, &VBO1);
        glGenVertexArrays(1, &VAO1);

        glBindVertexArray(VAO1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &VBO2);
        glGenVertexArrays(1, &VAO2);

        glBindVertexArray(VAO2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices+15, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    Rectangle(float ax, float ay, float az, float bx, float by, float bz,
              float cx, float cy, float cz, float dx, float dy, float dz):
              Rectangle({ax, ay, az}, {bx, by, bz}, {cx, cy, cz}, {dx, dy, dz}) {}


    ~Rectangle() {
        glDeleteVertexArrays(1, &VAO1);
        glDeleteVertexArrays(1, &VAO2);
        glDeleteBuffers(1, &VBO1);
        glDeleteBuffers(1, &VBO2);
    }

    void draw() const {
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    glm::vec3 getMidpoint() const {
        // first midpoint
        float   m1x = (a.x + c.x)/2,
                m1y = (a.y + b.y)/2,
                m1z = (a.z + c.z)/2;
        // second midpoint
        float   m2x = (b.x + d.x)/2,
                m2y = (b.y + d.y)/2,
                m2z = (b.z + d.z)/2;
        // midpoint of a segment connecting midpoints
        return {(m1x + m2x)/2, (m1y + m2y)/2, (m1z + m2z)/2};
    }

    std::vector<glm::vec4> getVertices() const {
        return {
            {a, 1.0},
            {b, 1.0},
            {c, 1.0},
            {d, 1.0}
        };
    };

private:
    glm::vec3 a, b, c, d;
    // a0    b1
    //  +----+
    //  |    |
    //  +----+
    // c2    d3
    unsigned int VAO1, VAO2, VBO1, VBO2;
};



int main() {
    // Init GL by initializing Wrapper singleton
    auto Window = window(); // not very elegant, yeah
    Wrapper::getInstance().setWindowSize(960, 540);
    lastX = Wrapper::getInstance().getWidth() / 2;
    lastY = Wrapper::getInstance().getHeight() / 2;
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(Window, mouse_callback);
    glfwSetScrollCallback(Window, scroll_callback);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // SHADERS
    Shader ourShader(
            SHADERS_DIRECTORY "coordinates/coordinates_vsh.vsh",
            CHALLENGE_CUBES_DIR "fragment_shader.fsh"
    );

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    Rectangle faces1[] = {
            // FIRST CUBE
            // 1 FAR
            {
                   -1.0f,  1.0f, -1.0f, // 5
                    1.0f,  1.0f, -1.0f, // 4
                   -1.0f, -1.0f, -1.0f, // 1
                    1.0f, -1.0f, -1.0f  // 2
            },
            // 2 FRONT
            {
                   -1.0f,  1.0f,  1.0f,  // 5
                    1.0f,  1.0f,   1.0f, // 4
                   -1.0f, -1.0f,  1.0f,  // 1
                    1.0f, -1.0f,   1.0f  // 2
            },
            // 3 LEFT
            {
                    -1.0f, -1.0f,  1.0f, // 5
                    -1.0f, -1.0f, -1.0f, // 4
                    -1.0f,  1.0f,  1.0f, // 1
                    -1.0f,  1.0f, -1.0f  // 2
            },
            // 4 RIGHT
            {
                    1.0f, -1.0f,  1.0f, // 5
                    1.0f, -1.0f, -1.0f, // 4
                    1.0f,  1.0f,  1.0f, // 1
                    1.0f,  1.0f, -1.0f  // 2
            },
            // 5 BOTTOM
            {
                    -1.0f, -1.0f,  1.0f, // 5
                    1.0f, -1.0f,  1.0f,  // 4
                    -1.0f, -1.0f, -1.0f, // 1
                    1.0f, -1.0f, -1.0f   // 2
            },
            // 6 TOP
            {
                   -1.0f,  1.0f,  1.0f,  // 5
                    1.0f,  1.0f,  1.0f,  // 4
                   -1.0f,  1.0f, -1.0f,  // 1
                    1.0f,  1.0f, -1.0f   // 2
            },


//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------


            // SECOND CUBE
            // 1 FAR
            {
                   -0.5f,  0.5f,  -0.5f, // 5
                    0.5f,  0.5f,  -0.5f, // 4
                   -0.5f, -0.5f,  -0.5f, // 1
                    0.5f, -0.5f,  -0.5f  // 2
            },
            // 2 FRONT
            {
                   -0.5f,  0.5f,  0.5f, // 5
                    0.5f,  0.5f,  0.5f, // 4
                   -0.5f, -0.5f,  0.5f, // 1
                    0.5f, -0.5f,  0.5f  // 2
            },
            // 3 LEFT
            {
                    -0.5f, -0.5f,  0.5f, // 5
                    -0.5f, -0.5f, -0.5f, // 4
                    -0.5f,  0.5f,  0.5f, // 1
                    -0.5f,  0.5f, -0.5f  // 2
            },
            // 4 RIGHT
            {
                    0.5f, -0.5f,  0.5f,  // 5
                    0.5f, -0.5f, -0.5f,  // 4
                    0.5f,  0.5f,  0.5f,  // 1
                    0.5f,  0.5f, -0.5f   // 2
            },
            // 5 BOTTOM
            {
                   -0.5f, -0.5f,  0.5f, // 5
                    0.5f, -0.5f,  0.5f, // 4
                   -0.5f, -0.5f, -0.5f, // 1
                    0.5f, -0.5f, -0.5f  // 2
            },
            // 6 TOP
            {
                   -0.5f,  0.5f,  0.5f, // 5
                    0.5f,  0.5f,  0.5f, // 4
                   -0.5f,  0.5f, -0.5f, // 1
                    0.5f,  0.5f, -0.5f  // 2
            }
    };

    std::vector<glm::vec4> vertices;
    for (const auto& e: faces1) {
        auto v = e.getVertices();
        vertices.insert(vertices.end(), v.begin(), v.end());
    }

    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2;
    {
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(CHALLENGE_CUBES_DIR "red_cube_green-border.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load(CHALLENGE_CUBES_DIR "opaque_squares2.png", &width, &height, &nrChannels, 0);
    if (data) {
        // note that the awesomeface.png has transparency and thus an alpha channel,
        // so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);

    }
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("Texture", 0);

    // RENDER LOOP
    while(!glfwWindowShouldClose(Window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = (float)glfwGetTime();
        std::cout << "radians: " << currentFrame << '\n';
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // processing input
        processInput(Window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // activate shader
        ourShader.use();

        // generate projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(fov), Wrapper::getInstance().getAspect(), 0.1f, 100.0f);
        ourShader.setMat4("projection", projection); // set projection matrix in the Shader

        // create transformations
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

        // make model matrices to determine distance
        // first cube
        glm::mat4 model1 = glm::mat4(1.0f);
        //model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model1 = glm::rotate(model1, 2.34765f, glm::vec3(1.0f, 1.0f, 0.0f));
        // second cube
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::rotate(model2, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
        model2 = glm::rotate(model2, 2.34765f, glm::vec3(-1.0f, -1.0f, -1.0f));
        //model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));

        // sort cubes' sides
//        std::vector<std::pair<float, std::size_t>> sorted;
//        for(std::size_t i = 0; i < midpoints.size(); ++i) {
//            glm::vec4 tmp = glm::vec4{midpoints[i], 1.0};
//            if (i < 6) {
//                tmp = model1 * tmp;
//            }
//            else {
//                tmp = model2 * tmp;
//            }
//            float distance = glm::length( cameraPos - glm::vec3{tmp.x, tmp.y, tmp.z} );
//            sorted.emplace_back(distance,i);
//        }
//        std::sort(sorted.begin(), sorted.end(),
//                  [&](const std::pair<float, std::size_t>& p1,
//                      const std::pair<float, std::size_t>& p2)
//                  { return p1.first > p2.first; }
//                  );

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

        // DRAW
        for (int i = 1; i < 6; ++i) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture2);
            ourShader.setMat4("model", model1);
            faces1[i].draw();
        }

//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture2);

        // swap buffers
        glfwSwapBuffers(Window);
        // check and call events
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    return 0;
}

void processInput(GLFWwindow *window) {
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos   = glm::vec3(0.0f, 0.0f, 5.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        yaw = -90.0f;
        pitch = 0.0f;
        fov = 45.0f;
    }
}

void *p = nullptr;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    p = window; // need this to use variable window
    // facepalm

    if (firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = static_cast<float>(lastY) - ypos; // reversed since y-coordinates range from bottom to top
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    // calculate new direction vector
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    p = window; // need this to use variable window
    // facepalm

    fov -= (float)(yoffset + 0.0*xoffset);
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 60.0f)
        fov = 60.0f;
}
