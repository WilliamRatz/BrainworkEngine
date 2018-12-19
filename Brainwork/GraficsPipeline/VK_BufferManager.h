#ifndef VK_BUFFERMANAGER_H
#define VK_BUFFERMANAGER_H

#include "VK_BufferObject.h"

class VK_Renderer;

class VK_BufferManager
{
private:
	VK_Renderer*					renderer;

public:
	std::vector<VkCommandBuffer>	commandBuffers;
	std::vector<VK_BufferObject>	bufferObjects;

	VK_BufferManager				(VK_Renderer& p_renderer);

	void UpdateUniformBuffers		(uint32_t currentImage);

	void CreateBufferObjects		();
	void CreateDescriptorSets		();
	void CreateCommandBuffers		();

	void CleanUpBuffers				();
};

#endif // !VK_BUFFERMANAGER_H