#include "Renderer/Mesh.hpp"

#include <iostream>

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<uint32_t>& indices)
    : m_IndexCount(indices.size()) {
    std::cout << "Creating mesh with " << vertices.size() << " vertices and "
              << indices.size() << " indices" << std::endl;

    // Generate VAO, VBO, and EBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    std::cout << "Generated: VAO=" << m_VAO << ", VBO=" << m_VBO
              << ", EBO=" << m_EBO << std::endl;

    // Bind VAO
    glBindVertexArray(m_VAO);
    std::cout << "Bound VAO " << m_VAO << std::endl;

    // Upload vertex data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    // Upload index data to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 indices.data(), GL_STATIC_DRAW);

    // Define vertex attribute pointers
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);
    std::cout << "Set position attribute (location 0)" << std::endl;

    // UV/TexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, UV));
    glEnableVertexAttribArray(1);
    std::cout << "Set UV attribute (location 1)" << std::endl;

    // Unbind VAO (EBO binding is stored in VAO state, so leave it)
    glBindVertexArray(0);
    std::cout << "Unbound VAO, mesh created successfully" << std::endl;
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_VAO(other.m_VAO),
      m_VBO(other.m_VBO),
      m_EBO(other.m_EBO),
      m_IndexCount(other.m_IndexCount) {
    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_EBO = 0;
    other.m_IndexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
        if (m_EBO) glDeleteBuffers(1, &m_EBO);

        m_VAO = other.m_VAO;
        m_VBO = other.m_VBO;
        m_EBO = other.m_EBO;
        m_IndexCount = other.m_IndexCount;

        other.m_VAO = 0;
        other.m_VBO = 0;
        other.m_EBO = 0;
        other.m_IndexCount = 0;
    }
    return *this;
}

Mesh::~Mesh() {
    if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
    if (m_VBO) glDeleteBuffers(1, &m_VBO);
    if (m_EBO) glDeleteBuffers(1, &m_EBO);
}

void Mesh::Bind() const {
    std::cout << "Mesh::Bind() - binding VAO " << m_VAO << std::endl;
    glBindVertexArray(m_VAO);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "ERROR: glBindVertexArray failed with code " << std::hex << err
                  << std::dec << " for VAO " << m_VAO << std::endl;
    }
}

uint32_t Mesh::GetIndexCount() const { return m_IndexCount; }
