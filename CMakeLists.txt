cmake_minimum_required(VERSION 3.20)
set(NAME MinecraftCPP)
project(${NAME} CXX)


set(CMAKE_CXX_STANDARD 23)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(CCACHE_PROGRAM ccache)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Handle Vulkan SDK Paths
if (DEFINED ENV{VULKAN_SDK} AND NOT "$ENV{VULKAN_SDK}" STREQUAL "")
    set(Vulkan_ROOT "$ENV{VULKAN_SDK}")
else()
    set(Vulkan_ROOT "/home/david/vulkan/1.4.350.1/x86_64")
endif()

# Global Header Paths
include_directories(SYSTEM
    $ENV{VULKAN_SDK}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyobj
)

# Find Vulkan SDK and SDL3 Library
find_package(Vulkan REQUIRED)
find_library(SDL_LIBRARY NAMES SDL3 HINTS "$ENV{VULKAN_SDK}/lib" REQUIRED)

add_subdirectory(src)