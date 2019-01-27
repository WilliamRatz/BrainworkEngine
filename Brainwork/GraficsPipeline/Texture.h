#pragma once
#include "VK_inc.h"

class VK_BufferObject;
class VK_Renderer;

class Texture 
{
private:
	VK_Renderer*			m_renderer;
	std::string				m_texturePath;
	VkImage					m_textureImage;
	VkDeviceMemory			m_textureImageMemory;

	void CreateTextureImage			();
	void CreateTextureImageViews	();
	void CreateTextureSampler		();
	void CopyBufferToImage			(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

public:
	VkSampler				textureSampler;
	VkImageView				textureImageView;

	Texture					();
	Texture					(std::string texturePath);
	Texture					(const Texture& texture);
	~Texture				();

	void CreateTexture		(VK_Renderer* renderer);

	void CleanUpTexture		();

	void operator=(const Texture&);
};

