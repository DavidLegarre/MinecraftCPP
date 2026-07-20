# MyEngineDevice — Vulkan Device Wrapper

`engine::MyEngineDevice` wraps core Vulkan device initialization, resource management, and buffer/image utilities.

## Public API

| Method | Description |
|--------|-------------|
| `MyEngineDevice(window::VkWindow &window)` | Constructs device from window |
| `~MyEngineDevice()` | Tears down device, surface, instance |
| `getCommandPool()` | Returns `VkCommandPool` |
| `device()` | Returns `VkDevice` |
| `surface()` | Returns `VkSurfaceKHR` |
| `graphicsQueue()` | Returns graphics `VkQueue` |
| `presentQueue()` | Returns present `VkQueue` |
| `getSwapChainSupport()` | Returns `SwapChainSupportDetails` for physical device |
| `findMemoryType(typeFilter, properties)` | Returns suitable memory type index |
| `findPhysicalQueueFamilies()` | Returns `QueueFamilyIndices` |
| `findSupportedFormat(candidates, tiling, features)` | Returns first compatible `VkFormat` |
| `createBuffer(size, usage, properties, buffer, memory)` | Creates buffer with device memory |
| `beginSingleTimeCommands()` | Allocates & begins one-shot command buffer |
| `endSingleTimeCommands(commandBuffer)` | Submits, waits, frees command buffer |
| `copyBuffer(src, dst, size)` | Copies data via command buffer |
| `copyBufferToImage(buffer, image, width, height, layers)` | Copies buffer → image |
| `createImageWithInfo(info, properties, image, memory)` | Creates image with device memory |

## Internal lifecycle

```
createInstance() → setupDebugMessenger() → createSurface()
→ pickPhysicalDevice() → createLogicalDevice() → createCommandPool()
```

`pickPhysicalDevice()` selects device with swap chain support, samplers anisotropy, and required queue families.

## Supporting structs

### `SwapChainSupportDetails`
- `capabilities` — `VkSurfaceCapabilitiesKHR`
- `formats` — available `VkSurfaceFormatKHR` list
- `presentModes` — available `VkPresentModeKHR` list

### `QueueFamilyIndices`
- `graphicsFamily` / `presentFamily` — queue family indices
- `graphicsFamilyHasValue` / `presentFamilyHasValue` — validity flags
- `isComplete()` — true when both families found

## Validation layers
Debug builds (`!NDEBUG`): `VK_LAYER_KHRONOS_validation` enabled.
Release builds (`NDEBUG`): disabled.

## Non-copyable / non-movable
Class deletes copy & move constructors/assignments.
