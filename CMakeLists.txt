cmake_minimum_required(VERSION 3.20)
project(MinecraftCPP)

set(CMAKE_CXX_STANDARD 23)

if (NOT IS_DIRECTORY $ENV{VULKAN_SDK})
    message(WARNING "Vulkan SDK not detected, if installed please set VULKAN_SDK env var or manually provide libraries")
else()
    message(STATUS "Found Vulkan SDK in $ENV{VULKAN_SDK}")
endif()

# 1. Define your source files (including the implementation file we created)
set(SOURCES
    main.cpp
    external/tinyobjloader/tiny_obj_loader.cpp # Source file containing the implementation definition
)

# 2. Define the executable
add_executable(MinecraftCPP ${SOURCES})

# 3. Include the directory containing tiny_obj_loader.h
target_include_directories(MinecraftCPP PRIVATE external/tinyobjloader)