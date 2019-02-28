#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include "VK_inc.h"

class VK_SwapChain;

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};
const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class VK_Device
{
private:

public:
	VK_Device					();

	VkDevice					device;
	VkPhysicalDevice			physicalDevice;
	VkSurfaceKHR				surface;

	VkInstance					instance;

	VkQueue						graphicsQueue;
	VkQueue						presentQueue;

	VkDebugUtilsMessengerEXT	callback;


	void PickPhysicalDevice				(VK_SwapChain& vk_SwapChain);
	void CreateLogicalDevice			();

	void CreateInstance					();

	void CreateSurface					(GLFWwindow* window);

	bool isDeviceSuitable				(VkPhysicalDevice& device, VK_SwapChain& vk_SwapChain);
	bool checkDeviceExtensionSupport	(VkPhysicalDevice device);

	std::vector<const char*>			getRequiredExtensions();

	uint32_t												findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	bool checkValidationLayerSupport						();
	void SetupDebugCallback									();
	VkResult CreateDebugUtilsMessengerEXT					(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
	void DestroyDebugUtilsMessengerEXT						(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
	QueueFamilyIndices findQueueFamilies					(VkPhysicalDevice device);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback		(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	void CleanUp();
	
};

#endif // !VK_DEVICE_H