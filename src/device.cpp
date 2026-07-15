#include "device.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

Device::Device(VkInstance instance) {
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        std::cerr << "Failed to find any GPUs with Vulkan support.\n";
        std::exit(-1);
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    uint32_t deviceIndex = 0;  // Select the first device for now
    m_physicalDevice = devices[deviceIndex];

    VkPhysicalDeviceProperties2 deviceProperties{
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};
    vkGetPhysicalDeviceProperties2(m_physicalDevice, &deviceProperties);
    std::cout << "Selected device: " << deviceProperties.properties.deviceName
              << "\n";
}

Device::~Device() {
    // Physical devices are owned by the Instance.
    // They don't need explicit destruction here!
}

void Device::buildQueueFamilies() {
    uint32_t queueFamilyCount{0};
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice,
                                             &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(
        m_physicalDevice, &queueFamilyCount, queueFamilies.data());
    uint32_t queueFamily{0};
    for (size_t i = 0; i < queueFamilies.size(); i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueFamily = i;
            break;
        }
    }

    chk(SDL_Vulkan_GetPresentationSupport(m_instance, m_physicalDevice,
                                          queueFamily));

    const float qfpriorities{1.0f};
    VkDeviceQueueCreateInfo queueCI{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = queueFamily,
        .queueCount = 1,
        .pQueuePriorities = &qfpriorities};
}