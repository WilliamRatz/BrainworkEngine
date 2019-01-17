#include "VK_BufferObject.h"
#include "VK_Device.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "Objects.h"
#include "Material.h"


VK_BufferObject::VK_BufferObject()
{
}
VK_BufferObject::~VK_BufferObject()
{
}


void VK_BufferObject::SetRenderer(VK_Renderer* p_renderer)
{
	m_renderer = p_renderer;
}

void VK_BufferObject::CleanupBufferObject()
{

	for (size_t i = 0; i < m_uniformBuffers.size(); ++i) {
		vkDestroyBuffer(m_renderer->vk_device->device, m_uniformBuffers[i], nullptr);
		vkFreeMemory(m_renderer->vk_device->device, m_uniformBuffersMemory[i], nullptr);
	}

	vkDestroyBuffer(m_renderer->vk_device->device, m_indexBuffer, nullptr);
	vkFreeMemory(m_renderer->vk_device->device, m_indexBufferMemory, nullptr);

	vkDestroyBuffer(m_renderer->vk_device->device, m_vertexBuffer, nullptr);
	vkFreeMemory(m_renderer->vk_device->device, m_vertexBufferMemory, nullptr);
}


void VK_BufferObject::CreateVertexBuffer(std::vector<Vertex> vertices) {
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	CreateBuffer(m_renderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(m_renderer->vk_device->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(m_renderer->vk_device->device, stagingBufferMemory);

	CreateBuffer(m_renderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vertexBuffer, m_vertexBufferMemory);

	CopyBuffer(stagingBuffer, m_vertexBuffer, bufferSize);

	vkDestroyBuffer(m_renderer->vk_device->device, stagingBuffer, nullptr);
	vkFreeMemory(m_renderer->vk_device->device, stagingBufferMemory, nullptr);
}
void VK_BufferObject::CreateIndexBuffer(std::vector<uint32_t> indices) {
	VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	CreateBuffer(m_renderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(m_renderer->vk_device->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices.data(), (size_t)bufferSize);
	vkUnmapMemory(m_renderer->vk_device->device, stagingBufferMemory);

	CreateBuffer(m_renderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_indexBuffer, m_indexBufferMemory);

	CopyBuffer(stagingBuffer, m_indexBuffer, bufferSize);

	vkDestroyBuffer(m_renderer->vk_device->device, stagingBuffer, nullptr);
	vkFreeMemory(m_renderer->vk_device->device, stagingBufferMemory, nullptr);
}
void VK_BufferObject::CreateUniformBuffers() {

	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	m_uniformBuffers.resize(m_renderer->vk_swapChain->swapChainImages.size());
	m_uniformBuffersMemory.resize(m_renderer->vk_swapChain->swapChainImages.size());

	for (size_t i = 0; i < m_renderer->vk_swapChain->swapChainImages.size(); ++i) {
		CreateBuffer(m_renderer, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_uniformBuffers[i], m_uniformBuffersMemory[i]);
	}
}
void VK_BufferObject::CreateDescriptorSet(Material& material) {

	std::vector<VkDescriptorSetLayout> layouts(m_renderer->vk_swapChain->swapChainImages.size(), m_renderer->descriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_renderer->descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(m_renderer->vk_swapChain->swapChainImages.size());
	allocInfo.pSetLayouts = layouts.data();

	m_descriptorSets.resize(m_renderer->vk_swapChain->swapChainImages.size());
	if (vkAllocateDescriptorSets(m_renderer->vk_device->device, &allocInfo, m_descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < m_renderer->vk_swapChain->swapChainImages.size(); ++i) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = m_uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkDescriptorImageInfo imageInfo = {};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = material.GetTextureRef().textureImageView;
		imageInfo.sampler = material.GetTextureRef().textureSampler;

		std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = m_descriptorSets[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = m_descriptorSets[i];
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pImageInfo = &imageInfo;

		vkUpdateDescriptorSets(m_renderer->vk_device->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}

}

void VK_BufferObject::UpdateUniformBuffer(UniformBufferObject& ubo, uint32_t& currentImage)
{
	void* data;
	vkMapMemory(m_renderer->vk_device->device, m_uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(m_renderer->vk_device->device, m_uniformBuffersMemory[currentImage]);
}

void VK_BufferObject::CreateBuffer(VK_Renderer* p_renderer, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(p_renderer->vk_device->device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(p_renderer->vk_device->device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = p_renderer->vk_device->findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(p_renderer->vk_device->device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(p_renderer->vk_device->device, buffer, bufferMemory, 0);
}
void VK_BufferObject::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
	VkCommandBuffer commandBuffer = m_renderer->beginSingleTimeCommands();

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	m_renderer->endSingleTimeCommands(commandBuffer);
}

std::vector<VkDescriptorSet> VK_BufferObject::GetDescriptorSets()
{
	return m_descriptorSets;
}
VkBuffer VK_BufferObject::GetIndexBuffer()
{
	return m_indexBuffer;
}
VkBuffer VK_BufferObject::GetVertexBuffer()
{
	return m_vertexBuffer;
}
std::vector<VkBuffer> VK_BufferObject::GetUniformBuffers()
{
	return m_uniformBuffers;
}
