#pragma once
#include <string>

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

class Shader {
   public:
    unsigned int ID;
    Shader(const char* vertexSource = vertexShaderSource,
           const char* fragmentSource = fragmentShaderSource);
    ~Shader();

    void use() const;

   private:
    void checkCompileErrors(unsigned int shader, std::string type);
};