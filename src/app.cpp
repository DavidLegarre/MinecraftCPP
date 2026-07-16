#include "app.hpp"

namespace app {
void App::run() {
    while (!window.shouldClose()) {
        glfwPollEvents();
    }
};
} // namespace app
