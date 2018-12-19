#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include "Camera.h"
#include "GameObject.h"


class VK_Renderer;

class VK_Buffer
{
protected:
	VkDeviceMemory					vertexBufferMemory;
	VkDeviceMemory					indexBufferMemory;
	std::vector<VkBuffer>			uniformBuffers;
	std::vector<VkDeviceMemory>		uniformBuffersMemory;

public:
	VK_Buffer							(VK_Renderer& renderer);

	VK_Renderer*					renderer;
	VkBuffer						indexBuffer;
	VkBuffer						vertexBuffer;
	std::vector<VkDescriptorSet>	descriptorSets;

	void createVertexBuffer			(std::vector<Vertex> vertices);
	void createIndexBuffer			(std::vector<uint16_t> indices);
	void createUniformBuffers		();
	void createDescriptorSets		(Texture& texture);

	void createBuffer				(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void copyBuffer					(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	uint32_t findMemoryType			(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

struct UniformBufferObject {
	Matrix<float, 4, 4> model;
	Matrix<float, 4, 4> view;
	Matrix<float, 4, 4> proj;
};
#endif // !VK_BUFFER_H