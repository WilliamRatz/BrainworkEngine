#pragma once
#include "VK_Device.h"
#include "VK_SwapChain.h"
#include "VK_Buffer.h"
#include "Camera.h"

class VK_Window
{
public:
	VK_Window() {

	};

	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

	VK_Buffer vk_Buffer = VK_Buffer(VKO);

private:

	VK_Object VKO = VK_Object();
	VK_Device vk_Device = VK_Device(VKO);
	VK_SwapChain vk_SwapChain = VK_SwapChain(VKO);
	

	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		VKO.window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		glfwSetWindowUserPointer(VKO.window, this);
		glfwSetFramebufferSizeCallback(VKO.window, framebufferResizeCallback);
	}

	void initVulkan() {
		createInstance();
		vk_Device.setupDebugCallback();
		createSurface();
		vk_Device.pickPhysicalDevice();
		vk_Device.createLogicalDevice();
		vk_SwapChain.createSwapChain();
		vk_SwapChain.createImageViews();
		vk_SwapChain.createRenderPass();
		vk_Device.createDescriptorSetLayout();
		vk_Buffer.createGraphicsPipeline();
		vk_Buffer.createFramebuffers();
		vk_Device.createCommandPool();
		vk_Buffer.createVertexBuffer();
		vk_Buffer.createIndexBuffer();
		vk_Buffer.createUniformBuffers();
		vk_Device.createDescriptorPool();
		vk_Device.createDescriptorSets();
		vk_Buffer.createCommandBuffers();
		createSyncObjects();
	}
	
	void mainLoop() {
		while (!glfwWindowShouldClose(VKO.window)) {
			glfwPollEvents();
			drawFrame();

		}

		vkDeviceWaitIdle(VKO.device);
	}
	void drawFrame() {
		vkWaitForFences(VKO.device, 1, &VKO.inFlightFences[VKO.currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(VKO.device, VKO.swapChain, std::numeric_limits<uint64_t>::max(), VKO.imageAvailableSemaphores[VKO.currentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			vk_SwapChain.recreateSwapChain(vk_Buffer);
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		vk_Buffer.updateUniformBuffer(imageIndex);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { VKO.imageAvailableSemaphores[VKO.currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &VKO.commandBuffers[imageIndex];

		VkSemaphore signalSemaphores[] = { VKO.renderFinishedSemaphores[VKO.currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkResetFences(VKO.device, 1, &VKO.inFlightFences[VKO.currentFrame]);

		if (vkQueueSubmit(VKO.graphicsQueue, 1, &submitInfo, VKO.inFlightFences[VKO.currentFrame]) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { VKO.swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		result = vkQueuePresentKHR(VKO.presentQueue, &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || VKO.framebufferResized) {
			VKO.framebufferResized = false;
			vk_SwapChain.recreateSwapChain(vk_Buffer);
		}
		else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}

		VKO.currentFrame = (VKO.currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void cleanup() {
		vk_SwapChain.cleanupSwapChain();

		vkDestroyDescriptorPool(VKO.device, VKO.descriptorPool, nullptr);

		vkDestroyDescriptorSetLayout(VKO.device, VKO.descriptorSetLayout, nullptr);

		for (size_t i = 0; i < VKO.swapChainImages.size(); i++) {
			vkDestroyBuffer(VKO.device, VKO.uniformBuffers[i], nullptr);
			vkFreeMemory(VKO.device, VKO.uniformBuffersMemory[i], nullptr);
		}

		vkDestroyBuffer(VKO.device, vk_Buffer.indexBuffer, nullptr);
		vkFreeMemory(VKO.device, vk_Buffer.indexBufferMemory, nullptr);

		vkDestroyBuffer(VKO.device, vk_Buffer.vertexBuffer, nullptr);
		vkFreeMemory(VKO.device, vk_Buffer.vertexBufferMemory, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(VKO.device, VKO.renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(VKO.device, VKO.imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(VKO.device, VKO.inFlightFences[i], nullptr);
		}

		vkDestroyCommandPool(VKO.device, VKO.commandPool, nullptr);

		vkDestroyDevice(VKO.device, nullptr);

		if (enableValidationLayers) {
			vk_Device.DestroyDebugUtilsMessengerEXT(vk_Device.instance, VKO.callback, nullptr);
		}

		vkDestroySurfaceKHR(vk_Device.instance, VKO.surface, nullptr);
		vkDestroyInstance(vk_Device.instance, nullptr);

		glfwDestroyWindow(VKO.window);

		glfwTerminate();
	}
	void createSurface() {
		if (glfwCreateWindowSurface(vk_Device.instance, VKO.window, nullptr, &VKO.surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
		
	}
	void createInstance() {
		if (enableValidationLayers && !VKO.checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");
		}

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "BrainworkEngine Sample";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Brainwork";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_1;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateInstance(&createInfo, nullptr, &vk_Device.instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}
	std::vector<const char*> getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<VK_Window*>(glfwGetWindowUserPointer(window));
		app->VKO.framebufferResized = true;
	}
	void createSyncObjects() {
		VKO.imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		VKO.renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		VKO.inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(VKO.device, &semaphoreInfo, nullptr, &VKO.imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(VKO.device, &semaphoreInfo, nullptr, &VKO.renderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(VKO.device, &fenceInfo, nullptr, &VKO.inFlightFences[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}


};

