#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
namespace render {
class Shader {
public:
  Shader(const std::string &vsPath, const std::string &fsPath);
  ~Shader();

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

  void bind() const;
  void cleanUp() const;
  void setMat4(const std::string &name, const glm::mat4 &value) const;

private:
  GLuint program = 0;
  const GLuint fragmentShader = 0;
  const GLuint vertexShader = 0;
};
} // namespace render
