#include "Renderer/MeshFactory.hpp"

#include <vector>

#include "Renderer/Vertex.hpp"

Mesh MeshFactory::CreateCube() {
    // Define vertices for a cube with position and UV coordinates
    // Scale cube by 0.5 to make it clearly visible in NDC space
    std::vector<Vertex> vertices = {
        // Front face
        {{-0.25f, -0.25f, 0.25f}, {0.0f, 0.0f}},
        {{0.25f, -0.25f, 0.25f}, {1.0f, 0.0f}},
        {{0.25f, 0.25f, 0.25f}, {1.0f, 1.0f}},
        {{-0.25f, 0.25f, 0.25f}, {0.0f, 1.0f}},

        // Back face
        {{0.25f, -0.25f, -0.25f}, {0.0f, 0.0f}},
        {{-0.25f, -0.25f, -0.25f}, {1.0f, 0.0f}},
        {{-0.25f, 0.25f, -0.25f}, {1.0f, 1.0f}},
        {{0.25f, 0.25f, -0.25f}, {0.0f, 1.0f}},

        // Top face
        {{-0.25f, 0.25f, 0.25f}, {0.0f, 0.0f}},
        {{0.25f, 0.25f, 0.25f}, {1.0f, 0.0f}},
        {{0.25f, 0.25f, -0.25f}, {1.0f, 1.0f}},
        {{-0.25f, 0.25f, -0.25f}, {0.0f, 1.0f}},

        // Bottom face
        {{-0.25f, -0.25f, -0.25f}, {0.0f, 0.0f}},
        {{0.25f, -0.25f, -0.25f}, {1.0f, 0.0f}},
        {{0.25f, -0.25f, 0.25f}, {1.0f, 1.0f}},
        {{-0.25f, -0.25f, 0.25f}, {0.0f, 1.0f}},

        // Right face
        {{0.25f, -0.25f, 0.25f}, {0.0f, 0.0f}},
        {{0.25f, -0.25f, -0.25f}, {1.0f, 0.0f}},
        {{0.25f, 0.25f, -0.25f}, {1.0f, 1.0f}},
        {{0.25f, 0.25f, 0.25f}, {0.0f, 1.0f}},

        // Left face
        {{-0.25f, -0.25f, -0.25f}, {0.0f, 0.0f}},
        {{-0.25f, -0.25f, 0.25f}, {1.0f, 0.0f}},
        {{-0.25f, 0.25f, 0.25f}, {1.0f, 1.0f}},
        {{-0.25f, 0.25f, -0.25f}, {0.0f, 1.0f}},
    };

    // Define indices for cube (2 triangles per face)
    std::vector<uint32_t> indices = {
        // Front face
        0,
        1,
        2,
        0,
        2,
        3,

        // Back face
        4,
        5,
        6,
        4,
        6,
        7,

        // Top face
        8,
        9,
        10,
        8,
        10,
        11,

        // Bottom face
        12,
        13,
        14,
        12,
        14,
        15,

        // Right face
        16,
        17,
        18,
        16,
        18,
        19,

        // Left face
        20,
        21,
        22,
        20,
        22,
        23,
    };

    return Mesh(vertices, indices);
}

Mesh MeshFactory::CreateQuad() {
    float aspect = 1080.0f / 1920.0f;
    float halfSize = 0.25f;
    std::vector<Vertex> vertices = {
        {{-halfSize * aspect, -halfSize, 0.0f}, {0.0f, 0.0f}},
        {{ halfSize * aspect, -halfSize, 0.0f}, {1.0f, 0.0f}},
        {{ halfSize * aspect,  halfSize, 0.0f}, {1.0f, 1.0f}},
        {{-halfSize * aspect,  halfSize, 0.0f}, {0.0f, 1.0f}}
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        0, 2, 3
    };

    return Mesh(vertices, indices);
}

