#include "Transform.h"
#include "GameObject.h"


void Transform::recalculateMatrix()
{
	if (m_pParentTransform != nullptr)
	{
		m_dependencieMatrix = (m_pParentTransform->m_dependencieMatrix * m_pParentTransform->m_localMatrix) * m_startDependencieMatrix;
	}

	for (int i = 0; i < m_childrenTransform.size(); ++i)
	{
		m_childrenTransform[i]->recalculateMatrix();
	}
}

Transform::Transform()
{
	
}

Transform::~Transform()
{
	
}

Mobility& Transform::getMobility()
{
	return m_mobility;
}
Transform* Transform::getParent()
{
	return m_pParentTransform;
}
Transform* Transform::getChild(uint16_t p_index)
{
	return m_childrenTransform[p_index];
}
std::vector<Transform*>& Transform::getChildren()
{
	return m_childrenTransform;
}
Matrix<float, 4, 4> Transform::getGlobalMatrix()
{
	return (m_dependencieMatrix * m_localMatrix).transpose();
}
Matrix<float, 4, 4> Transform::getLocalMatrix()
{
	return m_localMatrix;
}

void Transform::setLocalMatrix(Matrix<float, 4, 4> p_localMatrix)
{
	m_localMatrix = p_localMatrix;

	for (int i = 0; i < m_childrenTransform.size(); ++i)
	{
		m_childrenTransform[i]->recalculateMatrix();
	}
}

void Transform::setParent(Transform* p_parentTransform)
{
	m_pParentTransform = p_parentTransform;
	m_startDependencieMatrix = (m_pParentTransform->m_dependencieMatrix * m_pParentTransform->m_localMatrix).inverse();
}

void Transform::removeParent()
{
	m_pParentTransform = nullptr;
}

void Transform::addChild(Transform* p_childTransform)
{
	p_childTransform->setParent(this);
	m_childrenTransform.push_back(p_childTransform);
}

void Transform::addChildren(std::vector<Transform*>& p_childrenTransform)
{
	for (int i = 0; i < p_childrenTransform.size(); ++i)
	{
		m_childrenTransform.push_back(p_childrenTransform[i]);
	}
}

void Transform::CleanUpTransform()
{
}