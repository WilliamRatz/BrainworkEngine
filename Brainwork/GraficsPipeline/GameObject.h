#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Objects.h"
#include "Material.h"
#include "VK_BufferObject.h"

class VK_Renderer;

class GameObject
{
private:
	VK_Renderer*				m_renderer;
	VK_BufferObject				m_BufferObject;
	Object						m_object;
	Material					m_material;
	
	GameObject*					m_parentObject = NULL;
	std::vector<GameObject>		m_children;

	Matrix<float, 4, 4>			globalMatrix;
	Matrix<float, 4, 4>			recalculateMatrix();
public:
	GameObject					(VK_Renderer& renderer);
	GameObject					(const GameObject& gameObject);
	~GameObject					();

	void UpdateGameObject		(uint32_t currentImage);


	VK_BufferObject		GetBufferObject		();
	VK_BufferObject&	GetBufferObjectRef	();
	
	void				SetObject			(const Object object);
	Object				GetObject			();
	Object&				GetObjectRef		();
	
	void				SetMaterial			();
	void				SetMaterial			(const Material material);
	Material			GetMaterial			();
	Material&			GetMaterialRef		();

	void CreateBuffer			();
	void CreateDescriptorSets	();


	Matrix<float, 4, 4>			localMatrix;
	Matrix<float, 4, 4>			getGlobalMatrix();

	void setParent				(GameObject* parentObject);
	void addChild				(GameObject& childObject);
	void addChildren			(std::vector<GameObject>& childrenObject);

	GameObject*					getParent();
	GameObject&					getChild(uint16_t index);
	std::vector<GameObject>&	getChildren();

	void CleanupGameObject();
};



#endif // !GAMEOBJECT_H
