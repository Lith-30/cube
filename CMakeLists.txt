cmake_minimum_required(VERSION 3.16)
project(cubedrawer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
# Import Vulkan
find_package(Vulkan REQUIRED)
# import all installed libraries
add_subdirectory(libs)

add_executable(${PROJECT_NAME} drawer.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PRIVATE GPUOpen::VulkanMemoryAllocator)
target_link_libraries(${PROJECT_NAME} PRIVATE vk-bootstrap::vk-bootstrap)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)







