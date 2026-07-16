#pragma once

#include "window.hpp"
#include "pipeline.hpp"

namespace app {
class App {
  public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

  private:
    window::VkWindow window{WIDTH, HEIGHT, "Hello Vulkan!"};
    pipeline::Pipeline pipeline{"assets/simple_shader.vert.spv",
                                "assets/simple_shader.frag.spv"};
};
} // namespace app