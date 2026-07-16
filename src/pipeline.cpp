#include "pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace pipeline {

Pipeline::Pipeline(const std::string &vertFile, const std::string &fragFile) {
    createGraphicsPipeline(vertFile, fragFile);
};
std::vector<char> Pipeline::readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
};

void Pipeline::createGraphicsPipeline(const std::string &vertFile,
                                      const std::string &fragFile) {
    auto vertShaderCode = readFile(vertFile);
    auto fragShaderCode = readFile(fragFile);

    std::cout << "Vertex shader code size: " << vertShaderCode.size()
              << " bytes\n";
    std::cout << "Fragment shader code size: " << fragShaderCode.size()
              << " bytes\n";
};
} // namespace pipeline