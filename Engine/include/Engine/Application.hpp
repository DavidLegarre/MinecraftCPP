#pragma once

#include "Engine/ApplicationConfig.hpp"
#include "Engine/Window.hpp"

class Application {
   public:
    explicit Application(const ApplicationConfig& config);

    void Run();

   private:
    ApplicationConfig m_Config;
    Window m_Window;
};