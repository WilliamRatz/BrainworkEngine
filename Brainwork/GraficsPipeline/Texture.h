#pragma once
#include "VK_inc.h"



class VK_Buffer;

class Texture
{
private:
	VK_Buffer* vk_buffer;

public:
	VkSampler textureSampler;
	VkImage textureImage;
	VkImageView textureImageView;
	VkDeviceMemory textureImageMemory;

	Texture();
	Texture(VK_Buffer& vk_buffer);
	Texture(const Texture& texture);
	~Texture();

	void SetBuffer(VK_Buffer& vk_buffer);

	void CreateTextureImage();
	void CreateTextureImageViews();
	void CreateTextureSampler();
	void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	void cleanup();
};

