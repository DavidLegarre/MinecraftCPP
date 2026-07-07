cmake_minimum_required(VERSION 3.20)
project(MinecraftCPP)

set(CMAKE_CXX_STANDARD 23)

find_package(glfw3 REQUIRED)

add_executable(MinecraftCPP main.cpp)

# Using the official imported target from find_package
target_link_libraries(MinecraftCPP PRIVATE glfw)