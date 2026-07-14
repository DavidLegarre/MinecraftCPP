#include <stdio.h>
#include <vulkan/vulkan.h>

int main() {
    VkApplicationInfo appInfo{.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                              .pApplicationName = "How to Vulkan",
                              .apiVersion = VK_API_VERSION_1_3};
    printf("Hello, World!\n");
    return 0;
}