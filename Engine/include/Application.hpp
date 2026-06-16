#pragma once

#include "ApplicationConfig.hpp"
#include "InputSystem.hpp"
#include "Window.hpp"

class Application {
   public:
    explicit Application(const ApplicationConfig& config);

    void Run();

   private:
    ApplicationConfig m_Config;
    EventManager m_EventManager;
    InputSystem m_InputSystem;
    Window m_Window;
};
