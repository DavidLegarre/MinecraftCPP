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

private:
  GLint location(const std::string &name);
  GLuint program = 0;

};
} // namespace render
