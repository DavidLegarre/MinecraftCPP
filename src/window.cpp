#include "window.hpp"

#include <iostream>

Window::Window(int width, int height, const char* title)
    : m_Width(width), m_Height(height), m_Window(nullptr) {
    this->m_Height = height;
    this->m_Width = width;

    initGLFW();
    this->m_Window =
        glfwCreateWindow(this->m_Width, this->m_Height, title, NULL, NULL);
    if (!this->m_Window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    initGLAD();
}

Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
}

void Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void Window::update() {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void Window::clear(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width,
                                       int height) {
    glViewport(0, 0, width, height);
}