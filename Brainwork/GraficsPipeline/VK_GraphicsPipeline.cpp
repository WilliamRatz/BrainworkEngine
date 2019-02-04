#include "VK_GraphicsPipeline.h"
#include "VK_Renderer.h"
#include "VK_SwapChain.h"
#include "VK_Device.h"
#include "Objects.h"
#include "VK_GameObjectManager.h"
#include "GameObject.h"
#include "LightManager.h"


VK_GraphicsPipeline::VK_GraphicsPipeline(VK_Renderer& p_vk_renderer)
{
	m_pRenderer = &p_vk_renderer;
	m_pSwapChain = m_pRenderer->m_pSwapChain;
	m_pDevice = m_pRenderer->m_pDevice;
}
VK_GraphicsPipeline::VK_GraphicsPipeline(const VK_GraphicsPipeline& vk_graphicsPipeline)
{
	m_pRenderer = vk_graphicsPipeline.m_pRenderer;
	m_pSwapChain = vk_graphicsPipeline.m_pSwapChain;
	m_pDevice = vk_graphicsPipeline.m_pDevice;
}
VK_GraphicsPipeline::~VK_GraphicsPipeline()
{
}

void VK_GraphicsPipeline::CreateGraphicsPipeline(std::string p_vertexShader, std::string p_fragmentShader, unsigned int p_uboBindings, unsigned int p_imageSamplerBindings)
{
	std::vector<char> vertShaderCode = ReadFile("shaders/" + p_vertexShader + ".spv");
	std::vector<char> fragShaderCode = ReadFile("shaders/" + p_fragmentShader + ".spv");

	VkShaderModule vertShaderModule = CreateShaderModule(vertShaderCode);
	VkShaderModule fragShaderModule = CreateShaderModule(fragShaderCode);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;


	VkVertexInputBindingDescription bindingDescription = Vertex::getBindingDescriptionVertexAll();
	std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = Vertex::getAttributeDescriptionsVertexAll();
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	/*
	VkVertexInputBindingDescription bindingDescription;
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions;

	if (m_pRenderer->GetRendererCreatInfoRef().colorAttachment)
	{
		bindingDescription = Vertex::getBindingDescriptionVertexAll();
		attributeDescriptions.push_back(Vertex::getAttributeDescriptionsVertexAll()[0]);
		attributeDescriptions.push_back(Vertex::getAttributeDescriptionsVertexAll()[1]);
		attributeDescriptions.push_back(Vertex::getAttributeDescriptionsVertexAll()[2]);
	}
	else
	{
		bindingDescription = Vertex::getBindingDescriptionVertexPos();
		attributeDescriptions.push_back(Vertex::getAttributeDescriptionsVertexAll()[0]);
	}
	*/
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());

	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)m_pSwapChain->m_swapChainExtent.width;
	viewport.height = (float)m_pSwapChain->m_swapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = m_pSwapChain->m_swapChainExtent;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineDepthStencilStateCreateInfo depthStencil = {};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.stencilTestEnable = VK_FALSE;

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &m_pRenderer->GetDescriptorSetLayoutRef();


	m_pRenderer->CreateDescriptorSetLayouts(p_uboBindings, p_imageSamplerBindings);

	if (vkCreatePipelineLayout(m_pDevice->device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = m_pRenderer->GetRenderPassRef();
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	if (vkCreateGraphicsPipelines(m_pDevice->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}

	vkDestroyShaderModule(m_pDevice->device, fragShaderModule, nullptr);
	vkDestroyShaderModule(m_pDevice->device, vertShaderModule, nullptr);

	m_pRenderer->CreateCommandPool();
	m_pRenderer->CreateDescriptorPools(p_uboBindings, p_imageSamplerBindings);

}

void VK_GraphicsPipeline::RecreateGraphicsPipeline(GLFWwindow * window)
{
	int width = 0, height = 0;
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(m_pSwapChain->m_pDevice->device);


	m_pSwapChain->CreateSwapChain(window);
	m_pSwapChain->CreateImageViews();
	m_pRenderer->CreateRenderPass();
	//CreateGraphicsPipeline("TexturedVert", "TexturedFrag");
	m_pSwapChain->CreateDepthResources(*m_pRenderer);
	//vk_renderer->CreateFramebuffers();
	//vk_bufferManager->CreateCommandBuffers(*this);
}


VkShaderModule VK_GraphicsPipeline::CreateShaderModule(const std::vector<char>& code)
{

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(m_pSwapChain->m_pDevice->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}

	return shaderModule;

}
void VK_GraphicsPipeline::CleanUp()
{
	vkDestroyPipeline(m_pDevice->device, m_graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(m_pDevice->device, m_pipelineLayout, nullptr);
}
std::vector<char> VK_GraphicsPipeline::ReadFile(const std::string & filename)
{

	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;

}
