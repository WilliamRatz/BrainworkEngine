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

void VK_GameObjectManager::CreateBufferObjects()
{
	int u = 0;

	for (int i = 0; i < 1; ++i)
	{
		for (int ii = 0; ii < 1; ++ii)
		{
			GameObject temp(m_pRenderer);
			if (u % 2 == 0) {
				temp.SetObject(Sphere());
			}
			else {

				temp.SetObject(Capsule());
			}

			temp.GetMaterialRef().SetTexture(Texture("textures/brain.png"));
			temp.GetTransform().getLocalMatrixRef().translate3D(1.2*i, 1.2*ii, 0);
			//gameObjects[u].localMatrix.scale3D(10.0f, 10.0f, 10.0f);
			temp.CreateBuffer();
			this->AddGameObject(temp);
			++u;
		}
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

void VK_GameObjectManager::CleanUpBuffers()
{
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i].CleanupGameObject();
	}
}

