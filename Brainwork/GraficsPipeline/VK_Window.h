
#include "Vulkan.h"

const int WIDTH = 800;
const int HEIGHT = 600;




void VK_initWindow(Vulkan& vulk) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	vulk.window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(vulk.window, &vulk);
	glfwSetFramebufferSizeCallback(vulk.window , VK_framebufferResizeCallback);
}


void VK_framebufferResizeCallback(GLFWwindow* glfwWindow, int width, int height) {
	auto app = reinterpret_cast<Vulkan*>(glfwGetWindowUserPointer(glfwWindow));
	app->framebufferResized = true;
}

void VK_createSurface(Vulkan& vulk) {
	if (glfwCreateWindowSurface(vulk.instance, vulk.window, nullptr, &vulk.surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}
