#define GLFW_INCLUDE_VULKAN

#include "VK_Window.h"

int main() {
	VK_Window vk_Window;

	try {
		vk_Window.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}