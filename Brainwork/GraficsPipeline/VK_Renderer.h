#ifndef VK_RENDERER_H
#define VK_RENDERER_H
#include "VK_inc.h"


class VK_Device;
class VK_SwapChain;
class LightManager;
class VK_GameObjectManager;
class VK_GraphicsPipeline;

struct RendererCreatInfo
{
	bool colorAttachment;
	bool depthAttachment;

	RendererCreatInfo(bool p_colorAttachment, bool p_depthAttachment)
	{
		colorAttachment = p_colorAttachment;
		depthAttachment = p_depthAttachment;
	}
	RendererCreatInfo()
	{
		colorAttachment = false;
		depthAttachment = false;
	}
};

class VK_Renderer
{
private:
	VkRenderPass					m_renderPass;
	VkDescriptorPool				m_descriptorPool;
	VkDescriptorSetLayout			m_descriptorSetLayout;
	VkCommandPool					m_commandPool;
	std::vector<VkCommandBuffer>	m_commandBuffers;
	RendererCreatInfo				m_rendererCreatInfo;

public:
	VK_Device*				m_pDevice;
	VK_SwapChain*			m_pSwapChain;

	VK_Renderer				(VK_SwapChain& swapChain, RendererCreatInfo rendererCreatInfo);
	VK_Renderer				(const VK_Renderer& renderer);
	~VK_Renderer			();
	
	void CreateRenderPass				();

	void CreateFramebuffers				(std::vector<VkFramebuffer>& p_frameBuffers, std::vector<VkImageView>& p_colorImageView, VkImageView& p_depthImageView);
	void CreateFramebuffers				(std::vector<VkFramebuffer>& p_frameBuffers, VkImageView& p_depthImageView);

	void CreateDescriptorSetLayouts		(unsigned int p_uboBindings, unsigned int p_imageSamplerBindings);
	void CreateDescriptorPools			(unsigned int p_uboBindings, unsigned int p_imageSamplerBindings);

	void CreateCommandPool				();
	void CreateCommandBuffers			(VK_GraphicsPipeline& vk_graphicsPipeline, VK_GameObjectManager& VK_gameObjectManager);
	void CreateCommandBuffers			(VK_GraphicsPipeline& vk_graphicsPipeline, LightManager& VK_lightManager);

	VkCommandBuffer beginSingleTimeCommands		();
	void			endSingleTimeCommands		(VkCommandBuffer commandBuffer);

	VkRenderPass&					GetRenderPassRef();
	VkDescriptorPool&				GetDescriptorPoolRef();
	VkDescriptorSetLayout&			GetDescriptorSetLayoutRef();
	std::vector<VkCommandBuffer>&	GetCommandBuffersRef();
	RendererCreatInfo&				GetRendererCreatInfoRef();

	void CleanUp();
};


#endif // !VK_RENDERER_H