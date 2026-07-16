#pragma once

#include "window.hpp"

namespace app {
class App {
  public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

  private:
    window::VkWindow window{WIDTH, HEIGHT, "Hello Vulkan!"};
};
} // namespace app