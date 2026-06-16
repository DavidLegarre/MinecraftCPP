#pragma once

#include <glad/gl.h>
#include "Renderer/IRenderer.hpp"

class OpenGLRenderer : public IRenderer {
   public:
    OpenGLRenderer(GLFWwindow* window);
    ~OpenGLRenderer() override;

    void BeginFrame() override;
    void DrawMesh(const Mesh& mesh) override;
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
