#include "Renderer/OpenGLRenderer.hpp"

#include <iostream>
#include <stdexcept>
#include <stb_image.h>

#include "Renderer/MeshFactory.hpp"

extern unsigned char* load_stone_image(int& width, int& height, int& channels);

OpenGLRenderer::OpenGLRenderer(GLFWwindow* window) : m_Window(window) {
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable face culling for better performance
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    std::cout << "Initializing OpenGLRenderer..." << std::endl;
    CreateShaderProgram();
    CreateGeometry();
    CreateTestTexture();
    std::cout << "OpenGLRenderer initialized successfully" << std::endl;
}

OpenGLRenderer::~OpenGLRenderer() {
    // Cleanup is handled by unique_ptr destructors
}

void OpenGLRenderer::BeginFrame() {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::EndFrame() {
    // Nothing needed here for now
}

void OpenGLRenderer::DrawMesh(const Mesh& mesh) {
    m_Shader->Use();
    m_Shader->SetUniform1i("uTexture", 0);
    
    if (m_Texture) {
        m_Texture->Bind(0);
    }

    mesh.Bind();
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::DrawScene() {
    if (m_CubeMesh) {
        DrawMesh(*m_CubeMesh);
    } else {
        std::cerr << "ERROR: Scene mesh is null!" << std::endl;
    }
}

void OpenGLRenderer::CreateShaderProgram() {
    try {
        m_Shader = std::make_unique<Shader>("Engine/assets/shaders/basic.vert",
                                            "Engine/assets/shaders/basic.frag");
    } catch (const std::exception& e) {
        throw std::runtime_error(
            std::string("Failed to create shader program: ") + e.what());
    }
}

void OpenGLRenderer::CreateGeometry() {
    try {
        m_CubeMesh = std::make_unique<Mesh>(MeshFactory::CreateCube());
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to create cube mesh: ") +
                                 e.what());
    }
}

void OpenGLRenderer::CreateTestTexture() {
    try {
        int width, height, channels;
        unsigned char* data = load_stone_image(width, height, channels);
        if (data) {
            m_Texture = std::make_unique<Texture>(data, width, height, channels);
            stbi_image_free(data);
            std::cout << "Loaded stone texture successfully using load_image.cpp" << std::endl;
        } else {
            throw std::runtime_error("load_stone_image returned null data");
        }
    } catch (const std::exception& e) {
        std::cerr << "Warning: Failed to load stone texture: " << e.what() << std::endl;
        // Fallback to default texture if stone texture fails
        try {
            m_Texture =
                std::make_unique<Texture>("Engine/assets/textures/default.png");
        } catch (const std::exception& fallback_error) {
            std::cerr << "Warning: Failed to load fallback default texture: " << fallback_error.what()
                      << std::endl;
        }
    }
}
