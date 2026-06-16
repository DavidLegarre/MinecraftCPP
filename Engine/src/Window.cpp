#include "Engine/Window.hpp"

#include <stdexcept>

#include "Engine/Renderer/OpenGL.hpp"

// Window Constructor
Window::Window(const ApplicationConfig& config) : m_Window(nullptr) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(config.WindowWidth, config.WindowHeight,
                                config.WindowTitle, nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_Window);
}

// Window Destructor
Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_Window); }

void Window::PollEvents() const { glfwPollEvents(); }

void Window::SwapBuffers() const { glfwSwapBuffers(m_Window); }

GLFWwindow* Window::GetNativeWindow() const { return m_Window; }