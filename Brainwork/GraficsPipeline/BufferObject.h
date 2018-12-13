#pragma once

#include "Buffer.h"

class BufferObject : public Buffer
{
public:
	Cube cube;
	GameObject gameObject = GameObject(cube);

	BufferObject(VK_Object& vk_Object)
		:Buffer(vk_Object)
	{
		this->createVertexBuffer(gameObject.getVertices());
		this->createIndexBuffer(gameObject.getIndices());
		this->createUniformBuffers();
	};

	void updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo = {};

		//gameObject.m_matrix.rotation3DAroundZ(0.03f).rotation3DAroundY(-0.01f).rotation3DAroundX(0.02f);
		ubo.model = gameObject.m_matrix;
		ubo.view = Camera::getViewCamera.mat;
		ubo.proj.perspectivProjection((WIDTH < HEIGHT) ? (float)WIDTH / (float)HEIGHT : 1, (HEIGHT < WIDTH) ? (float)HEIGHT / (float)WIDTH : 1, 1, 60);
		ubo.proj[1][1] *= -1;

		void* data;
		vkMapMemory(VKO->device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(VKO->device, uniformBuffersMemory[currentImage]);
	}
	
	void cleanup() 
	{

		for (size_t i = 0; i < uniformBuffers.size(); ++i) {
			vkDestroyBuffer(VKO->device, uniformBuffers[i], nullptr);
			vkFreeMemory(VKO->device, uniformBuffersMemory[i], nullptr);
		}

		vkDestroyBuffer(VKO->device, indexBuffer, nullptr);
		vkFreeMemory(VKO->device, indexBufferMemory, nullptr);

		vkDestroyBuffer(VKO->device, vertexBuffer, nullptr);
		vkFreeMemory(VKO->device, vertexBufferMemory, nullptr);
	}

};

