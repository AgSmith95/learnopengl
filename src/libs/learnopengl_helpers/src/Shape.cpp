#include <glad/glad.h>

#include <helpers.h>

#include <Shape.h>

Shape::Shape(const float* vertices, size_t v_size, const unsigned int* indices, size_t i_size) {
    num = v_size;
    // GENERATE VBO
    glGenBuffers(1, &VBO);
    // GENERATE EBO
    glGenBuffers(1, &EBO);
    // GENERATE VAO
    glGenVertexArrays(1, &VAO);

    // BIND BUFFERS
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);
    // 4. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

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
}

Shape::Shape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) :
        Shape(vertices.data(), vertices.size() * sizeof(float),
              indices.data(), indices.size() * sizeof(float)) {}

void Shape::Draw() const {
    if (VAO != 0) {
        DrawElements(DrawInfo{VAO, num});
    }
}

Shape::~Shape() {
    // de-allocate all resources once they've outlived their purpose:
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
}
