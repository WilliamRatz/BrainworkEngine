#include "GameObject.h"


#pragma region GameObject


GameObject::GameObject(std::vector<Vertex>& p_vertices, std::vector<uint16_t>& p_indices)
{
	m_vertices = p_vertices;
	m_indices = p_indices;
}

GameObject::GameObject(const GameObject& p_gameObject)
{
	globalMatrix = p_gameObject.globalMatrix;
	localMatrix = p_gameObject.localMatrix;
	m_parentObject = p_gameObject.m_parentObject;
	m_children = p_gameObject.m_children;
	m_vertices = p_gameObject.m_vertices;
	m_indices = p_gameObject.m_indices;
}

GameObject::~GameObject()
{
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

std::vector<Vertex> GameObject::getVertices()
{
	return m_vertices;
}

std::vector<uint16_t> GameObject::getIndices()
{
	return m_indices;
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
#pragma endregion
