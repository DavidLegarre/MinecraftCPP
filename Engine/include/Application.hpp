#pragma once

#include "ApplicationConfig.hpp"
#include "Window.hpp"

class Application {
   public:
    explicit Application(const ApplicationConfig& config);

    void Run();

   private:
    ApplicationConfig m_Config;
    Window m_Window;
    EventManager m_EventManager;
};