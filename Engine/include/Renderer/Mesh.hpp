#pragma once

#include <vector>

#include "Renderer/OpenGL.hpp"
#include "Renderer/Vertex.hpp"

class Mesh {
   public:
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<uint32_t>& indices);

   private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};