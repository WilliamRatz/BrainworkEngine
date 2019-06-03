#pragma once
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"

class BWPhysik
{
public:

	/*
		gravity = the gravity of the envioroment in m/s^2
		time = time of fall in s
		returns the distance of fall in time
	*/
	static double FreeFall(double& gravity, double& time);
};

