#include "BWPhysik2D.h"
#include "../Inc_BWMath.h"


Vector2 BWPhysik2D::Reflect(Vector2& p_direction, Vector2& p_normal)
{
	return  (p_direction - (p_normal * 2 * (Vector2::dot(p_direction, p_normal))));
}


Vector2 BWPhysik2D::PosToVelo(Vector2& p_position, double& p_time)
{
	return Vector2(p_position / p_time);
}
Vector2 BWPhysik2D::PosToAccel(Vector2& p_position, double& p_time)
{
	return Vector2((p_position / p_time) / p_time);
}

Vector2 BWPhysik2D::VeloToPos(Vector2& p_velocity, Vector2& p_startPosition, double& p_time)
{
	return Vector2((p_velocity * p_time) + p_startPosition);
}
Vector2 BWPhysik2D::VeloToAccel(Vector2& p_velocity, double& p_time)
{
	return Vector2(p_velocity / p_time);
}

Vector2 BWPhysik2D::AccelToPos(Vector2& p_acceleration, Vector2& p_startVelocity, Vector2& p_startPosition, double& p_time)
{
	return Vector2((p_acceleration / 2) * (p_time *p_time) + p_startVelocity * p_time + p_startPosition);
}
Vector2 BWPhysik2D::AccelToVelo(Vector2& p_acceleration, Vector2& p_startVelocity, double& p_time)
{
	return Vector2(p_acceleration * p_time + p_startVelocity);
}

Vector2 BWPhysik2D::Force(double& p_mass, Vector2& p_acceleration)
{
	return Vector2(p_acceleration * p_mass);
}
Vector2 BWPhysik2D::ForceToMomentum(Vector2& force, double& time)
{
	return Vector2();
}
Vector2 BWPhysik2D::ForceToMass(Vector2& force, double& mass)
{
	return Vector2();
}
Vector2 BWPhysik2D::ForceToAccel(Vector2& force, double& mass)
{
	return Vector2();
}
Vector2 BWPhysik2D::Momentum(double& p_mass, Vector2& p_velocity)
{
	return Vector2(p_velocity * p_mass);
}

Vector2 BWPhysik2D::MomentumToForce(Vector2& momentum, double& time)
{
	return Vector2();
}
Vector2 BWPhysik2D::MomentumToMass(Vector2& momentum, double& mass)
{
	return Vector2();
}
Vector2 BWPhysik2D::MomentumToVeclocity(Vector2& momentum, double& mass)
{
	return Vector2();
}