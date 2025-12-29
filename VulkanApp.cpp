#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#incl
#include <cstdlib>

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 800

GLFWwindow *window = NULL;

void GLFW_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


class VulkanApp {

public:
	VulkanApp() {

	}

	~VulkanApp() {

	}

	void Init(const char *pAppName) {
		m_vkCore.Init(pAppName);
	}

	void RenderScene() {

	}

private:
	Vulkan::VulkanCore m_vkCore;	

}

