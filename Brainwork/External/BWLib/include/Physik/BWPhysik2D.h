#ifndef BWPHYSIK2D_H
#define BWPHYSIK2D_H
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "BWPhysik.h"

class BWPhysik2D : public BWPhysik
{
public:
	/*
	direction = the vector which have to be refected
	normal = the normal of the reflected surface

	returns the refected vector
	*/
	static Vector2 Reflect(Vector2& direction, Vector2& normal);

	//position converted to velocity in  Space
	static Vector2 PosToVelo(Vector2& position, double& time);
	//position converted to acceleration in  Space
	static Vector2 PosToAccel(Vector2& position, double& time);

	//velocity converted to position in  Space
	static Vector2 VeloToPos(Vector2& velocity, Vector2& startPosition, double& time);
	//velocity converted to acceleration in  Space
	static Vector2 VeloToAccel(Vector2& velocity, double& time);

	//acceleration converted to position in  Space
	static Vector2 AccelToPos(Vector2& acceleration, Vector2& startVelocity, Vector2& startPosition, double& time);
	//acceleration converted to velocity in  Space
	static Vector2 AccelToVelo(Vector2& acceleration, Vector2& startVelocity, double& time);

	//calculation of force in  Space
	static Vector2 Force(double& mass, Vector2& acceleration);

	static Vector2 ForceToMomentum(Vector2& force, double& time);
	static Vector2 ForceToMass(Vector2& force, double& mass);
	static Vector2 ForceToAccel(Vector2& force, double& mass);

	//calculation of momentum in  Space
	static Vector2 Momentum(double& mass, Vector2& velocity);

	static Vector2 MomentumToForce(Vector2& momentum, double& time);
	static Vector2 MomentumToMass(Vector2& momentum, double& mass);
	static Vector2 MomentumToVeclocity(Vector2& momentum, double& mass);
};
#endif