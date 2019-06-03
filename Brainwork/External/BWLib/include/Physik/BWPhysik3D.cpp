#include "BWPhysik3D.h"


Vector3 BWPhysik3D::Reflect(Vector3& p_direction, Vector3& p_normal)
{
	return (p_direction - (p_normal * 2 * (Vector3::dot(p_direction, p_normal))));
}

#pragma region UniformMotion
Vector3 BWPhysik3D::UM::GetElapseTime(Vector3& p_distance, Vector3& p_velocity)
{
	return Vector3(p_distance / p_velocity);
}

Vector3 BWPhysik3D::UM::GetPosition(Vector3& p_velocity, double& p_elapsedTime)
{
	return Vector3(p_velocity / p_elapsedTime);
}
Vector3 BWPhysik3D::UM::GetPosition(Vector3& p_velocity, double& p_elapsedTime, Vector3& p_startDistance)
{
	return Vector3((p_velocity / p_elapsedTime) + p_startDistance);
}

Vector3 BWPhysik3D::UM::GetVelocity(Vector3& p_distance, double& p_elapsedTime)
{
	return Vector3(p_distance / p_elapsedTime);
}
#pragma endregion
 
#pragma region Kinematics
Vector3 BWPhysik3D::K::GetElapseTime(Vector3& p_velocity, Vector3& p_acceleration)
{
	return Vector3(p_velocity / p_acceleration);
}
Vector3 BWPhysik3D::K::GetElapseTime(Vector3& p_velocity, Vector3& p_acceleration, Vector3& p_initialVelocity)
{
	return Vector3((p_velocity - p_initialVelocity) / p_acceleration);
}

Vector3 BWPhysik3D::K::GetPosition(Vector3& p_acceleration, double& p_elapsedTime)
{
	return Vector3((p_acceleration / 2) * (p_elapsedTime * p_elapsedTime));
}
Vector3 BWPhysik3D::K::GetPosition(Vector3& p_acceleration, double& p_elapsedTime, Vector3& p_initialVelocity, Vector3& p_startDistance)
{
	return Vector3((p_acceleration / 2) * (p_elapsedTime * p_elapsedTime) + (p_initialVelocity * p_elapsedTime) + p_startDistance);
}

Vector3 BWPhysik3D::K::GetVelocity(Vector3& p_acceleration, double& p_elapsedTime)
{
	return Vector3(p_acceleration * p_elapsedTime);
}
Vector3 BWPhysik3D::K::GetVelocity(Vector3& p_acceleration, double& p_elapsedTime, Vector3& p_initialVelocity)
{
	return Vector3((p_acceleration * p_elapsedTime) + p_initialVelocity);
}

Vector3 BWPhysik3D::K::GetAcceleration(Vector3& p_velocity, double& p_elapsedTime)
{
	return Vector3(p_velocity / p_elapsedTime);
}
Vector3 BWPhysik3D::K::GetAcceleration(Vector3& p_velocity, double& p_elapsedTime, Vector3& p_initialVelocity)
{
	return Vector3((p_velocity - p_initialVelocity) / p_elapsedTime);
}
#pragma endregion

#pragma region Dynamics
Vector3 BWPhysik3D::D::GetVelocity(Vector3& p_momentum, double& p_mass)
{
	return Vector3(p_momentum / p_mass);
}

Vector3 BWPhysik3D::D::GetAcceleration(Vector3& p_force, double& p_mass)
{
	return Vector3(p_force / p_mass);
}

Vector3 BWPhysik3D::D::GetMomentum(Vector3& p_velocity, double& p_mass)
{
	return Vector3(p_velocity * p_mass);
}

Vector3 BWPhysik3D::D::GetForce(Vector3& p_acceleration, double& p_mass)
{
	return Vector3(p_acceleration * p_mass);
}

Vector3 BWPhysik3D::D::GetMassP(Vector3& p_momentum, Vector3& p_velocity)
{
	return Vector3(p_momentum / p_velocity);
}
Vector3 BWPhysik3D::D::GetMassF(Vector3& p_force, Vector3& p_acceleration)
{
	return Vector3(p_force / p_acceleration);
}
#pragma endregion