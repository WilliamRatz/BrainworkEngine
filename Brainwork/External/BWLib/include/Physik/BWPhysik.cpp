#include "BWPhysik.h"


double BWPhysik::FreeFall(double& p_gravity, double& p_time)
{
	return (p_gravity * (p_time * p_time)) / 2;
}
