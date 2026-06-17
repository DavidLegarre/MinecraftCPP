#pragma once

#include <glad/gl.h>

#include <string>

class Shader {
   public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use() const;
    GLuint GetProgramID() const;
    void SetUniform1i(const std::string& name, int value) const;

   private:
    GLuint m_ProgramID;

    GLuint CompileShader(const std::string& source, GLenum type);
    std::string ReadShaderFile(const std::string& filePath);
};
