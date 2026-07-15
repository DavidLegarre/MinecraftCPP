#pragma once

#include <volk/volk.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

VkApplicationInfo init();
VkInstance getInstance(VkApplicationInfo const& appInfo);
