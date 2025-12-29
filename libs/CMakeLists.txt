add_subdirectory(glfw)

add_subdirectory(glm)

add_subdirectory(VulkanMemoryAllocator)

add_subdirectory(SDL)

add_subdirectory(vk-bootstrap)

add_subdirectory(fmt)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb)

add_subdirectory(fastgltf)

# Linking imgui 
#add_subdirectory(imguii)




