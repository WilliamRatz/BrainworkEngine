#include "GameObject.h"
#include "VK_Renderer.h"
#include "VK_Device.h"
#include "Camera.h"


GameObject::GameObject(VK_Renderer& p_renderer)
{
	m_renderer = &p_renderer;

	m_BufferObject.SetRenderer(m_renderer);


}

GameObject::GameObject(const GameObject& p_gameObject)
{
	globalMatrix = p_gameObject.globalMatrix;
	localMatrix = p_gameObject.localMatrix;
	m_parentObject = p_gameObject.m_parentObject;
	m_children = p_gameObject.m_children;

	m_renderer = p_gameObject.m_renderer;
	m_object = p_gameObject.m_object;
	m_BufferObject = p_gameObject.m_BufferObject;
	m_material = p_gameObject.m_material;
}

GameObject::~GameObject()
{
}


void GameObject::updateGameObject(uint32_t currentImage) {
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	UniformBufferObject ubo = {};


	//gameObject.localMatrix.rotation3DAroundZlocal(0.1f)/*.rotation3DAroundYlocal(0.15f).rotation3DAroundXlocal(0.05f)*/;


	ubo.model = this->getGlobalMatrix();
	ubo.view = Camera::getViewCamera.mat;
	ubo.proj.perspectivProjection((WIDTH < HEIGHT) ? (float)WIDTH / (float)HEIGHT : 1, (HEIGHT < WIDTH) ? (float)HEIGHT / (float)WIDTH : 1, 1, 60);
	ubo.proj[1][1] *= -1;

	m_BufferObject.UpdateUniformBuffer(ubo, currentImage);
}

void GameObject::SetObject(const Object p_object)
{
	m_object = p_object;
}

void GameObject::SetMaterial(Material p_material)
{
	m_material = p_material;

	for (int i = 0; i < m_object.GetVertices().size(); ++i) 
	{
		m_object.GetVerticesRef()[i].ColorChange(m_material.GetColorRef());
	}
}

VK_BufferObject GameObject::GetBufferObject()
{
	return m_BufferObject;
}

Object GameObject::GetObject()
{
	return m_object;
}

Material GameObject::GetMaterial()
{
	return m_material;
}

void GameObject::CreateBuffer()
{
	m_BufferObject.CreateVertexBuffer(m_object.GetVertices());
	m_BufferObject.CreateIndexBuffer(m_object.GetIndices());
	m_BufferObject.CreateUniformBuffers();
}

void GameObject::CreateDescriptorSets()
{
	m_BufferObject.CreateDescriptorSet(m_material);
}


Matrix<float, 4, 4> GameObject::recalculateMatrix()
{
	GameObject* parent = m_parentObject;

	while (parent != NULL)
	{
		globalMatrix *= parent->globalMatrix;
		parent = parent->m_parentObject;
	}

	for (GameObject& child : m_children)
	{
		child.recalculateMatrix();
	}

	return globalMatrix;
}

Matrix<float, 4, 4> GameObject::getGlobalMatrix()
{
	return (localMatrix * globalMatrix).transpose();
}

void GameObject::setParent(GameObject* p_parentObject)
{
	m_parentObject = p_parentObject;
	p_parentObject->addChild(*this);
	this->recalculateMatrix();
}

void GameObject::addChild(GameObject& p_childObject)
{
	p_childObject.setParent(this);
	p_childObject.recalculateMatrix();
	m_children.push_back(p_childObject);
}

void GameObject::addChildren(std::vector<GameObject>& p_childrenObject)
{
	for (GameObject& child : p_childrenObject)
	{
		child.setParent(this);
		child.recalculateMatrix();
		m_children.push_back(child);
	}
}


GameObject* GameObject::getParent()
{
	return m_parentObject;
}

GameObject& GameObject::getChild(uint16_t p_index)
{
	return  m_children[p_index];
}

std::vector<GameObject>& GameObject::getChildren()
{
	return  m_children;
}

void GameObject::CleanupGameObject()
{
	this->GetBufferObject().CleanupBufferObject();
}

