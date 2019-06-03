//
//  BWPhysik3D.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef BWPHYSIK3D_H
#define BWPHYSIK3D_H
#include "BWPhysik.h"


class BWPhysik3D : public BWPhysik
{
public:
	/*
		direction = the vector which have to be refected
		normal = the normal of the reflected surface

		returns the refected vector
	*/
	static Vector3 Reflect(Vector3& direction, Vector3& normal);

#pragma region UniformMotion
	//Uniform Motion
	class UM
	{
		static Vector3 GetElapseTime(Vector3& distance, Vector3& velocity);

		static Vector3 GetPosition(Vector3& velocity, double& elapsedTime);
		static Vector3 GetPosition(Vector3& velocity, double& elapsedTime, Vector3& startDistance);

		static Vector3 GetVelocity(Vector3& distance, double& elapsedTime);
	};
#pragma endregion

#pragma region Kinematics
	//Kinematics
	class K
	{
		static Vector3 GetElapseTime(Vector3& velocity, Vector3& acceleration);
		static Vector3 GetElapseTime(Vector3& velocity, Vector3& acceleration, Vector3& initialVelocity);

		static Vector3 GetPosition(Vector3& acceleration, double& elapsedTime);
		static Vector3 GetPosition(Vector3& acceleration, double& elapsedTime, Vector3& initialVelocity, Vector3& startDistance);

		static Vector3 GetVelocity(Vector3& acceleration, double& elapsedTime);
		static Vector3 GetVelocity(Vector3& acceleration, double& elapsedTime, Vector3& initialVelocity);

		static Vector3 GetAcceleration(Vector3& velocity, double& elapsedTime);
		static Vector3 GetAcceleration(Vector3& velocity, double& elapsedTime, Vector3& initialVelocity);

	};
#pragma endregion

#pragma region Dynamics
	//Dynamics
	class D
	{
		static Vector3 GetVelocity(Vector3& momentum, double& mass);

		static Vector3 GetAcceleration(Vector3& force, double& mass);

		static Vector3 GetMomentum(Vector3& velocity, double& mass);

		static Vector3 GetForce(Vector3& acceleration, double& mass);

		static Vector3 GetMassP(Vector3& momentum, Vector3& velocity);
		static Vector3 GetMassF(Vector3& force, Vector3& acceleration);
	};
#pragma endregion

	
};

#endif