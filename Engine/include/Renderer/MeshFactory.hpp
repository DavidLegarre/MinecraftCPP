#pragma once

#include "Renderer/Mesh.hpp"

class MeshFactory {
   public:
    static Mesh CreateCube();
    static Mesh CreateQuad();
};