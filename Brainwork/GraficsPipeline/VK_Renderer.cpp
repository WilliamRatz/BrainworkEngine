#include "VK_Renderer.h"
#include "VK_Device.h"
#include "VK_GameObjectManager.h"
#include "VK_SwapChain.h"
#include "LightManager.h"
#include "PointLight.h"
#include "VK_GraphicsPipeline.h"

VK_Renderer::VK_Renderer(VK_SwapChain& p_swapChain, RendererCreatInfo p_rendererCreatInfo)
{
	m_rendererCreatInfo = p_rendererCreatInfo;

	m_pSwapChain = &p_swapChain;
	m_pDevice = p_swapChain.m_pDevice;
}

VK_Renderer::VK_Renderer(const VK_Renderer& p_renderer)
{
	m_pDevice = p_renderer.m_pDevice;
	m_pSwapChain = p_renderer.m_pSwapChain;

	m_renderPass = p_renderer.m_renderPass;
	m_descriptorPool = p_renderer.m_descriptorPool;
	m_descriptorSetLayout = p_renderer.m_descriptorSetLayout;
	m_commandPool = p_renderer.m_commandPool;
	m_commandBuffers = p_renderer.m_commandBuffers;
	m_rendererCreatInfo = p_renderer.m_rendererCreatInfo;
}

VK_Renderer::~VK_Renderer()
{
}

