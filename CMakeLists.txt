cmake_minimum_required(VERSION 3.16)
project(cubedrawer)

#Importing Vulkan
find_package(Vulkan REQUIRED)

# Importing the GLFW library
add_subdirectory(libs/glfw)

# import the GLM library
add_subdirectory(libs/glm)

add_executable(${PROJECT_NAME} drawer.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)




