#include "render/Mesh.hpp"

namespace render {

Mesh::Mesh(const std::vector<float> &vertices)
    : count(static_cast<GLsizei>(vertices.size() / 3)) {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
               vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

void Mesh::draw() const {
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, count);
}

} // namespace render
