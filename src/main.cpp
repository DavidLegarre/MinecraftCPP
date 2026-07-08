#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <shader.hpp>
#include <window.hpp>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    Window gameWindow(SCR_WIDTH, SCR_HEIGHT, "MinecraftCPP");
    Shader shaderProgram;

    while (!gameWindow.shouldClose()) {
        processInput(gameWindow.getNativeWindow());
        // Render operations
        gameWindow.clear(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram.use();

        // Buffer Swapping & IO Polling
        gameWindow.update();
    }
}
