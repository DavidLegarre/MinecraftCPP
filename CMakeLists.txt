cmake_minimum_required(VERSION 3.20)
set(NAME MinecraftCPP)
project(${NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if (DEFINED ENV{VULKAN_SDK} AND NOT "$ENV{VULKAN_SDK}" STREQUAL "")
    set(VULKAN_ROOT "$ENV{VULKAN_SDK}")
else()
    set(VULKAN_ROOT "/home/david/vulkan/1.4.350.1/x86_64")
endif()

if (NOT IS_DIRECTORY "${VULKAN_ROOT}")
    message(WARNING "Vulkan SDK not detected, if installed please set VULKAN_SDK env var or manually provide libraries")
else()
    message(STATUS "Found Vulkan SDK in ${VULKAN_ROOT}")
endif()



find_package(Vulkan REQUIRED)
set(KTX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/ktx)
set(KTX_SOURCES
    ${KTX_DIR}/lib/texture.c
    ${KTX_DIR}/lib/hashlist.c
    ${KTX_DIR}/lib/checkheader.c
    ${KTX_DIR}/lib/swap.c
    ${KTX_DIR}/lib/memstream.c
    ${KTX_DIR}/lib/filestream.c
    ${KTX_DIR}/lib/vkloader.c)

find_library(SDL_LIBRARY NAMES SDL3 HINTS "${VULKAN_ROOT}/lib" REQUIRED)
find_library(Slang_LIBRARY NAMES slang slang-compiler HINTS "${VULKAN_ROOT}/lib" REQUIRED)


add_subdirectory(src)      # Runs src/CMakeLists.txt second

set_target_properties(${NAME} PROPERTIES DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_20)
target_link_libraries(${NAME} PRIVATE ${SDL_LIBRARY} ktx ${Slang_LIBRARY})