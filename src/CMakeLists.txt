# ── Dependencies ──────────────────────────────────────────
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# ── Target ────────────────────────────────────────────────
add_executable(${PROJECT_NAME}
    main.cpp
    app.cpp
    pipeline.cpp
    window.cpp
    engine_device.cpp
)

# ── Include Directories ───────────────────────────────────
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLFW_INCLUDE_DIRS}
)

# ── Compile Defines ───────────────────────────────────────

# ── Properties ────────────────────────────────────────────
set_target_properties(${PROJECT_NAME}
    PROPERTIES DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# ── Link Libraries ────────────────────────────────────────
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW_LIBRARIES}
    Vulkan::Vulkan
)
