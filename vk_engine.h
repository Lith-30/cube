#pragma once
#include <vulkan/vulkan_core.h>
#include <vulkan/vk_enum_string_helper.h>
#include <vector>

class VulkanEngine {
public:
	// Vulkan Instance Management
	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debug_messenger;
	VkPhysicalDevice _chosenGPU;
	VkDevice _device;
	VkSurfaceKHR _surface;

	// Swapchain management
	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat;
	std::vector<VkImage> _swapchainImages;
	std::vector<VkImageView> _swapchainImageViews;
	
	// Window Management
	bool _isIntialised{ false };
	int _frameNumber{0};
	bool stop_rendering{ false};
	VkExtent2D _windowExtent{1700, 900};

	// Command Buffer
	VkQueue _graphicsQueue;
	uint32_t _graphicsQueueFamily;

	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;

	struct SDL_Window *_window{ nullptr };

	static VulkanEngine& Get();

	void init();

	void cleanup();

	void draw();

	void run();

private:
	void init_vulkan();

	void init_swapchain();

	void init_commands();
};
