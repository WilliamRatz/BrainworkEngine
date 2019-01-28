#include "VK_Renderer.h"
#include "VK_Device.h"
#include "VK_GameObjectManager.h"
#include "VK_SwapChain.h"
#include "LightManager.h"
#include "PointLight.h"
#include "VK_GraphicsPipeline.h"

VK_Renderer::VK_Renderer(VK_SwapChain& p_vk_swapChain, RendererCreatInfo p_rendererCreatInfo)
{
	m_rendererCreatInfo = p_rendererCreatInfo;

	vk_swapChain = &p_vk_swapChain;
	vk_device = p_vk_swapChain.vk_device;
}

void VK_Renderer::CreateRenderPass() {
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = vk_swapChain->swapChainImageFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


	VkAttachmentDescription depthAttachment = {};
	depthAttachment.format = vk_swapChain->findDepthFormat();
	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentRef = {};
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	if (m_rendererCreatInfo.colorAttachment && m_rendererCreatInfo.depthAttachment)
	{
		depthAttachmentRef.attachment = 1;

		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

	}
	else if (m_rendererCreatInfo.depthAttachment)
	{
		depthAttachmentRef.attachment = 0;

		subpass.colorAttachmentCount = 0;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &depthAttachment;

	}

	if (vkCreateRenderPass(vk_swapChain->vk_device->device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
		throw std::runtime_error("failed to create render pass!");
	}
}



void VK_Renderer::CreateFramebuffers(std::vector<VkFramebuffer>& p_frameBuffers, std::vector<VkImageView>& p_colorImageView, VkImageView& p_depthImageView)
{
	p_frameBuffers.resize(vk_swapChain->swapChainImageViews.size());

	for (size_t i = 0; i < vk_swapChain->swapChainImageViews.size(); ++i) {
		std::array<VkImageView, 2> attachments = {
		p_colorImageView[i],
		p_depthImageView
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = vk_swapChain->swapChainExtent.width;
		framebufferInfo.height = vk_swapChain->swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(vk_device->device, &framebufferInfo, nullptr, &p_frameBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}
void VK_Renderer::CreateFramebuffers(std::vector<VkFramebuffer>& p_frameBuffers, VkImageView& p_depthImageView)
{
	p_frameBuffers.resize(vk_swapChain->swapChainImageViews.size());

	for (size_t i = 0; i < vk_swapChain->swapChainImageViews.size(); ++i) {
		VkImageView attachment = p_depthImageView;

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = &attachment;
		framebufferInfo.width = vk_swapChain->swapChainExtent.width;
		framebufferInfo.height = vk_swapChain->swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(vk_device->device, &framebufferInfo, nullptr, &p_frameBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}


void VK_Renderer::CreateDescriptorSetLayouts(unsigned int p_uboBindings, unsigned int p_imageSamplerBindings) {
	unsigned int u = 0;
	std::vector<VkDescriptorSetLayoutBinding> bindings;

	for (int i = 0; i < p_uboBindings; ++i) {
		VkDescriptorSetLayoutBinding uboLayoutBinding = {};
		uboLayoutBinding.binding = u;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		bindings.push_back(uboLayoutBinding);
		++u;
	}

	for (int i = 0; i < p_imageSamplerBindings; ++i) {
		VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
		samplerLayoutBinding.binding = u;
		samplerLayoutBinding.descriptorCount = 1;
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

	if (vkCreateDescriptorSetLayout(vk_device->device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

void VK_Renderer::CreateDescriptorPools(unsigned int p_uboBindings, unsigned int p_imageSamplerBindings) {
	std::vector<VkDescriptorPoolSize> poolSizes;

	for (int i = 0; i < p_uboBindings; ++i) {

		VkDescriptorPoolSize uboSize = {};
		uboSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboSize.descriptorCount = static_cast<uint32_t>(vk_swapChain->swapChainImages.size());
		poolSizes.push_back(uboSize);
	}

	for (int i = 0; i < p_imageSamplerBindings; ++i) {

		VkDescriptorPoolSize imageSamplerSize = {};
		imageSamplerSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		imageSamplerSize.descriptorCount = static_cast<uint32_t>(vk_swapChain->swapChainImages.size());
		poolSizes.push_back(imageSamplerSize);
	}

	VkDescriptorPoolCreateInfo poolTextureInfo = {};
	poolTextureInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolTextureInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolTextureInfo.pPoolSizes = poolSizes.data();
	poolTextureInfo.maxSets = static_cast<uint32_t>(vk_swapChain->swapChainImages.size());

	if (vkCreateDescriptorPool(vk_device->device, &poolTextureInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}
void VK_Renderer::CreateCommandPool() {
	QueueFamilyIndices queueFamilyIndices = vk_device->findQueueFamilies(vk_device->physicalDevice);

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

	if (vkCreateCommandPool(vk_device->device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics command pool!");
	}
}
void VK_Renderer::CreateCommandBuffers(VK_GraphicsPipeline& vk_graphicsPipeline, VK_GameObjectManager& VK_gameObjectManager) {

	commandBuffers.resize(vk_swapChain->swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(vk_device->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t i = 0; i < commandBuffers.size(); ++i) {

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = vk_swapChain->swapChainFramebuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = vk_swapChain->swapChainExtent;

		std::array<VkClearValue, 2> clearValues = {};
		clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vk_graphicsPipeline.graphicsPipeline);


		for (size_t ii = 0; ii < VK_gameObjectManager.GetGameObjectsRef().size(); ++ii)
		{

			VkBuffer vertexBuffers[] = { VK_gameObjectManager.GetGameObjectsRef()[ii].GetObjectRef().GetVK_BufferObjectRef().GetVertexBuffer() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffers[i], VK_gameObjectManager.GetGameObjectsRef()[ii].GetObjectRef().GetVK_BufferObjectRef().GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vk_graphicsPipeline.pipelineLayout, 0, 1, &VK_gameObjectManager.GetGameObjectsRef()[ii].GetObjectRef().GetVK_BufferObjectRef().GetDescriptorSets()[i], 0, nullptr);

			vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(VK_gameObjectManager.GetGameObjectsRef()[ii].GetObject().GetIndices().size()), 1, 0, 0, 0);
		}

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}



}

void VK_Renderer::CreateCommandBuffers(VK_GraphicsPipeline& p_vk_graphicsPipeline, LightManager& p_vk_lightManager)
{
	commandBuffers.resize(vk_swapChain->swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(vk_device->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t i = 0; i < commandBuffers.size(); ++i) {
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}



		for (size_t ii = 0; ii < p_vk_lightManager.m_pointLights.size(); ++ii) {
			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = renderPass;
			renderPassInfo.framebuffer = p_vk_lightManager.m_pointLights[ii].m_lightFramebuffers[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = vk_swapChain->swapChainExtent;

			VkClearValue clearValue;
			clearValue.depthStencil = { 1.0f, 0 };

			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearValue;

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, p_vk_graphicsPipeline.graphicsPipeline);

			for (size_t iii = 0; iii < 1; ++iii) {

				for (size_t iiii = 0; iiii < p_vk_lightManager.m_pointLights[iii].m_gameObjectsInFrustum.size(); ++iiii)
				{

					VkBuffer vertexBuffers[] = { p_vk_lightManager.m_pointLights[iii].m_gameObjectsInFrustum[iiii]->GetObjectRef().GetVK_BufferObjectRef().GetVertexBuffer() };
					VkDeviceSize offsets[] = { 0 };
					vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
					vkCmdBindIndexBuffer(commandBuffers[i], p_vk_lightManager.m_pointLights[iii].m_gameObjectsInFrustum[iiii]->GetObjectRef().GetVK_BufferObjectRef().GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);
					vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, p_vk_graphicsPipeline.pipelineLayout, 0, 1, &p_vk_lightManager.m_pointLights[iii].GetVkDescriptorSetRef()[iii][i], 0, nullptr);

					vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(p_vk_lightManager.m_pointLights[iii].m_gameObjectsInFrustum[iiii]->GetObject().GetIndices().size()), 1, 0, 0, 0);
				}

			}
		}

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
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
		allocInfo.commandPool = commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(vk_device->device, &allocInfo, &commandBuffer);

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

		vkQueueSubmit(vk_device->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(vk_device->graphicsQueue);

		vkFreeCommandBuffers(vk_device->device, commandPool, 1, &commandBuffer);
	}
}
