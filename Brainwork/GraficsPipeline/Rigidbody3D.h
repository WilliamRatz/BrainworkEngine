#pragma once
#include "Component.h"
#include "VK_inc.h"


class Transform;

class Rigidbody3D : public Component
{
private:
	Vector3 m_velocity = Vector3::Zero();
	Matrix<float, 4, 4>* m_position;
	double m_acceleration = 0;

public:
	Rigidbody3D(Transform& transform);
	~Rigidbody3D();


	Vector3& GetVelocity();
	double& GetAcceleration();
};

