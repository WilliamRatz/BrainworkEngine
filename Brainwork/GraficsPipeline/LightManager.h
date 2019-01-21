#pragma once
#include "VK_inc.h"
class PointLight;



class VK_Renderer;

class LightManager
{
public:
	VK_Renderer*			m_pRenderer;


	std::vector<PointLight> m_pointLights;
	VkDescriptorPool		m_descriptorPool;
	VkDescriptorSetLayout	m_descriptorSetLayout;

	LightManager(VK_Renderer& renderer);
	~LightManager();

	void AddLight(PointLight);

	void CalculateLightMaps();

	void CreateDescriptorPool();
	void CreateDescriptorSetLayout();
	void CreateDescriptorSets();
	void CreateLightBuffer();
	void UpdateLightInfos(uint32_t currentImage);
};

