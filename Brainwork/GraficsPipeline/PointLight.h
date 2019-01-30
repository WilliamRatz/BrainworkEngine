#pragma once
#include "VK_inc.h"

class VK_Renderer;
class LightManager;
class GameObject;

class PointLight
{
	VK_Renderer*			m_pRenderer;

	std::vector<std::vector<VkBuffer>>				m_lightInfoBuffer;
	std::vector<std::vector<VkDeviceMemory>>		m_lightInfoBufferMemory;
	std::vector<std::vector<VkDescriptorSet>>		m_descriptorSets;


	LightInfoObject			m_lightInfo;
	
	VkSampler				m_pointLightSampler;
	VkImageView				m_pointLightImageView;
	VkImage					m_pointLightImage;
	VkDeviceMemory			m_pointLightImageMemory;

public:
	std::vector<GameObject*> 						m_gameObjectsInFrustum;
	std::vector<VkFramebuffer>						m_lightFramebuffers;
	PointLight(VK_Renderer&);
	PointLight(const PointLight& pointLight);
	~PointLight();

	void UpdateLightInfo(uint32_t&, GameObject&);
	void CheckForObjectsInFurustum(std::vector<GameObject>& gameObject);

	void CreatePointLightImage();
	void CreateLightSampler();

	void CreateLightInfoBuffer(size_t);
	void CreateDescriptorSets(LightManager*);

	LightInfoObject		GetLightInfoObject();
	LightInfoObject&	GetLightInfoObjectRef();

	VkImageView		GetImageView();
	VkImageView&	GetImageViewRef();

	VkSampler		GetVkSampler();
	VkSampler&		GetVkSamplerRef();

	std::vector<std::vector<VkDescriptorSet>>		GetVkDescriptorSet();
	std::vector<std::vector<VkDescriptorSet>>&		GetVkDescriptorSetRef();

	void CleanUpPointLight();
};