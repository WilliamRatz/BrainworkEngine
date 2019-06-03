#include "GameObject.h"
#include "VK_Renderer.h"
#include "VK_Device.h"
#include "Camera.h"
#include "PointLight.h"
#include <typeinfo>


GameObject::GameObject(VK_Renderer* p_renderer)
{
	m_pRenderer = p_renderer;
	m_object.GetVK_BufferObjectRef().SetRenderer(m_pRenderer);
}


GameObject::GameObject(const GameObject& p_gameObject)
{
	m_pRenderer = p_gameObject.m_pRenderer;

	SetObject(p_gameObject.m_object);
	SetMaterial(p_gameObject.m_material);
	SetTransform(p_gameObject.m_transform);
}
GameObject::~GameObject()
{
}

void GameObject::UpdateGameObject(uint32_t currentImage) {

	if (m_transform.getMobility() == Mobility::m_moveable)
	{
		m_transform.getLocalMatrixRef().rotation3DAroundYlocal(0.05f);
	}

	m_object.GetUniformBufferObjectRef().lightsCount = ((m_lighting.GetPointLightRef().size() > 16) ? 16 : m_lighting.GetPointLightRef().size());
	for (size_t i = 0; i < m_object.GetUniformBufferObjectRef().lightsCount; ++i)
	{
		m_object.GetUniformBufferObjectRef().lightView[i] = m_lighting.GetPointLightRef()[i]->GetLightInfoObjectRef().lightView;
	}

	m_object.GetUniformBufferObjectRef().model = m_transform.getGlobalMatrix();
	m_object.GetUniformBufferObjectRef().view = Camera::ViewCamera.GetCameraMatrix();
	m_object.GetUniformBufferObjectRef().proj.perspectivProjection((WIDTH < HEIGHT) ? (float)WIDTH / (float)HEIGHT : 1, (HEIGHT < WIDTH) ? (float)HEIGHT / (float)WIDTH : 1, 1, 60);
	m_object.GetUniformBufferObjectRef().proj[1][1] *= -1;
	m_object.GetUniformBufferObjectRef().groundColor = Vector4(m_material.GetColorRef().x(), m_material.GetColorRef().y(), m_material.GetColorRef().z(), 1.0);

	m_object.GetVK_BufferObjectRef().UpdateUniformBuffer(m_object.GetUniformBufferObjectRef(), currentImage);
}
void GameObject::CreateBuffer()
{
	m_material.GetTextureRef().CreateTexture(m_pRenderer);

	m_object.CreateBuffer(m_pRenderer);
}
void GameObject::CreateDescriptorSets()
{
	m_object.GetVK_BufferObjectRef().CreateUniformBuffers(m_lighting);
	m_object.GetVK_BufferObjectRef().CreateDescriptorSet(m_material, m_lighting);
}


void GameObject::SetObject(const Object p_object)
{
	m_object = p_object;
}
Object GameObject::GetObject()
{
	return m_object;
}
Object& GameObject::GetObjectRef()
{
	return m_object;
}

void GameObject::SetTransform(const Transform p_transform)
{
	m_transform = p_transform;
}
Transform GameObject::GetTransform()
{
	return m_transform;
}
Transform& GameObject::GetTransformRef()
{
	return m_transform;
}

void GameObject::SetMaterial(const Material p_material)
{
	m_material = p_material;
}
Material GameObject::GetMaterial()
{
	return m_material;
}
Material& GameObject::GetMaterialRef()
{
	return m_material;
}

void GameObject::SetLighting(const Lighting p_lighting)
{
	m_lighting = p_lighting;
}
Lighting GameObject::GetLighting()
{
	return m_lighting;
}
Lighting& GameObject::GetLightingRef()
{
	return m_lighting;
}


void GameObject::CleanupGameObject()
{
	m_object.CleanUpObject();
	m_material.CleanUpMaterial();
	m_transform.CleanUpTransform();
	m_lighting.CleanUpLighting();
}