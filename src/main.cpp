#define VOLK_IMPLEMENTATION
#include <vulkan/vulkan.h>
#include <volk/volk.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <vector>
#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "slang/slang.h"
#include "slang/slang-com-ptr.h"
#include <ktx.h>
#include <ktxvulkan.h>
#include "utils.hpp"
#include "setUp.hpp"
#include "device.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

// Global Variables
uint32_t deviceIndex = 0;  // Select the first device for now

int main() {
    // Make sure asset folder is present from the current working directory

    if (!std::filesystem::is_directory("assets")) {
        std::cerr << "Could not locate assets folder from current working "
                     "directory\n";
        exit(-1);
    }

    VkApplicationInfo appInfo = init();
    VkInstance instance = getInstance(appInfo);
    Device device(instance);
    device.buildQueueFamilies();
    std::cout << "Hello, World! " << device.getDeviceCount()
              << " devices found\n";

    return 0;
}