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
private:
	VK_Device*					vk_device;

public:
	VK_SwapChain				(VK_Device& p_vk_device);

	VkSwapchainKHR				swapChain;
	VkFormat					swapChainImageFormat;
	VkExtent2D					swapChainExtent;
	std::vector<VkImage>		swapChainImages;
	std::vector<VkImageView>	swapChainImageViews;
	std::vector<VkFramebuffer>	swapChainFramebuffers;
	std::vector<VkSemaphore>	imageAvailableSemaphores;
	std::vector<VkSemaphore>	renderFinishedSemaphores;
	std::vector<VkFence>		inFlightFences;
	const int					MAX_FRAMES_IN_FLIGHT = 2;

	void CreateImageViews		();
	void CreateSwapChain		(GLFWwindow* window);
	void CreateFramebuffers		(VK_Renderer& renderer);

	void RecreateSwapChain		(GLFWwindow* window, VK_BufferManager& vkBuffer, VK_Renderer& renderer);
	void CleanupSwapChain		(VK_Renderer renderer);

	void CreateSyncObjects		();

	VkPresentModeKHR ChooseSwapPresentMode			(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat		(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkExtent2D ChooseSwapExtent						(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
	SwapChainSupportDetails querySwapChainSupport	(VkPhysicalDevice device);
};

#endif // !VK_SWAPCHAIN_H