
#include "Application.hpp"

#include <stdexcept>

#include "Renderer/OpenGL.hpp"

Application::Application(const ApplicationConfig& config)
    : m_Config(config), m_EventManager(), m_Window(config, m_EventManager) {
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void Application::Run() {
    while (!m_Window.ShouldClose()) {
        if (glfwGetKey(m_Window.GetNativeWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            m_Window.Close();
        }
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window.SwapBuffers();
        m_Window.PollEvents();
    }
}