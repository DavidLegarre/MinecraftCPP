cmake_minimum_required(VERSION 3.20)

project(MinecraftCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

add_library(glad
    External/glad/src/gl.c
)

target_include_directories(glad
    PUBLIC
        External/glad/include
)

add_executable(Minecraft
    Game/src/main.cpp
)

target_include_directories(Minecraft
    PRIVATE
        ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(Minecraft
    PRIVATE
        glad
        ${GLFW_LIBRARIES}
)