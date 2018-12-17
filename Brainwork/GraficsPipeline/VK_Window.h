#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include "VK_Device.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "VK_BufferManager.h"

class VK_Window
{
public:
	VK_Window();

	GLFWwindow*		window;
	void			run();

private:
	size_t			currentFrame		= 0;
	bool			framebufferResized	= false;
	Camera			cam;

	VK_Device		vk_Device			= VK_Device();
	VK_SwapChain	vk_SwapChain		= VK_SwapChain(vk_Device);
	VK_Renderer		renderer			= VK_Renderer(vk_Device, vk_SwapChain);
	VK_BufferManager	vk_Buffer			= VK_BufferManager(renderer);
	

	void			initWindow();
	void			initVulkan();
	void			mainLoop();
	void			drawFrame();

	void			cleanup();
	static void		framebufferResizeCallback(GLFWwindow* window, int width, int height);
};

#endif // !VK_WINDOW_H