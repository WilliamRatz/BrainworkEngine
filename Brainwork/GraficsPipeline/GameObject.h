#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Objects.h"
#include "Material.h"


#include "Lighting.h"
#include "Transform.h"

class VK_Renderer;
class PointLight;

class GameObject
{
private:
	VK_Renderer*		m_pRenderer;
	Object				m_object;
	Transform			m_transform;
	Material			m_material;
	Lighting			m_lighting;

public:
	GameObject					(VK_Renderer& renderer);
	GameObject					(const GameObject& gameObject);
	~GameObject					();

	void UpdateGameObject		(uint32_t currentImage);
	void CreateBuffer			();
	void CreateDescriptorSets	();

	void				SetObject			(const Object object);
	Object				GetObject			();
	Object&				GetObjectRef		();
	
	void				SetTransform		(const Transform material);
	Transform			GetTransform		();
	Transform&			GetTransformRef		();
	
	void				SetMaterial			(const Material material);
	Material			GetMaterial			();
	Material&			GetMaterialRef		();

	void				SetLighting			(const Lighting material);
	Lighting			GetLighting			();
	Lighting&			GetLightingRef		();

	void CleanupGameObject();
};



#endif // !GAMEOBJECT_H
