#include "VK_BufferObject.h"
#include "VK_Device.h"
#include "VK_Renderer.h"


BufferObject::BufferObject(VK_Renderer& renderer)
	:Buffer(renderer)
{
	this->createVertexBuffer(gameObject.getVertices());
	this->createIndexBuffer(gameObject.getIndices());
	this->createUniformBuffers();
};

void BufferObject::updateUniformBuffer(uint32_t currentImage) {
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	UniformBufferObject ubo = {};

	//gameObject.m_matrix.rotation3DAroundZ(0.03f).rotation3DAroundY(-0.01f).rotation3DAroundX(0.02f);
	ubo.model = gameObject.getGlobalMatrix();
	ubo.view = Camera::getViewCamera.mat;
	ubo.proj.perspectivProjection((WIDTH < HEIGHT) ? (float)WIDTH / (float)HEIGHT : 1, (HEIGHT < WIDTH) ? (float)HEIGHT / (float)WIDTH : 1, 1, 60);
	ubo.proj[1][1] *= -1;

	void* data;
	vkMapMemory(renderer->vk_device->device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(renderer->vk_device->device, uniformBuffersMemory[currentImage]);
}

void BufferObject::cleanup()
{

	for (size_t i = 0; i < uniformBuffers.size(); ++i) {
		vkDestroyBuffer(renderer->vk_device->device, uniformBuffers[i], nullptr);
		vkFreeMemory(renderer->vk_device->device, uniformBuffersMemory[i], nullptr);
	}

	vkDestroyBuffer(renderer->vk_device->device, indexBuffer, nullptr);
	vkFreeMemory(renderer->vk_device->device, indexBufferMemory, nullptr);

	vkDestroyBuffer(renderer->vk_device->device, vertexBuffer, nullptr);
	vkFreeMemory(renderer->vk_device->device, vertexBufferMemory, nullptr);
}