#pragma once
#include "VK_inc.h"

class VK_Renderer;
class LightManager;
class GameObject;

class PointLight
{
	LightInfoObject					m_LightInfo;

	std::vector <std::vector<VkBuffer>>				m_LightInfoBuffer;
	std::vector <std::vector<VkDeviceMemory>>		m_LightInfoBufferMemory;

	
	VkImage							m_PointLightImage;
	VkDeviceMemory					m_PointLightImageMemory;
	VkImageView						m_PointLightImageView;

public:
	std::vector<std::vector<VkDescriptorSet>>	m_descriptorSets;
	PointLight();
	PointLight(const PointLight& pointLight);
	~PointLight();

	void CreatePointLightImage(VK_Renderer*);
	void CreateLightInfoBuffer(VK_Renderer*, size_t);
	void UpdateLightInfo(VK_Renderer*, uint32_t&, GameObject&);
	void CreateDescriptorSets(LightManager*);

	VkImageView GetImageView();
};