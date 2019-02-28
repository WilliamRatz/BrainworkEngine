#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include "VK_inc.h"

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
	VK_Device*					m_pDevice;

	VkSwapchainKHR				m_swapChain;
	VkFormat					m_swapChainImageFormat;
	VkExtent2D					m_swapChainExtent;


	VkImage						m_depthImage;
	VkDeviceMemory				m_depthImageMemory;
	VkImageView					m_depthImageView;
	std::vector<VkImage>		m_swapChainImages;
	std::vector<VkImageView>	m_swapChainImageViews;
	std::vector<VkFramebuffer>	m_swapChainFramebuffers;
	std::vector<VkSemaphore>	m_imageAvailableSemaphores;
	std::vector<VkSemaphore>	m_renderFinishedSemaphores;
	std::vector<VkFence>		m_inFlightFences;
	const int					MAX_FRAMES_IN_FLIGHT = 2;

	VK_SwapChain				(VK_Device& device);
	VK_SwapChain				(const VK_SwapChain& swapchain);
	~VK_SwapChain				();

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
	bool					HasStencilComponent		(VkFormat format);

	void CleanUp();
};

#endif // !VK_SWAPCHAIN_H