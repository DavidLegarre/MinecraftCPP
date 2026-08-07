#include "first_app.hpp"

namespace lve {
FirstApp::FirstApp() {}
FirstApp::~FirstApp() {}

void FirstApp::run() {
    while (!lveWindow.shouldClose()) {
        glfwPollEvents();
    }
}
}  // namespace lve