#include "VK_BufferManager.h"
#include "VK_Renderer.h"
#include "VK_Device.h"
#include "VK_SwapChain.h"


VK_BufferManager::VK_BufferManager(VK_Renderer& p_renderer)
{
	renderer = &p_renderer;
}

void VK_BufferManager::UpdateUniformBuffers(uint32_t currentImage)
{
	for (size_t i = 0; i < bufferObjects.size(); ++i)
	{
		bufferObjects[i].updateUniformBuffer(currentImage);
	}
}

void VK_BufferManager::CreateBufferObjects()
{
	int u = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int ii = 0; ii < 5; ++ii)
		{
			bufferObjects.push_back(VK_BufferObject(*renderer));
			bufferObjects[u].gameObject.localMatrix[0][3] = ii * 1.2f;
			bufferObjects[u].gameObject.localMatrix[1][3] = i * 1.2f;
			++u;
		}
	}
}

void VK_BufferManager::CreateDescriptorSets()
{
	for (size_t i = 0; i < bufferObjects.size(); ++i)
	{
		std::cout << i << std::endl;
		bufferObjects[i].createDescriptorSets(bufferObjects[i].texture);
	}
}


void VK_BufferManager::CreateCommandBuffers() {

	commandBuffers.resize(renderer->vk_swapChain->swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = renderer->commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(renderer->vk_device->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
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
		renderPassInfo.renderPass = renderer->renderPass;
		renderPassInfo.framebuffer = renderer->vk_swapChain->swapChainFramebuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = renderer->vk_swapChain->swapChainExtent;

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, renderer->graphicsPipeline);

		for (size_t ii = 0; ii < bufferObjects.size(); ++ii)
		{

			VkBuffer vertexBuffers[] = { bufferObjects[ii].vertexBuffer };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffers[i], bufferObjects[ii].indexBuffer, 0, VK_INDEX_TYPE_UINT16);
			vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, renderer->pipelineLayout, 0, 1, &bufferObjects[ii].descriptorSets[i], 0, nullptr);

			vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(bufferObjects[ii].gameObject.getIndices().size()), 1, 0, 0, 0);
		}

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}

}

void VK_BufferManager::CleanUpBuffers()
{
	for (size_t i = 0; i < bufferObjects.size(); ++i)
	{
		bufferObjects[i].cleanup();
	}
}

