#pragma once
#include "VK_inc.h"

class VK_Renderer;
class LightManager;
struct LightInfo {
	Matrix<float, 4, 4> model;
	Matrix<float, 4, 4> view;
};

class PointLight
{
	LightInfo						m_LightInfo;

	std::vector<VkBuffer>			m_LightInfoBuffer;
	std::vector<VkDeviceMemory>		m_LightInfoBufferMemory;

	std::vector<VkDescriptorSet>	m_descriptorSets;
	
	VkImage							m_PointLightImage;
	VkDeviceMemory					m_PointLightImageMemory;
	VkImageView						m_PointLightImageView;

public:
	PointLight();
	PointLight(const PointLight& pointLight);
	~PointLight();

	void CreatePointLightImage(VK_Renderer*);
	void CreateLightInfoBuffer(VK_Renderer*);
	void UpdateLightInfoToShader(VK_Renderer*, uint32_t&);
	void CreateDescriptorSets(LightManager*, VkDescriptorPool&, VkDescriptorSetLayout&);

	VkImageView GetImageView();
};