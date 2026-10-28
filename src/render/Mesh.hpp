#pragma once

#include <GL/glew.h>

#include <vector>

namespace render {

// Owns one VAO + VBO pair. Positions only, drawn as a triangle list.
class Mesh {
public:
  explicit Mesh(const std::vector<float> &vertices);
  ~Mesh();

  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;

  void draw() const;

private:
  GLuint vao = 0;
  GLuint vbo = 0;
  GLsizei count = 0;
};

} // namespace render
