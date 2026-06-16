#pragma once

#include "ApplicationConfig.hpp"
#include "Events/EventManager.hpp"

struct GLFWwindow;

class Window {
   public:
    Window(const ApplicationConfig& config, EventManager& eventManager);
    ~Window();

    bool ShouldClose() const;

    void PollEvents() const;
    void SwapBuffers() const;
    void Close();

    GLFWwindow* GetNativeWindow() const;

   private:
    GLFWwindow* m_Window;
    EventManager& m_EventManager;
    static void KeyCallback(GLFWwindow* window, int key, int scancode,
                            int action, int mods);
};
