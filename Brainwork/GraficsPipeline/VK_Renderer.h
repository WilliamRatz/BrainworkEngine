#ifndef VK_RENDERER_H
#define VK_RENDERER_H

#include "VK_inc.h"

class VK_Device;
class VK_SwapChain;

class VK_Renderer
{
public:
	VK_Device*				vk_device;
	VK_SwapChain*			vk_swapChain;

public:
	VK_Renderer				(VK_Device& p_vk_device, VK_SwapChain& p_vk_SwapChain);
	VkPipeline				graphicsPipeline;
	VkPipelineLayout		pipelineLayout;

	VkRenderPass			renderPass;

	VkDescriptorPool		descriptorPool;
	VkDescriptorSetLayout	descriptorSetLayout;
	VkCommandPool			commandPool;

	
	void CreateRenderPass				();
	void CreateGraphicsPipeline			();

	void CreateDescriptorSetLayout		();

	void CreateDescriptorPool			();
	void CreateCommandPool				();

	static std::vector<char> readFile	(const std::string& filename);
	VkShaderModule createShaderModule	(const std::vector<char>& code);

};

#endif // !VK_RENDERER_H