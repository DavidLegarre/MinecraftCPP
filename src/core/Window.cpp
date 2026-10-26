#include "core/Window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

namespace core {

namespace {

std::string glfwError(const char* what) {
    const char* desc = nullptr;
    glfwGetError(&desc);
    return std::string(what) + ": " + (desc ? desc : "unknown");
}

}  // namespace

Window::Window(int width, int height, const char* title) {
    // shortcut: GLEW 2.2.0 only loads GL through GLX, so force the X11 backend
    // (XWayland) on Wayland sessions. Upgrade to GLAD if native Wayland is needed.
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit()) {
        throw std::runtime_error(glfwError("glfwInit failed"));
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle_) {
        const std::string msg = glfwError("glfwCreateWindow failed");
        glfwTerminate();
        throw std::runtime_error(msg);
    }

    glfwMakeContextCurrent(handle_);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    const GLenum err = glewInit();
    if (err != GLEW_OK) {
        const std::string msg =
            "glewInit failed: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(err)));
        glfwDestroyWindow(handle_);
        glfwTerminate();
        throw std::runtime_error(msg);
    }

    // glewInit leaves a GL_INVALID_ENUM on core profiles; clear it before real work.
    while (glGetError() != GL_NO_ERROR) {
    }
}

Window::~Window() {
    glfwDestroyWindow(handle_);
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle_) || glfwGetKey(handle_, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void Window::pollEvents() const {
    glfwPollEvents();
}

void Window::swapBuffers() const {
    glfwSwapBuffers(handle_);
}

void Window::clear(float r, float g, float b) const {
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(handle_, &width, &height);

    glViewport(0, 0, width, height);
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}  // namespace core
