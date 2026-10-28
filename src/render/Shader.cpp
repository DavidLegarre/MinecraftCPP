#include "render/Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

namespace render {

namespace {

std::string readFile(const std::string &path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("cannot open shader: " + path);
  }
  return std::string(std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>());
}

// Both stages run the same five GL calls; only the stage type and path differ.
GLuint compileStage(GLenum type, const std::string &source,
                    const std::string &path) {
  const GLuint shader = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint ok = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (ok != GL_TRUE) {
    char log[1024] = {};
    glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
    glDeleteShader(shader);
    throw std::runtime_error("shader compile failed (" + path + "):\n" + log);
  }
  return shader;
}

} // namespace

Shader::Shader(const std::string &vsPath, const std::string &fsPath) {
  const GLuint vertexShader =
      compileStage(GL_VERTEX_SHADER, readFile(vsPath), vsPath);
  const GLuint fragmentShader =
      compileStage(GL_FRAGMENT_SHADER, readFile(fsPath), fsPath);

  program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLint ok = GL_FALSE;
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  if (ok != GL_TRUE) {
    char log[1024] = {};
    glGetProgramInfoLog(program, sizeof(log), nullptr, log);
    glDeleteProgram(program);
    program = 0;
    throw std::runtime_error(std::string("shader link failed: ") + log);
  }
}

Shader::~Shader() {
  if (program != 0) {
    glDeleteProgram(program);
  }
}

void Shader::bind() const { glUseProgram(program); }

void Shader::cleanUp() const {
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
  glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(value));
}

} // namespace render
