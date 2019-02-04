#include "VK_BufferObject.h"
#include "VK_Device.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "Objects.h"
#include "Material.h"
#include "Lighting.h"
#include "PointLight.h"

VK_BufferObject::VK_BufferObject()
{
}
VK_BufferObject::~VK_BufferObject()
{
}


void VK_BufferObject::SetRenderer(VK_Renderer* p_renderer)
{
	m_pRenderer = p_renderer;
}

void VK_BufferObject::CleanUp()
{

	for (size_t i = 0; i < m_uniformBuffers.size(); ++i) {
		vkDestroyBuffer(m_pRenderer->m_pDevice->device, m_uniformBuffers[i], nullptr);
		vkFreeMemory(m_pRenderer->m_pDevice->device, m_uniformBuffersMemory[i], nullptr);
	}

	vkDestroyBuffer(m_pRenderer->m_pDevice->device, m_indexBuffer, nullptr);
	vkFreeMemory(m_pRenderer->m_pDevice->device, m_indexBufferMemory, nullptr);

	vkDestroyBuffer(m_pRenderer->m_pDevice->device, m_vertexBuffer, nullptr);
	vkFreeMemory(m_pRenderer->m_pDevice->device, m_vertexBufferMemory, nullptr);
}


void VK_BufferObject::CreateVertexBuffer(std::vector<Vertex>& vertices) {
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	CreateBuffer(m_pRenderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(m_pRenderer->m_pDevice->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(m_pRenderer->m_pDevice->device, stagingBufferMemory);

	CreateBuffer(m_pRenderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vertexBuffer, m_vertexBufferMemory);

	CopyBuffer(stagingBuffer, m_vertexBuffer, bufferSize);

	vkDestroyBuffer(m_pRenderer->m_pDevice->device, stagingBuffer, nullptr);
	vkFreeMemory(m_pRenderer->m_pDevice->device, stagingBufferMemory, nullptr);
}
void VK_BufferObject::CreateIndexBuffer(std::vector<uint32_t>& indices) {
	VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	CreateBuffer(m_pRenderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(m_pRenderer->m_pDevice->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices.data(), (size_t)bufferSize);
	vkUnmapMemory(m_pRenderer->m_pDevice->device, stagingBufferMemory);

	CreateBuffer(m_pRenderer, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_indexBuffer, m_indexBufferMemory);

	CopyBuffer(stagingBuffer, m_indexBuffer, bufferSize);

	vkDestroyBuffer(m_pRenderer->m_pDevice->device, stagingBuffer, nullptr);
	vkFreeMemory(m_pRenderer->m_pDevice->device, stagingBufferMemory, nullptr);
}
void VK_BufferObject::CreateUniformBuffers() {

	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	m_uniformBuffers.resize(m_pRenderer->m_pSwapChain->m_swapChainImages.size());
	m_uniformBuffersMemory.resize(m_pRenderer->m_pSwapChain->m_swapChainImages.size());

	for (size_t i = 0; i < m_pRenderer->m_pSwapChain->m_swapChainImages.size(); ++i) {
		CreateBuffer(m_pRenderer, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_uniformBuffers[i], m_uniformBuffersMemory[i]);
	}
}
void VK_BufferObject::CreateDescriptorSet(Material& p_material, Lighting& p_lighting) {

	std::vector<VkDescriptorSetLayout> layouts(m_pRenderer->m_pSwapChain->m_swapChainImages.size(), m_pRenderer->GetDescriptorSetLayoutRef());
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_pRenderer->GetDescriptorPoolRef();
	allocInfo.descriptorSetCount = static_cast<uint32_t>(m_pRenderer->m_pSwapChain->m_swapChainImages.size());
	allocInfo.pSetLayouts = layouts.data();

	m_descriptorSets.resize(m_pRenderer->m_pSwapChain->m_swapChainImages.size());
	if (vkAllocateDescriptorSets(m_pRenderer->m_pDevice->device, &allocInfo, m_descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < m_pRenderer->m_pSwapChain->m_swapChainImages.size(); ++i) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = m_uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkDescriptorImageInfo diffuseMap = {};
		diffuseMap.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		diffuseMap.imageView = p_material.GetTextureRef().textureImageView;
		diffuseMap.sampler = p_material.GetTextureRef().textureSampler;

		VkDescriptorImageInfo lightInfo = {};
		lightInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		lightInfo.imageView = p_lighting.GetPointLightRef()[0]->GetImageViewRef();
		lightInfo.sampler = p_lighting.GetPointLightRef()[0]->GetVkSamplerRef();

		std::array<VkWriteDescriptorSet, 3> descriptorWrites = {};

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
		descriptorWrites[1].pImageInfo = &diffuseMap;

		descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[2].dstSet = m_descriptorSets[i];
		descriptorWrites[2].dstBinding = 2;
		descriptorWrites[2].dstArrayElement = 0;
		descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[2].descriptorCount = 1;
		descriptorWrites[2].pImageInfo = &lightInfo;

		vkUpdateDescriptorSets(m_pRenderer->m_pDevice->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}

}

void VK_BufferObject::UpdateUniformBuffer(UniformBufferObject& ubo, uint32_t& currentImage)
{
	void* data;
	vkMapMemory(m_pRenderer->m_pDevice->device, m_uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(m_pRenderer->m_pDevice->device, m_uniformBuffersMemory[currentImage]);
}

void VK_BufferObject::CreateBuffer(VK_Renderer* p_renderer, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(p_renderer->m_pDevice->device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(p_renderer->m_pDevice->device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = p_renderer->m_pDevice->findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(p_renderer->m_pDevice->device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(p_renderer->m_pDevice->device, buffer, bufferMemory, 0);
}
void VK_BufferObject::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
	VkCommandBuffer commandBuffer = m_pRenderer->beginSingleTimeCommands();

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	m_pRenderer->endSingleTimeCommands(commandBuffer);
}

std::vector<VkDescriptorSet>& VK_BufferObject::GetDescriptorSetsRef()
{
	return m_descriptorSets;
}
VkBuffer& VK_BufferObject::GetIndexBufferRef()
{
	return m_indexBuffer;
}
VkBuffer& VK_BufferObject::GetVertexBufferRef()
{
	return m_vertexBuffer;
}
std::vector<VkBuffer>& VK_BufferObject::GetUniformBuffersRef()
{
	return m_uniformBuffers;
}
