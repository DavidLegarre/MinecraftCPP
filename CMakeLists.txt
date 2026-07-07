cmake_minimum_required(VERSION 3.20)
project(MinecraftCPP)

set(CMAKE_CXX_STANDARD 23)

# System-installed packages (via dnf/flatpak)
find_package(glfw3 REQUIRED)

# Tell CMake where to look for GLAD's headers
include_directories(lib/glad/include)

# Gather all source files
add_executable(MinecraftCPP 
    src/main.cpp 
    lib/glad/src/glad.c
)

target_link_libraries(MinecraftCPP PRIVATE glfw)