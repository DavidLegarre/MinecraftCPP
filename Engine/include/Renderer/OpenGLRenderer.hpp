#pragma once

#include <glad/gl.h>

#include <memory>

#include "Renderer/IRenderer.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"

class OpenGLRenderer : public IRenderer {
   public:
    OpenGLRenderer(GLFWwindow* window);
    ~OpenGLRenderer() override;

    void BeginFrame() override;
    void DrawMesh(const Mesh& mesh) override;
    void DrawScene() override;
    void EndFrame() override;

   private:
    GLFWwindow* m_Window;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texture;
    std::unique_ptr<Mesh> m_CubeMesh;

    void CreateShaderProgram();
    void CreateGeometry();
    void CreateTestTexture();
};
