#pragma once

#include "lve_device.hpp"

#include <string>
#include <vector>

namespace lve {

struct PipelineConfigInfo {};

class LvePipeline {
   public:
	LvePipeline(const lve::LveDevice& device, const std::string& vertFile,
	            const std::string& fragFile, const PipelineConfigInfo& configInfo = {});

   private:
	static std::vector<char> readFile(const std::string& filename);

	void createGraphicsPipeline(const std::string& vertFile,
	                            const std::string& fragFile,
	                            const PipelineConfigInfo& configInfo);

	void createShaderModule(const std::vector<char>& code,
	                        VkShaderModule* shaderModule);
	LveDevice& lveDevice;
	VkPipeline graphicsPipeline;
	VkShaderModule vertShaderModule;
	VkShaderModule fragShaderModule;
};
}  // namespace lve