#pragma once
#include <vector>

class Mesh {
   public:
    unsigned int VAO, VBO, EBO;
    int indexCount;

    Mesh(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;
};