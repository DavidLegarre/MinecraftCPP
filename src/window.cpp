#include "window.hpp"

#include <cstdlib>
#include <iostream>

namespace lve {
LveWindow::LveWindow(int w, int h, const std::string name)
    : width(w), height(h), windowName(name) {
    LveWindow::initWindow();
};

LveWindow::~LveWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
};

void LveWindow::initWindow() {
    if (!glfwInit()) {
        std::cerr << "glfwInit failed (is DISPLAY or WAYLAND_DISPLAY set?)\n";
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "glfwCreateWindow failed\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwShowWindow(window);
};
void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}
}  // namespace lve
