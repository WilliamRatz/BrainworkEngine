#pragma once
#include "VK_inc.h"

class VK_BufferObject;
class VK_Renderer;

class Texture
{
private:
	VK_BufferObject*		m_bufferObject;
	VK_Renderer*			m_renderer;
	const char*				m_texturePath;
	VkImage					m_textureImage;
	VkDeviceMemory			m_textureImageMemory;

public:
	VkSampler				textureSampler;
	VkImageView				textureImageView;

	Texture					();
	Texture					(const char* texturePath);
	Texture					(const Texture& texture);
	~Texture				();
	void CreateTexture		(VK_BufferObject* bufferObject, VK_Renderer* renderer);
		
	void CreateTextureImage			();
	void CreateTextureImageViews	();
	void CreateTextureSampler		();
	void CopyBufferToImage			(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	void cleanup					();

	void operator=(const Texture&);
};

