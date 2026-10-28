#include <cstdio>
#include <exception>
#include <vector>

#include <glm/glm.hpp>

#include "core/Window.hpp"
#include "render/Mesh.hpp"
#include "render/Shader.hpp"

int main() {
  try {
    core::Window window(1280, 720, "MinecraftCPP");
    render::Shader shader("shaders/basic.vert", "shaders/basic.frag");

    const std::vector<float> triangle = {
        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
    };
    render::Mesh mesh(triangle);

    // Uniform state persists per program, so the constant matrices go outside
    // the loop.
    shader.bind();
    shader.setMat4("uModel", glm::mat4(1.0f));
    shader.setMat4("uView", glm::mat4(1.0f));
    shader.setMat4("uProjection", glm::mat4(1.0f));
    shader.cleanUp();

    while (!window.shouldClose()) {
      window.clear(0.45f, 0.62f, 0.85f);
      mesh.draw();
      window.swapBuffers();
      window.pollEvents();
    }
  } catch (const std::exception &e) {
    std::fprintf(stderr, "%s\n", e.what());
    return 1;
  }

  return 0;
}
