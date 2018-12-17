#include "VK_Window.h"

VK_Window::VK_Window() 
{
}

void VK_Window::run() 
{
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

void VK_Window::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	cam.SetCameraToWindow(window);
}

void VK_Window::initVulkan() {
	vk_Device.CreateInstance();
	vk_Device.SetupDebugCallback();
	vk_Device.CreateSurface(window);
	vk_Device.PickPhysicalDevice(vk_SwapChain);
	vk_Device.CreateLogicalDevice();
	vk_SwapChain.CreateSwapChain(window);
	vk_SwapChain.CreateImageViews();
	renderer.CreateRenderPass();
	renderer.CreateDescriptorSetLayout();
	renderer.CreateGraphicsPipeline();
	vk_SwapChain.CreateFramebuffers(renderer);
	renderer.CreateCommandPool();
	renderer.CreateDescriptorPool();
	vk_Buffer.CreateBufferObjects();

	vk_Buffer.CreateDescriptorSets();
	vk_Buffer.CreateCommandBuffers();
	vk_SwapChain.CreateSyncObjects();
}

void VK_Window::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawFrame();
		Camera::CameraUpdate(window);

	}

	vkDeviceWaitIdle(vk_Device.device);
}

void VK_Window::drawFrame() {
	vkWaitForFences(vk_Device.device, 1, &vk_SwapChain.inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(vk_Device.device, vk_SwapChain.swapChain, std::numeric_limits<uint64_t>::max(), vk_SwapChain.imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		vk_SwapChain.RecreateSwapChain(window, vk_Buffer, renderer);
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	vk_Buffer.UpdateUniformBuffers(imageIndex);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { vk_SwapChain.imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &vk_Buffer.commandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { vk_SwapChain.renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(vk_Device.device, 1, &vk_SwapChain.inFlightFences[currentFrame]);

	if (vkQueueSubmit(vk_Device.graphicsQueue, 1, &submitInfo, vk_SwapChain.inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { vk_SwapChain.swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(vk_Device.presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		vk_SwapChain.RecreateSwapChain(window, vk_Buffer, renderer);
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	currentFrame = (currentFrame + 1) % vk_SwapChain.MAX_FRAMES_IN_FLIGHT;
}

void VK_Window::cleanup() {
	vk_SwapChain.CleanupSwapChain(renderer);

	vkDestroyDescriptorPool(vk_Device.device, renderer.descriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(vk_Device.device, renderer.descriptorSetLayout, nullptr);


	vk_Buffer.CleanUpBuffers();

	for (size_t i = 0; i < vk_SwapChain.MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(vk_Device.device, vk_SwapChain.renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(vk_Device.device, vk_SwapChain.imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(vk_Device.device, vk_SwapChain.inFlightFences[i], nullptr);
	}

	vkDestroyCommandPool(vk_Device.device, renderer.commandPool, nullptr);

	vkDestroyDevice(vk_Device.device, nullptr);

	if (enableValidationLayers) {
		vk_Device.DestroyDebugUtilsMessengerEXT(vk_Device.instance, vk_Device.callback, nullptr);
	}

	vkDestroySurfaceKHR(vk_Device.instance, vk_Device.surface, nullptr);
	vkDestroyInstance(vk_Device.instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}

void VK_Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app = reinterpret_cast<VK_Window*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}