#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include "VK_BufferManager.h"
#include "VK_Renderer.h"

class VK_Device;
class VK_Renderer;

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VK_SwapChain
{
public:

public:
	VK_Device*					vk_device;
	VK_SwapChain				(VK_Device& p_vk_device);

	VkSwapchainKHR				swapChain;
	VkFormat					swapChainImageFormat;
	VkExtent2D					swapChainExtent;
	VkImage						depthImage;
	VkDeviceMemory				depthImageMemory;
	VkImageView					depthImageView;
	std::vector<VkImage>		swapChainImages;
	std::vector<VkImageView>	swapChainImageViews;
	std::vector<VkFramebuffer>	swapChainFramebuffers;
	std::vector<VkSemaphore>	imageAvailableSemaphores;
	std::vector<VkSemaphore>	renderFinishedSemaphores;
	std::vector<VkFence>		inFlightFences;
	const int					MAX_FRAMES_IN_FLIGHT = 2;

	void CreateImage			(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void CreateImageViews		();
	void CreateSwapChain		(GLFWwindow* window);
	void CreateDepthResources	(VK_Renderer& renderer);


	void CreateSyncObjects		();

	void TransitionImageLayout	(VK_Renderer& renderer, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	VkImageView				CreateImageView			(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	VkPresentModeKHR		ChooseSwapPresentMode	(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkSurfaceFormatKHR		ChooseSwapSurfaceFormat	(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkExtent2D				ChooseSwapExtent		(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
	SwapChainSupportDetails querySwapChainSupport	(VkPhysicalDevice device);
	VkFormat				findSupportedFormat		(const std::vector<VkFormat>& formats, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat				findDepthFormat			();
	bool					isFormatSupported		(VkFormat format, VkImageTiling tiling, VkFormatFeatureFlags features);
	bool					HasStencilComponent		(VkFormat format) {
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}

};

#endif // !VK_SWAPCHAIN_H