#include "pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace lve {

LvePipeline::LvePipeline(const lve::MyEngineDevice& device, const std::string& vertFile,
                         const std::string& fragFile) {
    createGraphicsPipeline(vertFile, fragFile);
}

std::vector<char> LvePipeline::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }

    const auto fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

void LvePipeline::createGraphicsPipeline(const std::string& vertFile,
                                         const std::string& fragFile) {
    const auto vertShaderCode = readFile(vertFile);
    const auto fragShaderCode = readFile(fragFile);

    std::cout << "Vertex shader code size: " << vertShaderCode.size() << " bytes\n";
    std::cout << "Fragment shader code size: " << fragShaderCode.size() << " bytes\n";
}

}  // namespace lve