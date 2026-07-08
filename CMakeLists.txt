cmake_minimum_required(VERSION 3.20)
project(MinecraftCPP)

set(CMAKE_CXX_STANDARD 23)

find_package(glfw3 REQUIRED)

# Gather all source files
add_executable(MinecraftCPP src/main.cpp 
)

target_sources(MinecraftCPP PRIVATE 
    lib/glad/src/glad.c

    src/shader.cpp
    src/mesh.cpp
    src/window.cpp
)

target_include_directories(MinecraftCPP PRIVATE 
    lib/glad/include
    include                 # <--- Adds the src folder so headers can find each other
)

target_link_libraries(MinecraftCPP PRIVATE glfw)