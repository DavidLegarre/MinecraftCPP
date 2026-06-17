#pragma once

#include <vector>

#include "Renderer/OpenGL.hpp"
#include "Renderer/Vertex.hpp"

class Mesh {
   public:
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<uint32_t>& indices);

    ~Mesh();

    // Disable copy constructor and copy assignment operator
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    // Enable move constructor and move assignment operator
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void Bind() const;

    uint32_t GetIndexCount() const;

   private:
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;

    uint32_t m_IndexCount = 0;
};