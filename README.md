# MinecraftCPP
Small C++ Vulkan/SDL3 project for learning purposes.

## Fedora dependencies
Install build dependencies on Fedora with:

```bash
sudo dnf install -y \
  gcc-c++ cmake make \
  vulkan-headers vulkan-loader-devel vulkan-utility-libraries-devel \
  SDL3-devel glm-devel volk-devel \
  VulkanMemoryAllocator-devel slang-devel \
  ktx-software
```

The project also uses the vendored tinyobjloader code in the external directory, so no extra package is required for that part.

## Build
From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run
After building:

```bash
./build/MinecraftCPP
```

If your Vulkan SDK is installed outside the default system paths, set VULKAN_SDK before configuring:

```bash
export VULKAN_SDK=/path/to/vulkan-sdk
cmake -S . -B build
```
