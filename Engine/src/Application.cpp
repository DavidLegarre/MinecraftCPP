#include "Application.hpp"

#include <memory>
#include <stdexcept>

#include "Events/KeyPressedEvent.hpp"
#include "Renderer/OpenGLRenderer.hpp"

Application::Application(const ApplicationConfig& config)
    : m_Config(config),
      m_EventManager(),
      m_InputSystem(m_EventManager),
      m_Window(config, m_EventManager, m_InputSystem) {
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Initialize renderer after OpenGL context is ready
    m_Renderer = std::make_unique<OpenGLRenderer>(m_Window.GetNativeWindow());

    // Subscribe InputSystem to handle key events
    m_EventManager.Subscribe(
        [this](const Event& event) { m_InputSystem.OnEvent(event); });
}

void Application::Run() {
    while (!m_Window.ShouldClose()) {
        m_Renderer->BeginFrame();
        m_Renderer->DrawScene();
        m_Renderer->EndFrame();

        m_Window.SwapBuffers();
        m_Window.PollEvents();
    }
}