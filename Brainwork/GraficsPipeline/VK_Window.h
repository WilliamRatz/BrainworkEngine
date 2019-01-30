#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include "VK_Device.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "VK_GameObjectManager.h"
#include "VK_GraphicsPipeline.h"
#include "LightManager.h"
#include "Camera.h"

class VK_Window
{
public:
	VK_Window();

	GLFWwindow*		window;
	void			run();

private:
	bool			framebufferResized	= false;
	size_t			currentFrame		= 0;
	Camera			cam;

	VK_Device							vk_device				= VK_Device();
	VK_SwapChain						vk_swapChain			= VK_SwapChain(vk_device);
	std::vector<VK_Renderer>			vk_renderers			= { VK_Renderer(vk_swapChain, RendererCreatInfo(true, true)), VK_Renderer(vk_swapChain, RendererCreatInfo(false, true)) };
	std::vector<VK_GraphicsPipeline>	vk_graphicsPipelines	= { VK_GraphicsPipeline(vk_renderers[0]), VK_GraphicsPipeline(vk_renderers[1]) };
	VK_GameObjectManager				vk_gameObjectManager	= VK_GameObjectManager(vk_renderers[0]); //renderer 0 color and depth Image
	LightManager						vk_lightManager			= LightManager(vk_renderers[1]); //renderer 1 only depth Image
	

	void			initWindow();
	void			initVulkan();
	void			initObjects();

	void			mainLoop();
	void			drawFrame();

	void			cleanup();
	static void		framebufferResizeCallback(GLFWwindow* window, int width, int height);
};

#endif // !VK_WINDOW_H