#ifndef VK_BUFFERMANAGER_H
#define VK_BUFFERMANAGER_H
#include "VK_inc.h"
#include "GameObject.h"

class VK_Renderer;
class VK_GraphicsPipeline;

class VK_GameObjectManager
{
private:
	VK_Renderer*					renderer;

public:
	std::vector<VkCommandBuffer>	commandBuffers;
	std::vector<GameObject>			gameObjects;

	VK_GameObjectManager			(VK_Renderer& p_renderer);

	void UpdateUniformBuffers		(uint32_t currentImage);

	void CreateBufferObjects		();
	void CreateDescriptorSets		();
	void CreateCommandBuffers		(VK_GraphicsPipeline& vk_graphicsPipeline);

	void CleanUpBuffers				();
};

#endif // !VK_BUFFERMANAGER_H