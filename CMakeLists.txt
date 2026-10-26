cmake_minimum_required(VERSION 3.20)
project(MinecraftCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(minecraft ${SOURCES})

target_include_directories(minecraft PRIVATE src)
target_link_libraries(minecraft PRIVATE glfw GLEW::GLEW glm::glm OpenGL::GL)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(minecraft PRIVATE -Wall -Wextra -g)
endif()
