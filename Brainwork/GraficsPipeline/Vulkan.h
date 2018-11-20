#ifndef VULKAN_H
#define VULKAN_H

#include "Standarts.h"

#include "VK_Window.h"


const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif



struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct UniformBufferObject {
	Matrix<float, 4, 4> model;
	Matrix<float, 4, 4> view;
	Matrix<float, 4, 4> proj;
};

const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
};

class Vulkan {
public:
	void run() {
		VK_initWindow(*this);
		VK_initVulkan();
		VK_mainLoop();
		VK_cleanup();
	}

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	VkDevice device;
	VkInstance instance;
	bool framebufferResized = false;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;




	QueueFamilyIndices VK_findQueueFamilies(VkPhysicalDevice device);//Vulkan
	VkQueue graphicsQueue;
	VkCommandPool commandPool;
private:

	VkDebugUtilsMessengerEXT callback;


	VkQueue presentQueue;

	

	


	

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	
	
	void VK_cleanupSwapChain() {
		for (auto framebuffer : swapChainFramebuffers) {
			vkDestroyFramebuffer(device, framebuffer, nullptr);
		}

		vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

		vkDestroyPipeline(device, graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
		vkDestroyRenderPass(device, renderPass, nullptr);

		for (auto imageView : swapChainImageViews) {
			vkDestroyImageView(device, imageView, nullptr);
		}

		vkDestroySwapchainKHR(device, swapChain, nullptr);
	}

	void VK_initVulkan();//Vulkan

	void VK_mainLoop();//Vulkan


	void VK_cleanup();//Vulkan


	void VK_createInstance();//Vulkan


	

	void VK_pickPhysicalDevice();//Vulkan

	void VK_createLogicalDevice();//Vulkan

	

	void VK_createCommandPool();//Vulkan




	void VK_createDescriptorPool();//Vulkan




	


	void VK_createSyncObjects();//Vulkan

	

	bool VK_isDeviceSuitable(VkPhysicalDevice device);//Vulkan

	bool VK_checkDeviceExtensionSupport(VkPhysicalDevice device);//Vulkan


	std::vector<const char*> VK_getRequiredExtensions();//Vulkan

	bool VK_checkValidationLayerSupport();//Vulkan


};

#endif /* Vulkan_h */
