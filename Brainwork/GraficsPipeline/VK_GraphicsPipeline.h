#pragma once
#include "VK_inc.h"

class VK_Renderer;
class VK_SwapChain;
class VK_Device;
class LightManager;

struct LayoutBinding;


class VK_GraphicsPipeline
{
public:
	VK_Renderer*			m_pRenderer;
	VK_SwapChain*			m_pSwapChain;
	VK_Device*				m_pDevice;
	VkPipeline				m_graphicsPipeline;
	VkPipelineLayout		m_pipelineLayout;

	VK_GraphicsPipeline(VK_Renderer& vk_renderer);
	VK_GraphicsPipeline(const VK_GraphicsPipeline& vk_graphicsPipeline);
	~VK_GraphicsPipeline();

	void CreateGraphicsPipeline(std::string p_vertexShader, std::string p_fragmentShader, LayoutBinding& p_uboBindings, LayoutBinding& p_imageSamplerBindings);

	void RecreateGraphicsPipeline(GLFWwindow* window);

	static std::vector<char> ReadFile(const std::string& filename);
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	void CleanUp();
};