#pragma once
#include "VK_inc.h"

class PointLight;
class VK_Renderer;
class GameObject;

class LightManager
{
public:
	VK_Renderer*			m_pRenderer;

	std::vector<PointLight> m_pointLights;

	LightManager(VK_Renderer& renderer);
	~LightManager();

	void AddLight(PointLight);

	void CalculateLightMaps();
	void CheckForObjectsInFurustum(std::vector<GameObject>& gameObjects);

	void CreateDescriptorSets();
	void CreateFrameBuffer();
	void CreateLightBuffer(size_t gameObjectCount);
	void UpdateLightInfos(uint32_t currentImage, GameObject* onlyOnePossibleForNow);
};

