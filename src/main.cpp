#include <cstdio>
#include <exception>

#include "core/Window.hpp"

int main() {
    try {
        core::Window window(1280, 720, "MinecraftCPP");

        while (!window.shouldClose()) {
            window.clear(0.45f, 0.62f, 0.85f);
            window.swapBuffers();
            window.pollEvents();
        }
    } catch (const std::exception& e) {
        std::fprintf(stderr, "%s\n", e.what());
        return 1;
    }

    return 0;
}
