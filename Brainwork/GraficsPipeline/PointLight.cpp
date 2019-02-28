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
	VkFormat depthFormat = m_pRenderer->m_pSwapChain->findDepthFormat();

	m_pRenderer->m_pSwapChain->CreateImage(m_pRenderer->m_pSwapChain->m_swapChainExtent.width, m_pRenderer->m_pSwapChain->m_swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_pointLightImage, m_pointLightImageMemory);
	m_pointLightImageView = m_pRenderer->m_pSwapChain->CreateImageView(m_pointLightImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

	m_pRenderer->m_pSwapChain->TransitionImageLayout(*m_pRenderer, m_pointLightImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
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

	if (vkCreateSampler(m_pRenderer->m_pDevice->device, &samplerInfo, nullptr, &m_pointLightSampler) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}
}

void PointLight::CreateLightInfoBuffer()
{
	m_lightInfoBuffer.resize(m_pGameObjectsInFrustum->size());
	m_lightInfoBufferMemory.resize(m_pGameObjectsInFrustum->size());

	for (size_t i = 0; i < m_pGameObjectsInFrustum->size(); ++i) {

		VkDeviceSize bufferSize = sizeof(LightInfoObject);
		m_lightInfoBuffer[i].resize(m_pRenderer->m_pSwapChain->m_swapChainImages.size());
		m_lightInfoBufferMemory[i].resize(m_pRenderer->m_pSwapChain->m_swapChainImages.size());

		for (size_t ii = 0; ii < m_pRenderer->m_pSwapChain->m_swapChainImages.size(); ++ii) {
			VK_BufferObject::CreateBuffer(m_pRenderer, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_lightInfoBuffer[i][ii], m_lightInfoBufferMemory[i][ii]);
		}
	}
}

void PointLight::UpdateLightInfo(uint32_t& p_currentImage)
{
		m_lightInfo.lightView = m_lightInfo.lightView.transpose();
		m_lightInfo.lightView.translate3D(0.001, 0, 0);
		if (m_lightInfo.lightView[0][3] > 20) 
		{
			m_lightInfo.lightView[0][3] = -20;
		}
		m_lightInfo.lightView = m_lightInfo.lightView.transpose();

	for (size_t i = 0; i < m_pGameObjectsInFrustum->size(); ++i)
	{
		void* data;
		m_lightInfo.model = m_pGameObjectsInFrustum->at(i).GetObjectRef().GetUniformBufferObjectRef().model;
		m_lightInfo.proj = m_pGameObjectsInFrustum->at(i).GetObjectRef().GetUniformBufferObjectRef().proj;

		vkMapMemory(m_pRenderer->m_pDevice->device, m_lightInfoBufferMemory[i][p_currentImage], 0, sizeof(LightInfoObject), 0, &data);
		memcpy(data, &m_lightInfo, sizeof(LightInfoObject));
		vkUnmapMemory(m_pRenderer->m_pDevice->device, m_lightInfoBufferMemory[i][p_currentImage]);
	}
}

void PointLight::CheckForObjectsInFurustum(std::vector<GameObject>& p_gameObject)
{
	m_pGameObjectsInFrustum = &p_gameObject;

	for (unsigned int i = 0; i < p_gameObject.size(); ++i)
	{
		p_gameObject[i].GetLightingRef().GetPointLightRef().push_back(this);
	}

}

void PointLight::CreateDescriptorSets(LightManager* p_pLightManager)
{
	m_descriptorSets.resize(m_lightInfoBuffer.size());

	std::vector<VkDescriptorSetLayout> layouts(p_pLightManager->m_pRenderer->m_pSwapChain->m_swapChainImages.size(), p_pLightManager->m_pRenderer->GetDescriptorSetLayoutRef());
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = p_pLightManager->m_pRenderer->GetDescriptorPoolRef();
	allocInfo.descriptorSetCount = static_cast<uint32_t>(p_pLightManager->m_pRenderer->m_pSwapChain->m_swapChainImages.size());
	allocInfo.pSetLayouts = layouts.data();


	for (size_t i = 0; i < m_lightInfoBuffer.size(); ++i) {
		m_descriptorSets[i].resize(p_pLightManager->m_pRenderer->m_pSwapChain->m_swapChainImages.size());
		if (vkAllocateDescriptorSets(p_pLightManager->m_pRenderer->m_pDevice->device, &allocInfo, m_descriptorSets[i].data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		for (size_t ii = 0; ii < p_pLightManager->m_pRenderer->m_pSwapChain->m_swapChainImages.size(); ++ii) {
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
			vkUpdateDescriptorSets(p_pLightManager->m_pRenderer->m_pDevice->device, 1, &descriptorWrite, 0, nullptr);
		}
	}
}


LightInfoObject& PointLight::GetLightInfoObjectRef()
{
	return m_lightInfo;
}

VkImageView& PointLight::GetImageViewRef()
{
	return m_pointLightImageView;
}

VkSampler& PointLight::GetVkSamplerRef()
{
	return m_pointLightSampler;
}

std::vector<std::vector<VkDescriptorSet>>& PointLight::GetVkDescriptorSetRef()
{
	return m_descriptorSets;
}

std::vector<GameObject>* PointLight::GetGameObjectsInFrustumPtr()
{
	return m_pGameObjectsInFrustum;
}

std::vector<VkFramebuffer>& PointLight::GetFrameBufferRef()
{
	return m_lightFramebuffers;
}

void PointLight::CleanUp()
{
	vkDestroySampler(m_pRenderer->m_pDevice->device, m_pointLightSampler, nullptr);
	vkDestroyImageView(m_pRenderer->m_pDevice->device, m_pointLightImageView, nullptr);
	vkDestroyImage(m_pRenderer->m_pDevice->device, m_pointLightImage, nullptr);
	vkFreeMemory(m_pRenderer->m_pDevice->device, m_pointLightImageMemory, nullptr);

	for (auto framebuffer : m_lightFramebuffers) {
		vkDestroyFramebuffer(m_pRenderer->m_pDevice->device, framebuffer, nullptr);
	}

	for (size_t i = 0; i < m_lightInfoBuffer.size(); ++i) {
		for (size_t ii = 0; ii < m_lightInfoBuffer[i].size(); ++ii) {
			vkDestroyBuffer(m_pRenderer->m_pDevice->device, m_lightInfoBuffer[i][ii], nullptr);
			vkFreeMemory(m_pRenderer->m_pDevice->device, m_lightInfoBufferMemory[i][ii], nullptr);
		}
	}
}
