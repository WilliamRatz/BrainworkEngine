#include "LightManager.h"
#include "PointLight.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "VK_Device.h"
#include "GameObject.h"



LightManager::LightManager(VK_Renderer& p_pRenderer)
{
	m_pRenderer = &p_pRenderer;
}

LightManager::~LightManager()
{
}

void LightManager::AddLight(PointLight p_pointLight) 
{
	m_pointLights.push_back(p_pointLight);
}


void LightManager::CalculateLightMaps()
{
	for (PointLight& p_light : m_pointLights) 
	{
		p_light.CreatePointLightImage();
		p_light.CreateLightSampler();
	}
}

void LightManager::CheckForObjectsInFurustum(std::vector<GameObject>& p_gameObjects)
{
	for (PointLight& p_light : m_pointLights)
	{
		p_light.CheckForObjectsInFurustum(p_gameObjects);
	}
}

//void LightManager::CreateDescriptorPool()
//{
//	VkDescriptorPoolSize poolSize;
//	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//	poolSize.descriptorCount = static_cast<uint32_t>(m_pRenderer->vk_swapChain->swapChainImages.size());
//
//	VkDescriptorPoolCreateInfo poolTextureInfo = {};
//	poolTextureInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
//	poolTextureInfo.poolSizeCount = 1;
//	poolTextureInfo.pPoolSizes = &poolSize;
//	poolTextureInfo.maxSets = static_cast<uint32_t>(m_pRenderer->vk_swapChain->swapChainImages.size() * 60);
//
//	if (vkCreateDescriptorPool(m_pRenderer->vk_device->device, &poolTextureInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
//		throw std::runtime_error("failed to create descriptor pool!");
//	}
//}
//void LightManager::CreateDescriptorSetLayout()
//{
//	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
//	uboLayoutBinding.binding = 0;
//	uboLayoutBinding.descriptorCount = 1;
//	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//	uboLayoutBinding.pImmutableSamplers = nullptr;
//	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
//
//	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
//	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
//	layoutInfo.bindingCount = 1;
//	layoutInfo.pBindings = &uboLayoutBinding;
//
//	if (vkCreateDescriptorSetLayout(m_pRenderer->vk_device->device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS) {
//		throw std::runtime_error("failed to create descriptor set layout!");
//	}
//}

void LightManager::CreateDescriptorSets() 
{
	for (PointLight& p_light : m_pointLights)
	{
		p_light.CreateDescriptorSets(this);
	}
}

void LightManager::CreateFrameBuffer()
{
	for (PointLight& p_light : m_pointLights)
	{
		m_pRenderer->CreateFramebuffers(p_light.m_lightFramebuffers, p_light.GetImageViewRef());
	}
}

void LightManager::CreateLightBuffer(size_t p_gameObjectCount)
{
	for (PointLight& p_light : m_pointLights)
	{
		p_light.CreateLightInfoBuffer(p_gameObjectCount);
	}
}

void LightManager::UpdateLightInfos(uint32_t p_currentImage, GameObject* p_gameObject)
{
	for (PointLight& p_light : m_pointLights)
	{
		p_light.UpdateLightInfo(p_currentImage, *p_gameObject);
	}
}