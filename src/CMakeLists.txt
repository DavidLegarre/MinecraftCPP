add_library(setUp setUp.cpp)
target_include_directories(setUp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(SOURCES
    main.cpp
    setUp.cpp
    device.cpp
)

add_executable(${NAME} ${SOURCES})

target_include_directories(${NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(${NAME} PRIVATE VK_NO_PROTOTYPES)
set_target_properties(${NAME}
    PROPERTIES DEBUGGER_WORKING_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 5. Link libraries
target_link_libraries(${NAME} PRIVATE 
    ${SDL_LIBRARY}
    Vulkan::Vulkan
)