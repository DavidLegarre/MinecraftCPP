#pragma once

#include "engine_device.hpp"

#include <string>
#include <vector>

namespace pipeline {

struct PipelineConfigInfo {};
class Pipeline {
  public:
    Pipeline(const engine::MyEngineDevice &device, const std::string &vertFile,
             const std::string &fragFile);

  private:
    static std::vector<char> readFile(const std::string &filename);

    void createGraphicsPipeline(const std::string &vertFile, const std::string &fragFile);
};
} // namespace pipeline