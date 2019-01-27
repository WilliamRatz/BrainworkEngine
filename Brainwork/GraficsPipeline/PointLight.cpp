#include "PointLight.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "LightManager.h"
#include "VK_BufferObject.h"
#include "VK_Device.h"
#include "GameObject.h"



PointLight::PointLight(VK_Renderer& p_renderer)
{
	m_pRenderer = &p_renderer;
}

PointLight::PointLight(const PointLight& p_pointLight)
{
	m_pRenderer = p_pointLight.m_pRenderer;

	m_lightInfoBuffer = p_pointLight.m_lightInfoBuffer;
	m_lightInfoBufferMemory = p_pointLight.m_lightInfoBufferMemory;

	m_lightInfo = p_pointLight.m_lightInfo;

	m_pointLightSampler = p_pointLight.m_pointLightSampler;
	m_pointLightImageView = p_pointLight.m_pointLightImageView;
	m_pointLightImage = p_pointLight.m_pointLightImage;
	m_pointLightImageMemory = p_pointLight.m_pointLightImageMemory;
}

PointLight::~PointLight()
{
}

void PointLight::CreatePointLightImage()
{
	VkFormat depthFormat = m_pRenderer->vk_swapChain->findDepthFormat();

	m_pRenderer->vk_swapChain->CreateImage(m_pRenderer->vk_swapChain->swapChainExtent.width, m_pRenderer->vk_swapChain->swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_pointLightImage, m_pointLightImageMemory);
	m_pointLightImageView = m_pRenderer->vk_swapChain->CreateImageView(m_pointLightImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

	m_pRenderer->vk_swapChain->TransitionImageLayout(*m_pRenderer, m_pointLightImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void PointLight::CreateLightSampler()
{
	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 16;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(m_pRenderer->vk_device->device, &samplerInfo, nullptr, &m_pointLightSampler) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}
}

void PointLight::CreateLightInfoBuffer(size_t p_gameObjectCount)
{
	m_lightInfoBuffer.resize(p_gameObjectCount);
	m_lightInfoBufferMemory.resize(p_gameObjectCount);

	for (size_t i = 0; i < p_gameObjectCount; ++i) {

		VkDeviceSize bufferSize = sizeof(LightInfoObject);
		m_lightInfoBuffer[i].resize(m_pRenderer->vk_swapChain->swapChainImages.size());
		m_lightInfoBufferMemory[i].resize(m_pRenderer->vk_swapChain->swapChainImages.size());

		for (size_t ii = 0; ii < m_pRenderer->vk_swapChain->swapChainImages.size(); ++ii) {
			VK_BufferObject::CreateBuffer(m_pRenderer, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_lightInfoBuffer[i][ii], m_lightInfoBufferMemory[i][ii]);
		}
	}
}

void PointLight::UpdateLightInfo(uint32_t& p_currentImage, GameObject& p_GameObject)
{

	void* data;
	
		m_lightInfo.model = p_GameObject.GetObjectRef().GetUniformBufferObjectRef().model;
		m_lightInfo.proj = p_GameObject.GetObjectRef().GetUniformBufferObjectRef().proj;

		p_GameObject.GetLightingRef().AddPointLight(this);

		vkMapMemory(m_pRenderer->vk_device->device, m_lightInfoBufferMemory[0][p_currentImage], 0, sizeof(LightInfoObject), 0, &data);
		memcpy(data, &m_lightInfo, sizeof(LightInfoObject));
		vkUnmapMemory(m_pRenderer->vk_device->device, m_lightInfoBufferMemory[0][p_currentImage]);
	
}

void PointLight::CreateDescriptorSets(LightManager* p_LightManager)
{
	std::vector<VkDescriptorSetLayout> layouts(p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size(), p_LightManager->m_descriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = p_LightManager->m_descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size());
	allocInfo.pSetLayouts = layouts.data();

		m_descriptorSets.resize(m_lightInfoBuffer.size());

	for (size_t i = 0; i < m_lightInfoBuffer.size(); ++i) {
		m_descriptorSets[i].resize(p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size());
		if (vkAllocateDescriptorSets(p_LightManager->m_pRenderer->vk_device->device, &allocInfo, m_descriptorSets[i].data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		for (size_t ii = 0; ii < p_LightManager->m_pRenderer->vk_swapChain->swapChainImages.size(); ++ii) {
			VkDescriptorBufferInfo bufferInfo = {};
			bufferInfo.buffer = m_lightInfoBuffer[i][ii];
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(LightInfoObject);

			VkWriteDescriptorSet descriptorWrite = {};

			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = m_descriptorSets[i][ii];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;
			vkUpdateDescriptorSets(p_LightManager->m_pRenderer->vk_device->device, 1, &descriptorWrite, 0, nullptr);
		}
	}
}

VkImageView PointLight::GetImageView()
{
	return m_pointLightImageView;
}
VkImageView& PointLight::GetImageViewRef()
{
	return m_pointLightImageView;
}

VkSampler PointLight::GetVkSampler()
{
	return m_pointLightSampler;
}
VkSampler& PointLight::GetVkSamplerRef()
{
	return m_pointLightSampler;
}

void CleanUpPointLight()
{

}
