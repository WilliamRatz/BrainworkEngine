#ifndef VK_BUFFEROBJECT_H
#define VK_BUFFEROBJECT_H

#include "VK_inc.h"

class VK_Renderer;
class Material;
struct Vertex;
struct UniformBufferObject;

class VK_BufferObject
{
private:

	VkBuffer						m_indexBuffer;
	VkBuffer						m_vertexBuffer;
	std::vector<VkBuffer>			m_uniformBuffers;
	VkDeviceMemory					m_vertexBufferMemory;
	VkDeviceMemory					m_indexBufferMemory;
	std::vector<VkDeviceMemory>		m_uniformBuffersMemory;
	std::vector<VkDescriptorSet>	m_descriptorSets;

public:
	VK_Renderer*					m_renderer;

	VK_BufferObject				();
	~VK_BufferObject			();

	void SetRenderer			(VK_Renderer* renderer);

	void CreateVertexBuffer		(std::vector<Vertex> vertices);
	void CreateIndexBuffer		(std::vector<uint32_t> indices);
	void CreateUniformBuffers	();
	void CreateDescriptorSet	(Material& texture);

	void UpdateUniformBuffer	(UniformBufferObject& ubo, uint32_t& currentImage);

	static void CreateBuffer	(VK_Renderer* renderer, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer				(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkBuffer						GetIndexBuffer		();
	VkBuffer						GetVertexBuffer		();
	std::vector<VkBuffer>			GetUniformBuffers	();
	std::vector<VkDescriptorSet>	GetDescriptorSets	();

	void CleanupBufferObject();
};


#endif // !VK_BUFFEROBJECT_H
