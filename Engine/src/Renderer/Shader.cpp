#include "Renderer/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = ReadShaderFile(vertexPath);
    std::string fragmentSource = ReadShaderFile(fragmentPath);

    GLuint vertexShader = CompileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Link shaders
    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ProgramID, 512, nullptr, infoLog);
        throw std::runtime_error(
            std::string("Shader program linking failed: ") + infoLog);
    }

    std::cout << "Shader program linked successfully (ID: " << m_ProgramID
              << ")" << std::endl;
    glUseProgram(m_ProgramID);
    
    // Show uniforms
    GLint numUniforms = 0;
    glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &numUniforms);
    std::cout << "Active uniforms: " << numUniforms << std::endl;
    for (int i = 0; i < numUniforms; i++) {
        char uname[256];
        int len;
        glGetActiveUniformName(m_ProgramID, i, 256, &len, uname);
        std::cout << "  - " << uname << std::endl;
    }
    
    // Show attributes
    GLint numAttribs = 0;
    glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTES, &numAttribs);
    std::cout << "Active attributes: " << numAttribs << std::endl;
    for (int i = 0; i < numAttribs; i++) {
        char aname[256];
        int len, size;
        GLenum type;
        glGetActiveAttrib(m_ProgramID, i, 256, &len, &size, &type, aname);
        std::cout << "  - " << aname << " (location: " << i << ")" << std::endl;
    }
    glUseProgram(0);

    // Delete shaders as they're linked into the program now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(m_ProgramID); }

void Shader::Use() const { glUseProgram(m_ProgramID); }

GLuint Shader::GetProgramID() const { return m_ProgramID; }

void Shader::SetUniform1i(const std::string& name, int value) const {
    GLint loc = glGetUniformLocation(m_ProgramID, name.c_str());
    if (loc == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader"
                  << std::endl;
    }
    glUniform1i(loc, value);
}

GLuint Shader::CompileShader(const std::string& source, GLenum type) {
    GLuint shader = glCreateShader(type);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::string shaderType =
            (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";
        throw std::runtime_error(
            shaderType + std::string(" shader compilation failed: ") + infoLog);
    }

    return shader;
}

std::string Shader::ReadShaderFile(const std::string& filePath) {
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        std::cout << "Successfully loaded shader: " << filePath << std::endl;
        return shaderStream.str();
    } catch (std::ifstream::failure& e) {
        throw std::runtime_error(std::string("Failed to read shader file: ") +
                                 filePath);
    }
}
