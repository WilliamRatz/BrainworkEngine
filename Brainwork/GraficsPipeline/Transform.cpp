#include "Transform.h"
#include "GameObject.h"


Transform::Transform()
{
}

Transform::Transform(const Transform& p_transform)
{
	m_globalMatrix = p_transform.m_globalMatrix;
	m_localMatrix = p_transform.m_localMatrix;
	m_pParentObject = p_transform.m_pParentObject;
	m_children = p_transform.m_children;
}

Transform::~Transform()
{
}

Matrix<float, 4, 4>	Transform::getGlobalMatrix()
{
	return (m_globalMatrix * m_localMatrix).transpose();
}
Matrix<float, 4, 4>	Transform::getLocalMatrix()
{
	return m_localMatrix;
}
Matrix<float, 4, 4>& Transform::getLocalMatrixRef()
{
	return m_localMatrix;
}

void Transform::CleanUpTransform()
{

}