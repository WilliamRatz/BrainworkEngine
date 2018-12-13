#include "GameObject.h"


#pragma region GameObject


GameObject::GameObject(Matrix<float, 4, 4>& p_model, std::vector<Vertex>& p_vertices, std::vector<uint16_t>& p_indices)
{
	m_matrix = p_model;
	m_vertices = p_vertices;
	m_indices = p_indices;
}

//GameObject::GameObject(const Cube& p_cube)
//{
//	m_matrix = p_cube.m_model;
//	m_vertices = p_cube.m_vertices;
//	m_indices = p_cube.m_indices;
//}
//
//GameObject::GameObject(const Plane & p_plane)
//{
//	m_matrix = p_plane.m_model;
//	m_vertices = p_plane.m_vertices;
//	m_indices = p_plane.m_indices;
//}

GameObject::GameObject(const GameObject& p_gameObject)
{
	m_matrix = p_gameObject.m_matrix;
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
		m_matrix *= parent->m_matrix;
		parent = parent->m_parentObject;
	}

	for (GameObject& child : m_children)
	{
		child.recalculateMatrix();
	}

	return m_matrix;
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

#pragma region Cube
Cube::Cube()
{
}
Cube::Cube(const Matrix<float, 4, 4>& p_defaultValue)
{

	m_model = p_defaultValue;
}


Cube::operator GameObject()
{
	return GameObject(m_model, m_vertices, m_indices);
}

#pragma endregion

#pragma region Plane
Plane::Plane()
{
}

Plane::Plane(const Matrix<float, 4, 4>& p_defaultValue)
{
	m_model = p_defaultValue;
}

Plane::operator GameObject()
{
	return GameObject(m_model, m_vertices, m_indices);
}

#pragma endregion
