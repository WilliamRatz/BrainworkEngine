#ifndef VULKAN_H
#define VULKAN_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <BW_Math.h>

#include "VK_Window.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <array>
#include <optional>
#include <set>



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

//VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback) 
//{
//	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
//	if (func != nullptr) {
//		return func(instance, pCreateInfo, pAllocator, pCallback);
//	}
//	else {
//		return VK_ERROR_EXTENSION_NOT_PRESENT;
//	}
//}
//
//void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator) {
//	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
//	if (func != nullptr) {
//		func(instance, callback, pAllocator);
//	}
//}

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

struct Vertex {
	Quaternion pos;
	Vector3 color;

	Vertex(float a1, float a2, float a3, float a4, float b1, float b2, float b3)
	{
		pos = Quaternion(a1, a2, a3, a4);
		color = Vector3(b1, b2, b3);
	}

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

struct UniformBufferObject {
	Matrix<float, 4, 4> model;
	Matrix<float, 4, 4> view;
	Matrix<float, 4, 4> proj;
};

const std::vector<Vertex> vertices = {
	Vertex(-0.5f,  -0.5f,  1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
	Vertex( 0.5f,  -0.5f,  1.0f, 1.0f,		1.0f, 1.0f, 0.0f),
	Vertex( 0.5f,   0.5f,  1.0f, 1.0f,		1.0f, 0.5f, 0.5f),
	Vertex(-0.5f,   0.5f,  1.0f, 1.0f,		1.0f, 0.0f, 0.1f)

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

	GLFWwindow* window;
	VkInstance instance;
	VkSurfaceKHR surface;
	bool framebufferResized = false;
private:

	VkDebugUtilsMessengerEXT callback;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;

	

	void VK_initVulkan();//Vulkan

	void VK_mainLoop();//Vulkan

	void VK_cleanupSwapChain();//SwapChain

	void VK_cleanup();//Vulkan

	void VK_recreateSwapChain();//SwapChain

	void VK_createInstance();//Vulkan

	void VK_setupDebugCallback();//Debug

	

	void VK_pickPhysicalDevice();//Vulkan

	void VK_createLogicalDevice();//Vulkan

	void VK_createSwapChain();//SwapChain

	void VK_createImageViews();//SwapChain

	void VK_createRenderPass();//Render

	void VK_createDescriptorSetLayout();//Render

	void VK_createGraphicsPipeline();//GarficsPipe

	void VK_createFramebuffers();//SwapChain

	void VK_createCommandPool();//Vulkan

	void VK_createVertexBuffer();//Buffer

	void VK_createIndexBuffer();//Buffer

	void VK_createUniformBuffers();//Buffer

	void VK_createDescriptorPool();//Vulkan

	void VK_createDescriptorSets();//Render

	void VK_createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);//Buffer

	void VK_copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);//Buffer

	uint32_t VK_findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);//Vulkan

	void VK_createCommandBuffers();//Buffer

	void VK_createSyncObjects();//Vulkan

	void VK_updateUniformBuffer(uint32_t currentImage);//Swapchain

	void VK_drawFrame();//Swapchain

	VkShaderModule VK_createShaderModule(const std::vector<char>& code);//Graficspipe

	VkSurfaceFormatKHR VK_chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);//Swapchain

	VkPresentModeKHR VK_chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);//SWapchain

	VkExtent2D VK_chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);//swapchain

	SwapChainSupportDetails VK_querySwapChainSupport(VkPhysicalDevice device);//swapchain

	bool VK_isDeviceSuitable(VkPhysicalDevice device);//Vulkan

	bool VK_checkDeviceExtensionSupport(VkPhysicalDevice device);//Vulkan

	QueueFamilyIndices VK_findQueueFamilies(VkPhysicalDevice device);//Vulkan

	std::vector<const char*> VK_getRequiredExtensions();//Vulkan

	bool VK_checkValidationLayerSupport();//Vulkan

	static std::vector<char> VK_readFile(const std::string& filename);//GarficsPipe

	static VKAPI_ATTR VkBool32 VKAPI_CALL VK_debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);//Debug
};

#endif /* Vulkan_h */
