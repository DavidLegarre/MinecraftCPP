#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "lve_device.hpp"

namespace lve {
class App {
   public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	void run();

   private:
	LveWindow window{WIDTH, HEIGHT, "Hello Vulkan!"};
	LveDevice device{window};
	LvePipeline pipeline{
	    device,
	    "assets/simple_shader.vert.spv",
	    "assets/simple_shader.frag.spv",
	    LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
};
}  // namespace lve