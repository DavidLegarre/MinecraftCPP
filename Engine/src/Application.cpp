
#include "Application.hpp"

#include <stdexcept>

#include "Events/KeyPressedEvent.hpp"
#include "Renderer/OpenGL.hpp"

Application::Application(const ApplicationConfig& config)
    : m_Config(config), m_EventManager(), m_Window(config, m_EventManager) {
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    m_EventManager.Subscribe([this](const Event& event) {
        if (event.GetEventType() != EventType::KeyPressed) {
            return;
        }

        const auto& keyEvent = static_cast<const KeyPressedEvent&>(event);

        if (keyEvent.GetKey() == GLFW_KEY_Q) {
            m_Window.Close();
        }
    });
}

void Application::Run() {
    while (!m_Window.ShouldClose()) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window.SwapBuffers();
        m_Window.PollEvents();
    }
}