#include "Engine/Application.hpp"

#include <stdexcept>

#include "Engine/Application.hpp"
#include "Engine/Renderer/OpenGL.hpp"

Application::Application(const ApplicationConfig& config)
    : m_Config(config), m_Window(config) {
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void Application::Run() {
    while (!m_Window.ShouldClose()) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window.SwapBuffers();
        m_Window.PollEvents();
    }
}