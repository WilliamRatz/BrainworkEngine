#include "VK_Window.h"

int main() {
	VK_Window vulkanWindow;

	try {
		vulkanWindow.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}