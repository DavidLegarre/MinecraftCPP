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

    const std::vector<const char*> deviceExtensions{
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    VkPhysicalDeviceVulkan12Features enabledVk12Features{
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
        .descriptorIndexing = true,
        .shaderSampledImageArrayNonUniformIndexing = true,
        .descriptorBindingVariableDescriptorCount = true,
        .runtimeDescriptorArray = true,
        .bufferDeviceAddress = true};
    VkPhysicalDeviceVulkan13Features enabledVk13Features{
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
        .pNext = &enabledVk12Features,
        .synchronization2 = true,
        .dynamicRendering = true,
    };
    VkPhysicalDeviceFeatures enabledVk10Features{.samplerAnisotropy = VK_TRUE};

    const auto& queueCreateInfo = device.getQueueCreateInfo();
    VkDeviceCreateInfo deviceCI{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &enabledVk13Features,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = &enabledVk10Features};
    VkDevice logicalDevice{VK_NULL_HANDLE};
    chk(vkCreateDevice(device.getPhysicalDevice(), &deviceCI, nullptr,
                       &logicalDevice));

    return 0;
}