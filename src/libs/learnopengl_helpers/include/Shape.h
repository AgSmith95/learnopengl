#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>

#include <vector>

class Shape {
public:
    /**
     *
     * @param vertices
     * @param v_size
     * @param indices
     * @param i_size
     */
    Shape(const float* vertices, size_t v_size,
          const unsigned int* indices, size_t i_size);

    /**
     *
     * @param vertices
     * @param indices
     */
    Shape(const std::vector<float>& vertices,
          const std::vector<unsigned int>& indices);

    ~Shape();

    void Draw() const;

private:
    unsigned int VBO{};
    unsigned int EBO{};
    unsigned int VAO{};
    GLsizei num{};
};

#endif //SHAPE_H
