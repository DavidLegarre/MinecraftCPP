#pragma once
#include <string>

class Shader {
   public:
    unsigned int ID;
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    void use() const;

   private:
    void checkCompileErrors(unsigned int shader, std::string type);
};