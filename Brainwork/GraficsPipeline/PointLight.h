#pragma once
#include "VK_inc.h"

class VK_Renderer;
class LightManager;
class GameObject;

class PointLight
{
	VK_Renderer*			m_pRenderer;
	LightInfoObject			m_lightInfo;
	
	VkSampler				m_pointLightSampler;
	VkImageView				m_pointLightImageView;
	VkImage					m_pointLightImage;
	VkDeviceMemory			m_pointLightImageMemory;

	std::vector<GameObject>* 						m_pGameObjectsInFrustum;
	std::vector<VkFramebuffer>						m_lightFramebuffers;
	std::vector<std::vector<VkBuffer>>				m_lightInfoBuffer;
	std::vector<std::vector<VkDeviceMemory>>		m_lightInfoBufferMemory;
	std::vector<std::vector<VkDescriptorSet>>		m_descriptorSets;


public:
	PointLight	(VK_Renderer&);
	PointLight	(const PointLight& pointLight);
	~PointLight	();

	void UpdateLightInfo			(uint32_t&);
	void CheckForObjectsInFurustum	(std::vector<GameObject>& gameObject);

	void CreatePointLightImage		();
	void CreateLightSampler			();

	void CreateLightInfoBuffer		();
	void CreateDescriptorSets		(LightManager*);

	VkImageView&		GetImageViewRef			();
	VkSampler&			GetVkSamplerRef			();
	LightInfoObject&	GetLightInfoObjectRef	();

	std::vector<std::vector<VkDescriptorSet>>&	GetVkDescriptorSetRef();
	std::vector<GameObject>*					GetGameObjectsInFrustumPtr();
	std::vector<VkFramebuffer>&					GetFrameBufferRef();

	void CleanUp();
};