#pragma once

#include "VK_inc.h"

class VK_Renderer;
class VK_SwapChain;
class VK_Device;
class VK_BufferManager;


class VK_GraphicsPipeline
{
public:
	VK_Renderer*			vk_renderer;
	VK_SwapChain*			vk_swapChain;
	VK_Device*				vk_device;
	VkPipeline				graphicsPipeline;
	VkPipelineLayout		pipelineLayout;

	VK_GraphicsPipeline(VK_Renderer& vk_renderer);
	VK_GraphicsPipeline(const VK_GraphicsPipeline& vk_graphicsPipeline);
	~VK_GraphicsPipeline();

	void CreateGraphicsPipeline();

	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	void CleanupSwapChain(VK_BufferManager* vk_bufferManager);


	void RecreateSwapChain(GLFWwindow* window, VK_BufferManager* vk_bufferManager);
};

