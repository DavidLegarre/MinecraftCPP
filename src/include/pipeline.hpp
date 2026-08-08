#pragma once

#include "engine_device.hpp"

#include <string>
#include <vector>

namespace lve {

struct PipelineConfigInfo {};
class LvePipeline {
   public:
    LvePipeline(const lve::MyEngineDevice& device, const std::string& vertFile,
                const std::string& fragFile);

   private:
    static std::vector<char> readFile(const std::string& filename);

    void createGraphicsPipeline(const std::string& vertFile,
                                const std::string& fragFile);
};
}  // namespace lve