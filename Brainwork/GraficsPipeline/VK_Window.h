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

	GLFWwindow*		m_pWindow;
	void			run();

private:
	bool			m_framebufferResized	= false;
	size_t			m_currentFrame		= 0;
	Camera			m_cam;

	VK_Device							m_device			= VK_Device();
	VK_SwapChain						m_swapChain			= VK_SwapChain(m_device);
	std::vector<VK_Renderer>			m_renderers			= { VK_Renderer(m_swapChain, RendererCreatInfo(true, true)), VK_Renderer(m_swapChain, RendererCreatInfo(false, true)) };
	std::vector<VK_GraphicsPipeline>	m_graphicsPipelines	= { VK_GraphicsPipeline(m_renderers[0]), VK_GraphicsPipeline(m_renderers[1]) };
	std::vector<VK_GameObjectManager>	m_gameObjectManager = { VK_GameObjectManager(m_renderers[0])}; //renderer 0 color and depth Image
	LightManager						m_lightManager		= LightManager(m_renderers[1]); //renderer 1 only depth Image
	

	void			InitWindow();
	void			InitVulkan();
	void			InitObjects();

	void			MainLoop();
	void			NextFrame();

	void			Cleanup();
	static void		FramebufferResizeCallback(GLFWwindow* window, int width, int height);
};

#endif // !VK_WINDOW_H