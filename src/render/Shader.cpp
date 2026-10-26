#include "render/Shader.hpp"

#include <iostream>
#include <fstream>

namespace render {
    std::string readFile(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            throw std::runtime_error("cannot open shader: " + path);
        }
        return std::string(std::istreambuf_iterator<char>(file),
                           std::istreambuf_iterator<char>());
    }
    Shader::Shader(const std::string &vsPath, const std::string &fsPath){
        std::string vertexSource;
        std::string fragmentSource;
        // use private _readFile function
        vertexSource = readFile(vsPath);
        fragmentSource = readFile(fsPath);
    };

    Shader::~Shader() {
        if (program != 0) {
            glDeleteProgram(program);
        }
    }

};
