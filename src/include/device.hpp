#pragma once

#include <volk/volk.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

class Device {
   public:
    Device(VkInstance instance);
    ~Device();

    // Accessors
    uint32_t getDeviceCount() const { return deviceCount; }
    VkPhysicalDevice getPhysicalDevice() const { return m_physicalDevice; }

    void buildQueueFamilies();

   private:
    uint32_t deviceCount{0};
    VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
    VkInstance m_instance{VK_NULL_HANDLE};
};