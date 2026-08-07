#pragma once

#include lve_window.hpp

namespace lve {
class FirstApp {
   public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    FirstApp();
    ~FirstApp();

    void run(){};

   private:
    LveWindow lveWindow{WIDTH, HEIGHT, "VulkanEngine"};
};
}  // namespace lve