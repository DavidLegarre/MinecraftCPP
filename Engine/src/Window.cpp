#include "Window.hpp"

#include <stdexcept>

#include "Events/Event.hpp"
#include "Events/KeyPressedEvent.hpp"
#include "Events/EventManager.hpp"
#include "Renderer/OpenGL.hpp"

// Window Constructor
Window::Window(const ApplicationConfig& config, EventManager& eventManager)
    : m_Window(nullptr), m_EventManager(eventManager) {
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

    glfwSetWindowUserPointer(m_Window, this);

    glfwSetKeyCallback(m_Window, KeyCallback);

    glfwMakeContextCurrent(m_Window);
}

// Window Destructor
Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_Window); }

void Window::PollEvents() const { glfwPollEvents(); }

void Window::SwapBuffers() const { glfwSwapBuffers(m_Window); }

void Window::Close() { glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

GLFWwindow* Window::GetNativeWindow() const { return m_Window; }

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        KeyPressedEvent event(key);

        self->m_EventManager.Dispatch(event);
    }
}