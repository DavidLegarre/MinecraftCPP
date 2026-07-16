find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(SDL3 REQUIRED sdl3)

add_executable(${PROJECT_NAME}
    main.cpp
    app.cpp
    pipeline.cpp
    window.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLFW_INCLUDE_DIRS}
    ${SDL3_INCLUDE_DIRS}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE VK_NO_PROTOTYPES)

set_target_properties(${PROJECT_NAME}
    PROPERTIES DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW_LIBRARIES}
    ${SDL3_LIBRARIES}
    Vulkan::Vulkan
)