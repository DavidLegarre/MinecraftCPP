cmake_minimum_required(VERSION 3.20)
project(MinecraftCPP)

set(CMAKE_CXX_STANDARD 23)

# 1. Define your source files (including the implementation file we created)
set(SOURCES
    main.cpp
    external/tinyobjloader/tiny_obj_loader.cpp # Source file containing the implementation definition
)

# 2. Define the executable
add_executable(MinecraftCPP ${SOURCES})

# 3. Include the directory containing tiny_obj_loader.h
target_include_directories(MinecraftCPP PRIVATE external/tinyobjloader)