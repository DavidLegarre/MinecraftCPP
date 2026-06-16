#pragma once

#include "Renderer/Mesh.hpp"

class IRenderer {
   public:
    virtual ~IRenderer() = default;

    virtual void BeginFrame() = 0;

    virtual void DrawMesh(const Mesh& mesh) = 0;

    virtual void EndFrame() = 0;
};