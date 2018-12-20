#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include "VK_Device.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "VK_BufferManager.h"
#include "VK_GraphicsPipeline.h"

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

	VK_Device			vk_Device			= VK_Device();
	VK_SwapChain		vk_swapChain		= VK_SwapChain(vk_Device);
	VK_Renderer			vk_renderer			= VK_Renderer(vk_swapChain);
	VK_BufferManager	vk_bufferManager	= VK_BufferManager(vk_renderer);
	VK_GraphicsPipeline vk_graphicsPipeline = VK_GraphicsPipeline(vk_renderer);
	

	void			initWindow();
	void			initVulkan();
	void			mainLoop();
	void			drawFrame();

	void			cleanup();
	static void		framebufferResizeCallback(GLFWwindow* window, int width, int height);
};

#endif // !VK_WINDOW_H