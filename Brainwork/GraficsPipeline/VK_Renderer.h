#ifndef VK_RENDERER_H
#define VK_RENDERER_H

#include "VK_inc.h"

class VK_Device;
class VK_SwapChain;
class LightManager;

class VK_Renderer
{
public:
	VK_Device*				vk_device;
	VK_SwapChain*			vk_swapChain;

public:
	VK_Renderer				(VK_SwapChain& vk_swapChain);
	
	VkRenderPass			renderPass;
	VkRenderPass			renderPassLight;

	VkDescriptorPool		descriptorPool;
	VkDescriptorSetLayout	descriptorSetLayout;
	VkCommandPool			commandPool;

	
	void CreateRenderPass				();
	void CreateRenderPassLight			();
	void CreateFramebuffers				();
	void CreateLightFramebuffers		(LightManager* lightmanager);

	void CreateDescriptorSetLayouts		();
	void CreateDescriptorPools			();
	void CreateCommandPool				();

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
};

#endif // !VK_RENDERER_H