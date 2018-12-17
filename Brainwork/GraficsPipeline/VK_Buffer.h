#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include "Camera.h"
#include "GameObject.h"


class VK_Renderer;

class Buffer
{
protected:
	VK_Renderer*						renderer;

	VkDeviceMemory					vertexBufferMemory;
	VkDeviceMemory					indexBufferMemory;
	std::vector<VkBuffer>			uniformBuffers;
	std::vector<VkDeviceMemory>		uniformBuffersMemory;

public:
	Buffer							(VK_Renderer& renderer);

	VkBuffer						indexBuffer;
	VkBuffer						vertexBuffer;
	std::vector<VkDescriptorSet>	descriptorSets;

	void createVertexBuffer			(std::vector<Vertex> vertices);
	void createIndexBuffer			(std::vector<uint16_t> indices);
	void createUniformBuffers		();
	void createDescriptorSets		();

	void createBuffer				(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer					(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	uint32_t findMemoryType			(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

struct UniformBufferObject {
	Matrix<float, 4, 4> model;
	Matrix<float, 4, 4> view;
	Matrix<float, 4, 4> proj;
};
#endif // !VK_BUFFER_H