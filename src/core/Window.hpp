#pragma once

struct GLFWwindow;

namespace core {

// Owns the GLFW window and the OpenGL context. One Window per process.
class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // True when the user asked to quit (window close button or Escape).
    bool shouldClose() const;

    void pollEvents() const;
    void swapBuffers() const;

    // Resizes the viewport to the framebuffer, then clears it.
    void clear(float r, float g, float b) const;

private:
    GLFWwindow* handle_ = nullptr;
};

}  // namespace core
