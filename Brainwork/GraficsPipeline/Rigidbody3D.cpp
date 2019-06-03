#include "Rigidbody3D.h"
#include "Transform.h"



Rigidbody3D::Rigidbody3D(Transform& p_transform)
{
	m_componentID = 1;
	m_position = &p_transform.getGlobalMatrix();
}

Rigidbody3D::~Rigidbody3D()
{
}

Vector3& Rigidbody3D::GetVelocity()
{
	return m_velocity;
}

double& Rigidbody3D::GetAcceleration()
{
	return m_acceleration;
}
