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
	//FirstBox
	{
		//Plane back
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Plane.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(-8, 0, 4);
		temp.GetTransformRef().getLocalMatrixRef().scale3D(15, 15, 0);
		temp.GetTransformRef().getLocalMatrixRef().rotation3DAroundX(-90);
		temp.GetTransformRef().getMobility() = Mobility::m_static;
		temp.GetMaterialRef().SetColor(Vector3(1.0f, 1.0f, 1.0f));
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}



	{
		//Cube
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Dodecahedron.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/Dodecahedron.jpg"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(-8.0f, 0, 0);
		temp.GetTransformRef().getLocalMatrixRef().scale3D(4, 4, 4);
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}
	//{
	//	//Sphere
	//	GameObject temp(m_pRenderer);
	//	temp.GetObjectRef().SetMesh("models/Sphere.obj");
	//	temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
	//	temp.GetTransformRef().getLocalMatrixRef().translate3D(-8, 0, 0);
	//	temp.GetTransformRef().getLocalMatrixRef().scale3D(2, 2, 2);
	//	temp.GetTransformRef().getMobility() = Mobility::m_static;
	//	temp.GetMaterialRef().SetColor(Vector3(0.0f, 0.6f, 0.0f));
	//	temp.CreateBuffer();
	//	this->AddGameObject(temp);
	//}
	//{
	//	//Capsule
	//	GameObject temp(m_pRenderer);
	//	temp.GetObjectRef().SetMesh("models/Capsule.obj");
	//	temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
	//	temp.GetTransformRef().getLocalMatrixRef().translate3D(-5.4, 0, 0);
	//	temp.GetTransformRef().getLocalMatrixRef().scale3D(2, 2, 2);
	//	temp.GetTransformRef().getMobility() = Mobility::m_static;
	//	temp.GetMaterialRef().SetColor(Vector3(0.0f, 0.0f, 0.6f));
	//	temp.CreateBuffer();
	//	this->AddGameObject(temp);
	//}


	{
		//Plane
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Plane.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(8, 0, 4);
		temp.GetTransformRef().getLocalMatrixRef().scale3D(15, 15, 0);
		temp.GetTransformRef().getLocalMatrixRef().rotation3DAroundX(-90);
		temp.GetTransformRef().getMobility() = Mobility::m_static;
		temp.GetMaterialRef().SetColor(Vector3(1.0f, 1.0f, 1.0f));
		temp.CreateBuffer();
		this->AddGameObject(temp);
	}
	{
		//Brain
		GameObject temp(m_pRenderer);
		temp.GetObjectRef().SetMesh("models/Brain.obj");
		temp.GetMaterialRef().SetTexture(Texture("textures/emptyTexture.png"));
		temp.GetTransformRef().getLocalMatrixRef().translate3D(8, -1, 0);
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

