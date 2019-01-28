#include "VK_Window.h"
#include "LightManager.h"
#include "PointLight.h"

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

	window = glfwCreateWindow(WIDTH, HEIGHT, "Brainwork", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	cam.SetCameraToWindow(window);
}

void VK_Window::initVulkan() {
	vk_device.CreateInstance();
	vk_device.SetupDebugCallback();
	vk_device.CreateSurface(window);
	vk_device.PickPhysicalDevice(vk_swapChain);
	vk_device.CreateLogicalDevice();
	
	vk_swapChain.CreateSwapChain(window);
	vk_swapChain.CreateImageViews();
	
	vk_renderers[0].CreateRenderPass();
	vk_renderers[1].CreateRenderPass();

	vk_graphicsPipelines[0].CreateGraphicsPipeline("vert", "frag", 1, 2);
	vk_graphicsPipelines[1].CreateGraphicsPipeline("LightVert", "LightFrag", 1, 0);


	this->initObjects();
	
}

void VK_Window::initObjects()
{
	vk_lightManager.AddLight(PointLight(vk_renderers[1]));
	vk_lightManager.CalculateLightMaps();

	vk_swapChain.CreateDepthResources(vk_renderers[0]);
	vk_renderers[0].CreateFramebuffers(vk_swapChain.swapChainFramebuffers, vk_swapChain.swapChainImageViews, vk_swapChain.depthImageView);
	vk_lightManager.CreateFrameBuffer();
	vk_gameObjectManager.CreateBufferObjects();
	vk_lightManager.CheckForObjectsInFurustum(vk_gameObjectManager.GetGameObjectsRef());
	vk_lightManager.CreateLightBuffer(vk_gameObjectManager.GetGameObjectsRef().size());
	vk_lightManager.CreateDescriptorSets();
	vk_renderers[1].CreateCommandBuffers(vk_graphicsPipelines[1], vk_lightManager);


	vk_gameObjectManager.CreateDescriptorSets();
	vk_renderers[0].CreateCommandBuffers(vk_graphicsPipelines[0], vk_gameObjectManager);

	vk_swapChain.CreateSyncObjects();
}

void VK_Window::mainLoop() {

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawFrame();
		Camera::CameraUpdate(window);
	}

	vkDeviceWaitIdle(vk_device.device);
}

void VK_Window::drawFrame() {
	vkWaitForFences(vk_device.device, 1, &vk_swapChain.inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(vk_device.device, vk_swapChain.swapChain, std::numeric_limits<uint64_t>::max(), vk_swapChain.imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		vk_graphicsPipelines[0].RecreateSwapChain(window, &vk_gameObjectManager);
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	vk_lightManager.UpdateLightInfos(imageIndex, &vk_gameObjectManager.GetGameObjectsRef()[0]);
	vk_gameObjectManager.UpdateGameObjects(imageIndex);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { vk_swapChain.imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 2;
	submitInfo.pCommandBuffers = &vk_renderers[0].commandBuffers[imageIndex];
	submitInfo.pCommandBuffers = &vk_renderers[1].commandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { vk_swapChain.renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(vk_device.device, 1, &vk_swapChain.inFlightFences[currentFrame]);

	if (vkQueueSubmit(vk_device.graphicsQueue, 1, &submitInfo, vk_swapChain.inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { vk_swapChain.swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(vk_device.presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		vk_graphicsPipelines[0].RecreateSwapChain(window, &vk_gameObjectManager);
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	currentFrame = (currentFrame + 1) % vk_swapChain.MAX_FRAMES_IN_FLIGHT;
}

void VK_Window::cleanup() {
	vk_graphicsPipelines[0].CleanupSwapChain(&vk_gameObjectManager);
	vkDestroyDescriptorPool(vk_device.device, vk_renderers[0].m_descriptorPool, nullptr);
	vkDestroyDescriptorPool(vk_device.device, vk_renderers[1].m_descriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(vk_device.device, vk_renderers[0].m_descriptorSetLayout, nullptr);
	vkDestroyDescriptorSetLayout(vk_device.device, vk_renderers[1].m_descriptorSetLayout, nullptr);

	for (size_t i = 0; i < vk_swapChain.MAX_FRAMES_IN_FLIGHT; ++i) {
		vkDestroySemaphore(vk_device.device, vk_swapChain.renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(vk_device.device, vk_swapChain.imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(vk_device.device, vk_swapChain.inFlightFences[i], nullptr);
	}

	vkFreeCommandBuffers(vk_device.device, vk_renderers[0].commandPool, static_cast<uint32_t>(vk_renderers[0].commandBuffers.size()), vk_renderers[0].commandBuffers.data());
	vkFreeCommandBuffers(vk_device.device, vk_renderers[1].commandPool, static_cast<uint32_t>(vk_renderers[0].commandBuffers.size()), vk_renderers[0].commandBuffers.data());


	vkDestroyCommandPool(vk_device.device, vk_renderers[0].commandPool, nullptr);
	vkDestroyCommandPool(vk_device.device, vk_renderers[1].commandPool, nullptr);


	vkDestroyDevice(vk_device.device, nullptr);

	if (enableValidationLayers) {
		vk_device.DestroyDebugUtilsMessengerEXT(vk_device.instance, vk_device.callback, nullptr);
	}

	vkDestroySurfaceKHR(vk_device.instance, vk_device.surface, nullptr);
	vkDestroyInstance(vk_device.instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}

void VK_Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app = reinterpret_cast<VK_Window*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}