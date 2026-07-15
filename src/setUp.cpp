#include "setUp.hpp"
#include "utils.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

VkApplicationInfo init() {
    chk(SDL_Init(SDL_INIT_VIDEO));
    chk(SDL_Vulkan_LoadLibrary(NULL));
    volkInitialize();

    VkApplicationInfo appInfo{.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                              .pApplicationName = "How to Vulkan",
                              .apiVersion = VK_API_VERSION_1_3};

    return appInfo;
}

VkInstance getInstance(VkApplicationInfo const& appInfo) {
    VkInstance instance{VK_NULL_HANDLE};
    uint32_t instanceExtensionsCount{0};
    char const* const* instanceExtensions{
        SDL_Vulkan_GetInstanceExtensions(&instanceExtensionsCount)};
    VkInstanceCreateInfo instanceCI{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = instanceExtensionsCount,
        .ppEnabledExtensionNames = instanceExtensions,
    };
    chk_vk(vkCreateInstance(&instanceCI, nullptr, &instance));
    volkLoadInstance(instance);
    return instance;
}
