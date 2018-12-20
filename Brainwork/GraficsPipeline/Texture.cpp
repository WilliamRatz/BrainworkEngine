#include "Texture.h"
#include "VK_BufferObject.h"
#include "VK_Renderer.h"
#include "VK_Device.h"
#include "VK_SwapChain.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
}

Texture::Texture(VK_Buffer& p_vk_buffer)
{
	vk_buffer = &p_vk_buffer;
}

Texture::Texture(const Texture& texture)
{
	vk_buffer = texture.vk_buffer;
	textureImage = texture.textureImage;
	textureImageMemory = texture.textureImageMemory;
}

Texture::~Texture()
{
}

void Texture::SetBuffer(VK_Buffer& p_vk_renderer)
{
	vk_buffer = &p_vk_renderer;

}

void Texture::CreateTextureImage() {
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	VkDeviceSize imageSize = texWidth * texHeight * 4;

	if (!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	vk_buffer->createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(vk_buffer->renderer->vk_device->device, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(vk_buffer->renderer->vk_device->device, stagingBufferMemory);

	stbi_image_free(pixels);

	vk_buffer->renderer->vk_swapChain->CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

	vk_buffer->renderer->vk_swapChain->TransitionImageLayout(*vk_buffer->renderer,textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	CopyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
	vk_buffer->renderer->vk_swapChain->TransitionImageLayout(*vk_buffer->renderer,textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkDestroyBuffer(vk_buffer->renderer->vk_device->device, stagingBuffer, nullptr);
	vkFreeMemory(vk_buffer->renderer->vk_device->device, stagingBufferMemory, nullptr);
}
void Texture::CreateTextureImageViews()
{
	textureImageView = vk_buffer->renderer->vk_swapChain->CreateImageView(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
}

void Texture::CreateTextureSampler()
{
	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 16;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(vk_buffer->renderer->vk_device->device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}
}
void Texture::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
	VkCommandBuffer commandBuffer = vk_buffer->renderer->beginSingleTimeCommands();
	VkBufferImageCopy region = {};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		width,
		height,
		1
	};

	vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	vk_buffer->renderer->endSingleTimeCommands(commandBuffer);
}

void Texture::cleanup() {
	//after cleanup swapchain
	
	vkDestroySampler(vk_buffer->renderer->vk_device->device, textureSampler, nullptr);
	vkDestroyImageView(vk_buffer->renderer->vk_device->device, textureImageView, nullptr);

	vkDestroyImage(vk_buffer->renderer->vk_device->device, textureImage, nullptr);
	vkFreeMemory(vk_buffer->renderer->vk_device->device, textureImageMemory, nullptr);

}