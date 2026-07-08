// Window.hpp
#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <memory>

class Window {
   public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const { return glfwWindowShouldClose(m_Window); }
    void update();  // Swaps buffers and polls events
    void clear(float r, float g, float b, float a) const;

    GLFWwindow* getNativeWindow() const { return m_Window; }

   private:
    GLFWwindow* m_Window;
    int m_Width, m_Height;

    void initGLFW();
    void initGLAD();

    // Callbacks can be mapped safely via static bridge helpers
    static void framebuffer_size_callback(GLFWwindow* window, int width,
                                          int height);
};