#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Objects.h"
#include "Texture.h"


class GameObject
{
private:
	std::vector<Vertex>			m_vertices;
	std::vector<uint16_t>		m_indices;
	
	GameObject*					m_parentObject = NULL;
	std::vector<GameObject>		m_children;
	Matrix<float, 4, 4>			globalMatrix;
public:
	GameObject					(std::vector<Vertex>& vertices, std::vector<uint16_t>& indices);
	GameObject					(const GameObject& gameObject);
	~GameObject					();

	Matrix<float, 4, 4>			localMatrix;

	Matrix<float, 4, 4>			recalculateMatrix();
	Matrix<float, 4, 4>			getGlobalMatrix();

	void setParent				(GameObject* parentObject);
	void addChild				(GameObject& childObject);
	void addChildren			(std::vector<GameObject>& childrenObject);

	std::vector<Vertex>			getVertices();
	std::vector<uint16_t>		getIndices();
	GameObject*					getParent();
	GameObject&					getChild(uint16_t index);
	std::vector<GameObject>&	getChildren();
};



#endif // !GAMEOBJECT_H
