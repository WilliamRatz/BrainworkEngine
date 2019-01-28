#ifndef VK_BUFFERMANAGER_H
#define VK_BUFFERMANAGER_H
#include "VK_inc.h"
#include "GameObject.h"

class VK_Renderer;
class VK_GraphicsPipeline;
class LightManager;

class VK_GameObjectManager
{
private:
	VK_Renderer*					m_pRenderer;

	std::vector<GameObject>			m_gameObjects;
public:

	VK_GameObjectManager			(VK_Renderer& p_renderer);

	void UpdateGameObjects			(uint32_t currentImage);

	void AddGameObject				(GameObject& gameObject);
	void CreateBufferObjects		();
	void CreateDescriptorSets		();

	std::vector<GameObject>		GetGameObjects		();
	std::vector<GameObject>&	GetGameObjectsRef	();


	void CleanUpBuffers				();
};

#endif // !VK_BUFFERMANAGER_H