#pragma once
#include <string>

class Shader {
   public:
    unsigned int ID;
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

   private:
    void checkCompileErrors(unsigned int shader, std::string type);
};