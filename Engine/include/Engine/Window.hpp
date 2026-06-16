#pragma once

#include "Engine/ApplicationConfig.hpp"

struct GLFWwindow;

class Window {
   public:
    Window(const ApplicationConfig& config);
    ~Window();

    bool ShouldClose() const;

    void PollEvents() const;
    void SwapBuffers() const;

    GLFWwindow* GetNativeWindow() const;

   private:
    GLFWwindow* m_Window;
};
