cmake_minimum_required(VERSION 3.20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    main.cpp
    # player.cpp, world.cpp, etc.
)

add_executable(${NAME} ${SOURCES})

target_compile_definitions(${NAME} PRIVATE VK_NO_PROTOTYPES)

set_target_properties(${NAME} PROPERTIES DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${NAME} PRIVATE
    ${Vulkan_INCLUDE_DIRS}
    ${VULKAN_ROOT}/include
    external/tinyobj
)
