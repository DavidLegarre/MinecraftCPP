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

file(GLOB_RECURSE ENGINE_SOURCES "Engine/src/*.cpp")

add_library(Engine
    ${ENGINE_SOURCES}
)

target_include_directories(Engine
    PUBLIC
        Engine/include
)

target_link_libraries(Engine
    PUBLIC
        glad
        ${GLFW_LIBRARIES}
)

add_executable(Minecraft
    Game/src/main.cpp
)

target_link_libraries(Minecraft
    PRIVATE
        Engine
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g
        -O0
        -fsanitize=address
        -fsanitize=undefined
    )

    add_link_options(
        -fsanitize=address
        -fsanitize=undefined
    )
endif()