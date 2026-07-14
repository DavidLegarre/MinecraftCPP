cmake_minimum_required(VERSION 3.20)
set(NAME MinecraftCPP)
project(${NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if (NOT IS_DIRECTORY $ENV{VULKAN_SDK})
    message(WARNING "Vulkan SDK not detected, if installed please set VULKAN_SDK env var or manually provide libraries")
else()
    message(STATUS "Found Vulkan SDK in $ENV{VULKAN_SDK}")
endif()

include_directories(SYSTEM $ENV{VULKAN_SDK}/include)
include_directories(external/tinyobj)

find_package (Vulkan REQUIRED)

find_library(SDL_LIBRARY NAMES SDL3 HINTS "$ENV{VULKAN_SDK}/lib" REQUIRED)
find_library(Slang_LIBRARY NAMES slang slang-compiler HINTS "$ENV{VULKAN_SDK}/lib" REQUIRED)

add_executable(${NAME} main.cpp )
target_compile_definitions(${NAME} PRIVATE VK_NO_PROTOTYPES)

set_target_properties(${NAME} PROPERTIES DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_20)
target_link_libraries(${NAME} PRIVATE ${SDL_LIBRARY} ktx ${Slang_LIBRARY})