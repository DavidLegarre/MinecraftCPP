#include <iostream>
#include <vulkan/vulkan.h>

inline void chk(bool result) {
    if (!result) {
        std::cerr << "Vulkan call returned an error (" << result << ")\n";
        std::exit(result);
    }
}

inline void chk_vk(VkResult result) {
    if (result != VK_SUCCESS) {
        std::cerr << "Vulkan call returned an error (" << result << ")\n";
        std::exit(result);
    }
}