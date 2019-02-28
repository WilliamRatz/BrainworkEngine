#ifndef VK_BUFFEROBJECT_H
#define VK_BUFFEROBJECT_H

#include "VK_inc.h"

class VK_Renderer;
class Material;
class Lighting;
struct Vertex;

class VK_BufferObject
{
private:
	std::vector<VkDescriptorSet>	m_descriptorSets;
	std::vector<VkBuffer>			m_uniformBuffers;
	std::vector<VkDeviceMemory>		m_uniformBuffersMemory;

	VkDeviceMemory					m_vertexBufferMemory;
	VkBuffer						m_vertexBuffer;
	VkBuffer						m_indexBuffer;
	VkDeviceMemory					m_indexBufferMemory;

public:
	VK_Renderer*					m_pRenderer;

	VK_BufferObject				();
	~VK_BufferObject			();

	void SetRenderer			(VK_Renderer* renderer);

	void CreateVertexBuffer		(std::vector<Vertex>& vertices);
	void CreateIndexBuffer		(std::vector<uint32_t>& indices);
	void CreateUniformBuffers	(Lighting& p_lighting);
	void CreateDescriptorSet	(Material& texture, Lighting& lighting);

	void UpdateUniformBuffer	(UniformBufferObject& ubo, uint32_t& currentImage);

	static void CreateBuffer	(VK_Renderer* renderer, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer				(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkBuffer&						GetIndexBufferRef		();
	VkBuffer&						GetVertexBufferRef		();
	std::vector<VkBuffer>&			GetUniformBuffersRef	();
	std::vector<VkDescriptorSet>&	GetDescriptorSetsRef	();

	void CleanUp();
};


#endif // !VK_BUFFEROBJECT_H
