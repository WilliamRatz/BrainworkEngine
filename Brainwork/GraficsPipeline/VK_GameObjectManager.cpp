#include "VK_GameObjectManager.h"
#include "VK_Renderer.h"
#include "VK_Device.h"
#include "VK_SwapChain.h"
#include "VK_GraphicsPipeline.h"
#include "GameObject.h"
#include "Texture.h"
#include "Objects.h"
#include "LightManager.h"
#include "PointLight.h"

VK_GameObjectManager::VK_GameObjectManager(VK_Renderer& p_renderer)
{
	m_pRenderer = &p_renderer;
}

void VK_GameObjectManager::UpdateGameObjects(uint32_t currentImage)
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i].UpdateGameObject(currentImage);
	}
}

void VK_GameObjectManager::CreateGameObjects()
{
	{
		//Plane
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Cube.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/brain.png"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(5, 5, 4);
		temp.GetTransformRef().getLocalMatrixRef().scale3D(16, 16, 0);
		temp.GetTransformRef().getLocalMatrixRef().rotation3DAroundZ(180);
		temp.GetMaterialRef().SetColor(Vector3(1.0f, 1.0f, 1.0f));
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}

	{
		//Cube
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Cube.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
		temp.GetMaterialRef().SetColor(Vector3(0.6f, 0.0f, 0.0f));
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}
	{
		//Sphere
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Sphere.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(2, 0, 0);
		temp.GetMaterialRef().SetColor(Vector3(0.0f, 0.6f, 0.0f));
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}
	{
		//Capsule
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Capsule.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(4, 0, 0);
		temp.GetMaterialRef().SetColor(Vector3(0.0f, 0.0f, 0.6f));
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}
	{
		//Brain
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Brain.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(10, 0, 0);
		temp.GetTransformRef().getLocalMatrixRef().scale3D(0.1f, 0.1f, 0.1f);
		temp.GetMaterialRef().SetColor(Vector3(0.8f, 0.6f, 0.6f));
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}
}
void VK_GameObjectManager::AddGameObject(GameObject& p_gameObject)
{
	m_gameObjects.push_back(p_gameObject);
}
void VK_GameObjectManager::CreateDescriptorSets()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i].CreateDescriptorSets();
	}
}
std::vector<GameObject> VK_GameObjectManager::GetGameObjects()
{
	return m_gameObjects;
}
std::vector<GameObject>& VK_GameObjectManager::GetGameObjectsRef()
{
	return m_gameObjects;
}

void VK_GameObjectManager::CleanUp()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i].CleanupGameObject();
	}
}

