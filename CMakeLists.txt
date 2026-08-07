cmake_minimum_required(VERSION 3.22)
project(VulkanApp LANGUAGES CXX)

# Require C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include FetchContent module for dynamic dependency management
include(FetchContent)

# Fetch GLFW dynamically
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Fetch GLM dynamically
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

# Locate Vulkan SDK installed on system (CachyOS / Arch)
find_package(Vulkan REQUIRED)

# Define executable target
file(GLOB_RECURSE CPP_SOURCE_FILES "src/*.h" "src/*.cpp")
add_executable(${PROJECT_NAME}
    ${CPP_SOURCE_FILES}
)
target_sources(${PROJECT_NAME} PRIVATE
    src/lve_window.cpp
    src/first_app.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Target-based property linking
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
)

# Target-based compile features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
