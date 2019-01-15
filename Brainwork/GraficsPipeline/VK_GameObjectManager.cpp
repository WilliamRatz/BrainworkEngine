#include "VK_GameObjectManager.h"
#include "VK_Renderer.h"
#include "VK_Device.h"
#include "VK_SwapChain.h"
#include "VK_GraphicsPipeline.h"
#include "GameObject.h"
#include "Texture.h"
#include "Objects.h"

VK_GameObjectManager::VK_GameObjectManager(VK_Renderer& p_renderer)
{
	renderer = &p_renderer;
}

void VK_GameObjectManager::UpdateUniformBuffers(uint32_t currentImage)
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i].updateGameObject(currentImage);
	}
}

void VK_GameObjectManager::CreateBufferObjects()
{
	Material mat;
	Object ob;
	ob.SetMesh("models/Cube.obj");
	const char* cha = "textures/texture.png";
	int u = 0;

	for (int i = 0; i < 5; ++i)
	{
		for (int ii = 0; ii < 5; ++ii)
		{
			gameObjects.push_back(GameObject(*renderer));
			gameObjects[u].SetObject(ob);
			gameObjects[u].SetMaterial(mat);

			Texture text(cha);

			gameObjects[u].GetMaterial().SetTexture(text);
			gameObjects[u].localMatrix.translate3D(1.2*i, 1.2*ii, 0);
			//gameObjects[u].localMatrix.scale3D(0.1, 0.1, 0.1);
			gameObjects[u].CreateBuffer();
			++u;
		}
	}
}

void VK_GameObjectManager::CreateDescriptorSets()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i].CreateDescriptorSets();
	}
}


void VK_GameObjectManager::CreateCommandBuffers(VK_GraphicsPipeline& vk_graphicsPipeline) {

	int a;
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

		std::array<VkClearValue, 2> clearValues = {};
		clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vk_graphicsPipeline.graphicsPipeline);

		for (size_t ii = 0; ii < gameObjects.size(); ++ii)
		{

			VkBuffer vertexBuffers[] = { gameObjects[ii].GetBufferObject().GetVertexBuffer() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffers[i], gameObjects[ii].GetBufferObject().GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vk_graphicsPipeline.pipelineLayout, 0, 1, &gameObjects[ii].GetBufferObject().GetDescriptorSets()[i], 0, nullptr);

			vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(gameObjects[ii].GetObject().GetIndices().size()), 1, 0, 0, 0);
		}

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}

}

void VK_GameObjectManager::CleanUpBuffers()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i].CleanupGameObject();
	}
	vkFreeCommandBuffers(renderer->vk_device->device, renderer->commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
}