void VK_Renderer::CreateRenderPass() {
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = m_pSwapChain->m_swapChainImageFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


	VkAttachmentDescription depthAttachment = {};
	depthAttachment.format = m_pSwapChain->findDepthFormat();
	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkAttachmentReference depthAttachmentRef = {};
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	std::array<VkSubpassDependency, 2> dependenciesDepth;

	dependenciesDepth[0].srcSubpass = VK_SUBPASS_EXTERNAL;
	dependenciesDepth[0].dstSubpass = 0;
	dependenciesDepth[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	dependenciesDepth[0].dstStageMask = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
	dependenciesDepth[0].srcAccessMask = 0;
	dependenciesDepth[0].dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	dependenciesDepth[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	dependenciesDepth[1].srcSubpass = 0;
	dependenciesDepth[1].dstSubpass = VK_SUBPASS_EXTERNAL;
	dependenciesDepth[1].srcStageMask = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
	dependenciesDepth[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	dependenciesDepth[1].srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	dependenciesDepth[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
	dependenciesDepth[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;


	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	std::vector<VkAttachmentDescription> attachments;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	if (m_rendererCreatInfo.colorAttachment && m_rendererCreatInfo.depthAttachment)
	{
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		depthAttachmentRef.attachment = 1;

		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

		attachments.push_back(colorAttachment);
		attachments.push_back(depthAttachment);

		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

	}
	else if (m_rendererCreatInfo.depthAttachment)
	{
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		depthAttachmentRef.attachment = 0;

		subpass.colorAttachmentCount = 0;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &depthAttachment;

		renderPassInfo.dependencyCount = 2;
		renderPassInfo.pDependencies = dependenciesDepth.data();

	}

	if (vkCreateRenderPass(m_pSwapChain->m_pDevice->device, &renderPassInfo, nullptr, &m_renderPass) != VK_SUCCESS) {
		throw std::runtime_error("failed to create render pass!");
	}
}



void VK_Renderer::CreateFramebuffers(std::vector<VkFramebuffer>& p_frameBuffers, std::vector<VkImageView>& p_colorImageView, VkImageView& p_depthImageView)
{
	p_frameBuffers.resize(m_pSwapChain->m_swapChainImageViews.size());

	for (size_t i = 0; i < m_pSwapChain->m_swapChainImageViews.size(); ++i) {
		std::array<VkImageView, 2> attachments = {
		p_colorImageView[i],
		p_depthImageView
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = m_renderPass;
		framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = m_pSwapChain->m_swapChainExtent.width;
		framebufferInfo.height = m_pSwapChain->m_swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(m_pDevice->device, &framebufferInfo, nullptr, &p_frameBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}
void VK_Renderer::CreateFramebuffers(std::vector<VkFramebuffer>& p_frameBuffers, VkImageView& p_depthImageView)
{
	p_frameBuffers.resize(m_pSwapChain->m_swapChainImageViews.size());

	for (size_t i = 0; i < m_pSwapChain->m_swapChainImageViews.size(); ++i) {
		VkImageView attachment = p_depthImageView;

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = m_renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = &attachment;
		framebufferInfo.width = m_pSwapChain->m_swapChainExtent.width;
		framebufferInfo.height = m_pSwapChain->m_swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(m_pDevice->device, &framebufferInfo, nullptr, &p_frameBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}


void VK_Renderer::CreateDescriptorSetLayouts(LayoutBinding& p_uboBindings, LayoutBinding& p_imageSamplerBindings) {
	unsigned int u = 0;
	std::vector<VkDescriptorSetLayoutBinding> bindings;

	for (int i = 0; i < p_uboBindings.m_bindings; ++i) {
		VkDescriptorSetLayoutBinding uboLayoutBinding = {};
		uboLayoutBinding.binding = u;
		uboLayoutBinding.descriptorCount = p_uboBindings.m_descriptorCount[i];
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

		bindings.push_back(uboLayoutBinding);
		++u;
	}

	for (int i = 0; i < p_imageSamplerBindings.m_bindings; ++i) {
		VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
		samplerLayoutBinding.binding = u;
		samplerLayoutBinding.descriptorCount = p_imageSamplerBindings.m_descriptorCount[i];
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		bindings.push_back(samplerLayoutBinding);
		++u;
	}

	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	if (vkCreateDescriptorSetLayout(m_pDevice->device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

void VK_Renderer::CreateDescriptorPools(unsigned int p_uboBindings, unsigned int p_imageSamplerBindings) {
	std::vector<VkDescriptorPoolSize> poolSizes;

	for (int i = 0; i < p_uboBindings; ++i) {

		VkDescriptorPoolSize uboSize = {};
		uboSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboSize.descriptorCount = static_cast<uint32_t>(m_pSwapChain->m_swapChainImages.size());
		poolSizes.push_back(uboSize);
	}

	for (int i = 0; i < p_imageSamplerBindings; ++i) {

		VkDescriptorPoolSize imageSamplerSize = {};
		imageSamplerSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		imageSamplerSize.descriptorCount = static_cast<uint32_t>(m_pSwapChain->m_swapChainImages.size());
		poolSizes.push_back(imageSamplerSize);
	}

	VkDescriptorPoolCreateInfo poolTextureInfo = {};
	poolTextureInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolTextureInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolTextureInfo.pPoolSizes = poolSizes.data();
	poolTextureInfo.maxSets = static_cast<uint32_t>(m_pSwapChain->m_swapChainImages.size()) * 60;

	if (vkCreateDescriptorPool(m_pDevice->device, &poolTextureInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}
void VK_Renderer::CreateCommandPool() {
	QueueFamilyIndices queueFamilyIndices = m_pDevice->findQueueFamilies(m_pDevice->physicalDevice);

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

	if (vkCreateCommandPool(m_pDevice->device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics command pool!");
	}
}
void VK_Renderer::CreateCommandBuffers(VK_GraphicsPipeline& vk_graphicsPipeline, VK_GameObjectManager& VK_gameObjectManager) {

	m_commandBuffers.resize(m_pSwapChain->m_swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

	if (vkAllocateCommandBuffers(m_pDevice->device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t cb = 0; cb < m_commandBuffers.size(); ++cb) {

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		if (vkBeginCommandBuffer(m_commandBuffers[cb], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_renderPass;
		renderPassInfo.framebuffer = m_pSwapChain->m_swapChainFramebuffers[cb];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = m_pSwapChain->m_swapChainExtent;

		std::array<VkClearValue, 2> clearValues = {};
		clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(m_commandBuffers[cb], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(m_commandBuffers[cb], VK_PIPELINE_BIND_POINT_GRAPHICS, vk_graphicsPipeline.m_graphicsPipeline);


		for (size_t gm = 0; gm < VK_gameObjectManager.GetGameObjectsRef().size(); ++gm)
		{
			VkBuffer vertexBuffers[] = { VK_gameObjectManager.GetGameObjectsRef()[gm].GetObjectRef().GetVK_BufferObjectRef().GetVertexBufferRef() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(m_commandBuffers[cb], 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(m_commandBuffers[cb], VK_gameObjectManager.GetGameObjectsRef()[gm].GetObjectRef().GetVK_BufferObjectRef().GetIndexBufferRef(), 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(m_commandBuffers[cb], VK_PIPELINE_BIND_POINT_GRAPHICS, vk_graphicsPipeline.m_pipelineLayout, 0, 1, &VK_gameObjectManager.GetGameObjectsRef()[gm].GetObjectRef().GetVK_BufferObjectRef().GetDescriptorSetsRef()[cb], 0, nullptr);

			vkCmdDrawIndexed(m_commandBuffers[cb], static_cast<uint32_t>(VK_gameObjectManager.GetGameObjectsRef()[gm].GetObject().GetIndices().size()), 1, 0, 0, 0);
		}

		vkCmdEndRenderPass(m_commandBuffers[cb]);

		if (vkEndCommandBuffer(m_commandBuffers[cb]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}




}

void VK_Renderer::CreateCommandBuffers(VK_GraphicsPipeline& p_vk_graphicsPipeline, LightManager& p_vk_lightManager)
{
	m_commandBuffers.resize(m_pSwapChain->m_swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

	if (vkAllocateCommandBuffers(m_pDevice->device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t cb = 0; cb < m_commandBuffers.size(); ++cb) { // cb = commandBuffers
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		if (vkBeginCommandBuffer(m_commandBuffers[cb], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		for (size_t pl = 0; pl < p_vk_lightManager.m_pointLights.size(); ++pl) { //pl = PointLight
			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = m_renderPass;
			renderPassInfo.framebuffer = p_vk_lightManager.m_pointLights[pl].GetFrameBufferRef()[cb];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = m_pSwapChain->m_swapChainExtent;

			VkClearValue clearValue;
			clearValue.depthStencil = { 1.0f, 0 };

			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearValue;

			vkCmdBeginRenderPass(m_commandBuffers[cb], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(m_commandBuffers[cb], VK_PIPELINE_BIND_POINT_GRAPHICS, p_vk_graphicsPipeline.m_graphicsPipeline);


			for (size_t gm = 0; gm < p_vk_lightManager.m_pointLights[pl].GetGameObjectsInFrustumPtr()->size(); ++gm) //gm = GameObjects
			{

				VkBuffer vertexBuffers[] = { p_vk_lightManager.m_pointLights[pl].GetGameObjectsInFrustumPtr()->at(gm).GetObjectRef().GetVK_BufferObjectRef().GetVertexBufferRef() };
				VkDeviceSize offsets[] = { 0 };
				vkCmdBindVertexBuffers(m_commandBuffers[cb], 0, 1, vertexBuffers, offsets);
				vkCmdBindIndexBuffer(m_commandBuffers[cb], p_vk_lightManager.m_pointLights[pl].GetGameObjectsInFrustumPtr()->at(gm).GetObjectRef().GetVK_BufferObjectRef().GetIndexBufferRef(), 0, VK_INDEX_TYPE_UINT32);
				vkCmdBindDescriptorSets(m_commandBuffers[cb], VK_PIPELINE_BIND_POINT_GRAPHICS, p_vk_graphicsPipeline.m_pipelineLayout, 0, 1, &p_vk_lightManager.m_pointLights[pl].GetVkDescriptorSetRef()[gm][cb], 0, nullptr);

				vkCmdDrawIndexed(m_commandBuffers[cb], static_cast<uint32_t>(p_vk_lightManager.m_pointLights[pl].GetGameObjectsInFrustumPtr()->at(gm).GetObject().GetIndices().size()), 1, 0, 0, 0);
			}

			vkCmdEndRenderPass(m_commandBuffers[cb]);
		}


		if (vkEndCommandBuffer(m_commandBuffers[cb]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}
}


VkCommandBuffer VK_Renderer::beginSingleTimeCommands()
{
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(m_pDevice->device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		return commandBuffer;
	}
}

void VK_Renderer::endSingleTimeCommands(VkCommandBuffer commandBuffer)
{
	{
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(m_pDevice->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_pDevice->graphicsQueue);

		vkFreeCommandBuffers(m_pDevice->device, m_commandPool, 1, &commandBuffer);
	}
}

VkRenderPass & VK_Renderer::GetRenderPassRef()
{
	return m_renderPass;
}

VkDescriptorPool & VK_Renderer::GetDescriptorPoolRef()
{
	return m_descriptorPool;
}

VkDescriptorSetLayout & VK_Renderer::GetDescriptorSetLayoutRef()
{
	return m_descriptorSetLayout;
}

std::vector<VkCommandBuffer>& VK_Renderer::GetCommandBuffersRef()
{
	return m_commandBuffers;
}

RendererCreatInfo & VK_Renderer::GetRendererCreatInfoRef()
{
	return m_rendererCreatInfo;
}

void VK_Renderer::CleanUp()
{
	vkDestroyDescriptorPool(m_pDevice->device, m_descriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(m_pDevice->device, m_descriptorSetLayout, nullptr);
	vkFreeCommandBuffers(m_pDevice->device, m_commandPool, static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
	vkDestroyCommandPool(m_pDevice->device, m_commandPool, nullptr);


	vkDestroyRenderPass(m_pDevice->device, m_renderPass, nullptr);
}
