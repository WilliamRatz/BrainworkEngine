#ifndef VK_WINDOW
#define VK_WINDOW

#include "VK_Device.h"


const int WIDTH = 800;
const int HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VK_Window {
private:
	VkDebugUtilsMessengerEXT callback;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;

	VK_Device vk_device;
	VK_Debug vk_debug;
	VK_Render vk_Render;
	VK_GraficsPipeline vk_GraficsPipeline;
	VK_Buffer vk_Buffer;

public:

	GLFWwindow* window;
	bool framebufferResized = false;


	void run() {
		VK_initWindow();
		VK_initVulkan();
		VK_mainLoop();
		VK_cleanup();
	}

	

	void VK_initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, VK_framebufferResizeCallback);
	}

	void VK_initVulkan() {
		vk_device.VK_createInstance();
		vk_debug.VK_setupDebugCallback();
		VK_createSurface();
		vk_device.VK_pickPhysicalDevice();
		vk_device.VK_createLogicalDevice();
		vk_SwapChain.VK_createSwapChain();
		vk_SwapChain.VK_createImageViews();
		vk_Render.VK_createRenderPass();
		vk_Render.VK_createDescriptorSetLayout();
		vk_GraficsPipeline.VK_createGraphicsPipeline();
		vk_Buffer.VK_createFramebuffers();
		vk_device.VK_createCommandPool();
		vk_Buffer.VK_createVertexBuffer();
		vk_Buffer.VK_createIndexBuffer();
		vk_Buffer.VK_createUniformBuffers();
		vk_SwapChain.VK_createDescriptorPool();
		vk_SwapChain.VK_createDescriptorSets();
		vk_Buffer.VK_createCommandBuffers();
		VK_createSyncObjects();
	}

	void VK_mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			VK_drawFrame();
		}

		vkDeviceWaitIdle(device);
	}
	
	void VK_cleanup() {
		VK_cleanupSwapChain();

		vkDestroyDescriptorPool(device, descriptorPool, nullptr);

		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

		for (size_t i = 0; i < vk_SwapChain.swapChainImages.size(); i++) {
			vkDestroyBuffer(device, uniformBuffers[i], nullptr);
			vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
		}

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);

		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(device, inFlightFences[i], nullptr);
		}

		vkDestroyCommandPool(device, commandPool, nullptr);

		vkDestroyDevice(device, nullptr);

		/*if (enableValidationLayers) {
			DestroyDebugUtilsMessengerEXT(instance, callback, nullptr);
		}*/

		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}

	void VK_createSurface() {
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

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
	void VK_createSyncObjects() {
		imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}
	void VK_framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<Vulkan*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	}
};
#endif // VK_WINDOW
