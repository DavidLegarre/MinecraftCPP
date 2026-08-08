#include "pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace lve {

LvePipeline::LvePipeline(LveDevice& device,
                         const std::string& vertFile,
                         const std::string& fragFile,
                         const PipelineConfigInfo& configInfo)
    : lveDevice(device) {
	createGraphicsPipeline(vertFile, fragFile, configInfo);
}

LvePipeline::~LvePipeline() {}

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
                                         const std::string& fragFile,
                                         const PipelineConfigInfo& configInfo) {
	const auto vertShaderCode = readFile(vertFile);
	const auto fragShaderCode = readFile(fragFile);

	std::cout << "Vertex shader code size: " << vertShaderCode.size() << " bytes\n";
	std::cout << "Fragment shader code size: " << fragShaderCode.size() << " bytes\n";
}

void LvePipeline::createShaderModule(const std::vector<char>& code,
                                     VkShaderModule* shaderModule) {
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	if (vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) !=
	    VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
}

PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(uint32_t width,
                                                          uint32_t height) {
	PipelineConfigInfo configInfo{};
	return configInfo;
}
}  // namespace lve