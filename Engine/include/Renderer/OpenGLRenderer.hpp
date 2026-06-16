#pragma once

#include "Renderer/IRenderer.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class OpenGLRenderer : public IRenderer {
   public:
    OpenGLRenderer(GLFWwindow* window);
    ~OpenGLRenderer() override;

    void BeginFrame() override;
    void EndFrame() override;

    void RenderTriangle();

   private:
    GLFWwindow* m_Window;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_ShaderProgram;

    void CreateShaderProgram();
    void CreateGeometry();
};
