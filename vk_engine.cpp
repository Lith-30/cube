#include "vk_engine.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#include "vk_initalisers.h"
#include "vk_types.h"

#include <VkBootstrap.h>

#include <chrono>
#include <thread>
#include <iostream>

// #define VK_CHECK(x)				\
// 	do {					\
// 		VkResult err = x;		\
// 		if (err) {			\
// 			std::cout << "Detected Vulkan Error: " << err << std::endl;	\
// 			abort();		\
// 		}				\
// 	} while (0)				\

constexpr bool bUseValidationLayers = false;

VulkanEngine *loadedEngine = nullptr;

VulkanEngine &VulkanEngine::Get() {return *loadedEngine; }
void VulkanEngine::init() {
	assert(loadedEngine == nullptr);
	_isIntialised = false;


	SDL_Init(SDL_INIT_VIDEO);

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);
	_window = SDL_CreateWindow(
		"Vulkan Engine", 
		_windowExtent.width, 
		_windowExtent.height, 
		window_flags);

	init_vulkan();
	init_swapchain();
	init_commands();
	_isIntialised = true;

}

void VulkanEngine::init_vulkan() {
	vkb::InstanceBuilder builder;

	auto inst_ret = builder.set_app_name("Vulkan Application")
		.request_validation_layers(true)
		.require_api_version(1, 1, 0)
		.use_default_debug_messenger()
		.build();
	vkb::Instance vkb_inst = inst_ret.value();

	_instance = vkb_inst.instance;
	_debug_messenger = vkb_inst.debug_messenger;
	SDL_Vulkan_CreateSurface(_window, _instance, nullptr, &_surface);

	vkb::PhysicalDeviceSelector selector{ vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1, 1)
		.set_surface(_surface)
		.select()
		.value();

	vkb::DeviceBuilder deviceBuilder{ physicalDevice };
	vkb::Device vkbDevice = deviceBuilder.build().value();

	_device = vkbDevice.device;
	_chosenGPU = physicalDevice.physical_device;

	_graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
	_graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

}

void VulkanEngine::init_swapchain() {
	vkb::SwapchainBuilder swapchainBuilder{_chosenGPU, _device, _surface};

	vkb::Swapchain vkbSwapchain = swapchainBuilder
		.use_default_format_selection()
		.set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
		.set_desired_extent(_windowExtent.width, _windowExtent.height)
		.build()
		.value();

	_swapchain = vkbSwapchain.swapchain;
	_swapchainImages = vkbSwapchain.get_images().value();
	_swapchainImageViews = vkbSwapchain.get_image_views().value();

	_swapchainImageFormat = vkbSwapchain.image_format;
}

void VulkanEngine::cleanup() {
	if (_isIntialised) {
		vkDestroySwapchainKHR(_device, _swapchain, nullptr);

		for (int i = 0; i < _swapchainImageViews.size(); i++) {
			vkDestroyImageView(_device, _swapchainImageViews[i], nullptr);
		}

		vkDestroyDevice(_device, nullptr);
		vkDestroySurfaceKHR(_instance, _surface, nullptr);
		vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
		vkDestroyInstance(_instance, nullptr);
		SDL_DestroyWindow(_window);
	}
}

void VulkanEngine::draw() {
	// empty
}

void VulkanEngine::run() {
	SDL_Event e;
	bool bQuit = false;

	while (!bQuit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_EVENT_QUIT) {
				bQuit = true;
			}
			// if (e.type == SDL_EVENT_WINDOW) {
			// 	if (e.window.event == SDL_WINDOWEVENT_MINIMIZED) {
			// 		stop_rendering = true;
			// 	}
			// 	if (e.window.event == SDL_WINDOWEVENT_RESTORED) {
			// 		stop_rendering = false;
			// 	}
			// }
			if (e.type == SDL_EVENT_WINDOW_MINIMIZED) {
				stop_rendering = true;
			}
			if (e.type == SDL_EVENT_WINDOW_RESTORED) {
				stop_rendering = false;
			}
		}

		if (stop_rendering) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		draw();
	}

}

void VulkanEngine::init_commands() {
	VkCommandPoolCreateInfo commandPoolInfo = {};
	commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolInfo.pNext = nullptr;

	commandPoolInfo.queueFamilyIndex = _graphicsQueueFamily;

	commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	VK_CHECK(vkCreateCommandPool(_device, &commandPoolInfo, nullptr, &_commandPool));

	VkCommandBufferAllocateInfo cmdAllocInfo = {};
	cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdAllocInfo.pNext = nullptr;

	cmdAllocInfo.commandPool = _commandPool;
	cmdAllocInfo.commandBufferCount = 1;
	cmdAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	VK_CHECK(vkAllocateCommandBuffers(_device, &cmdAllocInfo, &_mainCommandBuffer));
}
