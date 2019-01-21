#include "PointLight.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "LightManager.h"
#include "VK_BufferObject.h"
#include "VK_Device.h"



PointLight::PointLight()
{

}

PointLight::PointLight(const PointLight& pointLight)
{
}

PointLight::~PointLight()
{
}

void PointLight::CreatePointLightImage(VK_Renderer* p_renderer)
{
	VkFormat depthFormat = p_renderer->vk_swapChain->findDepthFormat();

	p_renderer->vk_swapChain->CreateImage(p_renderer->vk_swapChain->swapChainExtent.width, p_renderer->vk_swapChain->swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_PointLightImage, m_PointLightImageMemory);
	m_PointLightImageView = p_renderer->vk_swapChain->CreateImageView(m_PointLightImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

	p_renderer->vk_swapChain->TransitionImageLayout(*p_renderer, m_PointLightImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}
void PointLight::CreateLightInfoBuffer(VK_Renderer* p_renderer)
{
	VkDeviceSize bufferSize = sizeof(LightInfo);
	m_LightInfoBuffer.resize(p_renderer->vk_swapChain->swapChainImages.size());
	m_LightInfoBufferMemory.resize(p_renderer->vk_swapChain->swapChainImages.size());

	for (size_t i = 0; i < p_renderer->vk_swapChain->swapChainImages.size(); ++i) {
		VK_BufferObject::CreateBuffer(p_renderer, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_LightInfoBuffer[i], m_LightInfoBufferMemory[i]);
	}
}

void PointLight::UpdateLightInfoToShader(VK_Renderer* p_renderer, uint32_t& p_currentImage)
{
	void* data;

	vkMapMemory(p_renderer->vk_device->device, m_LightInfoBufferMemory[p_currentImage], 0, sizeof(LightInfo), 0, &data);
	memcpy(data, &m_LightInfo, sizeof(LightInfo));
	vkUnmapMemory(p_renderer->vk_device->device, m_LightInfoBufferMemory[p_currentImage]);
}

void PointLight::CreateDescriptorSets(LightManager* p_LightManager, VkDescriptorPool&  vkDescriptorPool, VkDescriptorSetLayout& vkDescriptorSetLayout)
{
	std::vector<VkDescriptorSetLayout> layouts(p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size(), p_LightManager->m_descriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = p_LightManager->m_descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size());
	allocInfo.pSetLayouts = layouts.data();

	m_descriptorSets.resize(p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size());
	if (vkAllocateDescriptorSets(p_LightManager->m_pRenderer->vk_device->device, &allocInfo, m_descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size(); ++i) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = m_LightInfoBuffer[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(LightInfo);

		VkWriteDescriptorSet descriptorWrite;

		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = m_descriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;

		vkUpdateDescriptorSets(p_LightManager->m_pRenderer->vk_device->device, 1, &descriptorWrite, 0, nullptr);
	}

}

VkImageView PointLight::GetImageView() 
{
	return m_PointLightImageView;
}
