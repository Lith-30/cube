cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(cubedrawer)


# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
# Import Vulkan
find_package(Vulkan REQUIRED)
add_subdirectory(libs)

# import all installed libraries
add_executable(${PROJECT_NAME} 
	main.cpp
	vk_descriptors.cpp
	vk_engine.cpp
	vk_images.cpp
	vk_initalisers.cpp
	vk_loader.cpp
	vk_pipelines.cpp
)
# Make sure that Vulkan is linked before we make execuables
target_link_libraries(${PROJECT_NAME} PRIVATE 
	glm
	glfw
	VulkanMemoryAllocator
	vk-bootstrap::vk-bootstrap
	SDL3::SDL3
	stb
	fmt
	Vulkan::Vulkan
)

get_target_property(VK_INCS Vulkan::Vulkan INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "Vulkan Headers: " ${VK_INCS})






