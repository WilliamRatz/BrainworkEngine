#include "VK_Window.h"
#include "LightManager.h"
#include "PointLight.h"

VK_Window::VK_Window()
{
}

void VK_Window::run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
	Cleanup();
}

void VK_Window::InitWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Brainwork", nullptr, nullptr);
	glfwSetWindowUserPointer(m_pWindow, this);
	glfwSetFramebufferSizeCallback(m_pWindow, FramebufferResizeCallback);

	m_cam.SetCameraToWindow(m_pWindow);
}

void VK_Window::InitVulkan() {
	m_device.CreateInstance();
	m_device.SetupDebugCallback();
	m_device.CreateSurface(m_pWindow);
	m_device.PickPhysicalDevice(m_swapChain);
	m_device.CreateLogicalDevice();

	m_swapChain.CreateSwapChain(m_pWindow);
	m_swapChain.CreateImageViews();

	m_renderers[0].CreateRenderPass();
	m_renderers[1].CreateRenderPass();

	m_graphicsPipelines[0].CreateGraphicsPipeline("vert", "frag", 1, 2);
	m_graphicsPipelines[1].CreateGraphicsPipeline("LightVert", "LightFrag", 1, 0);


	this->InitObjects();

}

void VK_Window::InitObjects()
{
	{
		PointLight pl(m_renderers[1]);
		pl.GetLightInfoObjectRef().lightView.translate3D(-1.8f, 0, 6.0f);
		pl.GetLightInfoObjectRef().lightView = pl.GetLightInfoObjectRef().lightView.transpose();
		m_lightManager.AddLight(pl);
	}

	//{
	//	PointLight pl(m_renderers[1]);
	//	pl.GetLightInfoObjectRef().lightView.translate3D(-8.0f, 0, 10.0f);
	//	pl.GetLightInfoObjectRef().lightView = pl.GetLightInfoObjectRef().lightView.transpose();
	//	m_lightManager.AddLight(pl);
	//}

	m_lightManager.CalculateLightMaps();

	m_swapChain.CreateDepthResources(m_renderers[0]);
	m_renderers[0].CreateFramebuffers(m_swapChain.m_swapChainFramebuffers, m_swapChain.m_swapChainImageViews, m_swapChain.m_depthImageView);
	m_lightManager.CreateFrameBuffer();

	for (unsigned int i = 0; i < m_gameObjectManager.size(); ++i)
	{
		m_gameObjectManager[i].CreateGameObjects();
	}

	m_lightManager.CheckForObjectsInFurustum(m_gameObjectManager[0].GetGameObjectsRef());
	m_lightManager.CreateLightBuffer();
	m_lightManager.CreateDescriptorSets();
	m_renderers[1].CreateCommandBuffers(m_graphicsPipelines[1], m_lightManager);

	for (unsigned int i = 0; i < m_gameObjectManager.size(); ++i)
	{
		m_gameObjectManager[i].CreateDescriptorSets();
		m_renderers[0].CreateCommandBuffers(m_graphicsPipelines[0], m_gameObjectManager[i]);
	}

	m_swapChain.CreateSyncObjects();
}

void VK_Window::MainLoop() {

	while (!glfwWindowShouldClose(m_pWindow)) {
		glfwPollEvents();
		NextFrame();

		Camera::CameraUpdate(m_pWindow);
	}

	vkDeviceWaitIdle(m_device.device);
}

void VK_Window::NextFrame() {
	vkWaitForFences(m_device.device, 1, &m_swapChain.m_inFlightFences[m_currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_device.device, m_swapChain.m_swapChain, std::numeric_limits<uint64_t>::max(), m_swapChain.m_imageAvailableSemaphores[m_currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		m_graphicsPipelines[0].RecreateGraphicsPipeline(m_pWindow);
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	for (unsigned int i = 0; i < m_gameObjectManager.size(); ++i)
	{
		m_gameObjectManager[i].UpdateGameObjects(imageIndex);
	}

	m_lightManager.UpdateLightInfos(imageIndex);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { m_swapChain.m_imageAvailableSemaphores[m_currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	VkCommandBuffer cmdBuffers[] = {
		m_renderers[1].GetCommandBuffersRef()[imageIndex],
		m_renderers[0].GetCommandBuffersRef()[imageIndex]
	};

	submitInfo.commandBufferCount = sizeof(cmdBuffers) / sizeof(cmdBuffers[0]);
	submitInfo.pCommandBuffers = cmdBuffers;

	VkSemaphore signalSemaphores[] = { m_swapChain.m_renderFinishedSemaphores[m_currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(m_device.device, 1, &m_swapChain.m_inFlightFences[m_currentFrame]);

	if (vkQueueSubmit(m_device.graphicsQueue, 1, &submitInfo, m_swapChain.m_inFlightFences[m_currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { m_swapChain.m_swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(m_device.presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_framebufferResized) {
		m_framebufferResized = false;
		m_graphicsPipelines[0].RecreateGraphicsPipeline(m_pWindow);
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	m_currentFrame = (m_currentFrame + 1) % m_swapChain.MAX_FRAMES_IN_FLIGHT;
}

void VK_Window::Cleanup() {

	for (unsigned int i = 0; i < m_renderers.size(); ++i)
	{
		m_renderers[i].CleanUp();
	}

	for (unsigned int i = 0; i < m_graphicsPipelines.size(); ++i)
	{
		m_graphicsPipelines[i].CleanUp();
	}

	m_swapChain.CleanUp();

	for (unsigned int i = 0; i < m_gameObjectManager.size(); ++i)
	{
		m_gameObjectManager[i].CleanUp();
	}

	m_lightManager.CleanUp();

	for (size_t i = 0; i < m_swapChain.MAX_FRAMES_IN_FLIGHT; ++i) {
		vkDestroySemaphore(m_device.device, m_swapChain.m_renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(m_device.device, m_swapChain.m_imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(m_device.device, m_swapChain.m_inFlightFences[i], nullptr);
	}
	m_device.CleanUp();

	glfwDestroyWindow(m_pWindow);

	glfwTerminate();
}

void VK_Window::FramebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app = reinterpret_cast<VK_Window*>(glfwGetWindowUserPointer(window));
	app->m_framebufferResized = true;
}