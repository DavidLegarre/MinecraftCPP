#pragma once

#include <string>
#include <vector>

namespace pipeline {
class Pipeline {
  public:
    Pipeline(const std::string &vertFile, const std::string &fragFile);

  private:
    static std::vector<char> readFile(const std::string &filename);

    void createGraphicsPipeline(const std::string &vertFile,
                                const std::string &fragFile);
};
} // namespace pipeline