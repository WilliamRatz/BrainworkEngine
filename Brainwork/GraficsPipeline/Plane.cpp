#include "Plane.h"


Plane::Plane()
{
}

Plane::Plane(const Matrix<float, 4, 4>& defaultValue)
{
	model = defaultValue;
}
Plane::Plane(const Plane& plane)
{
	model = plane.model;
	vertices = plane.vertices;
	indices = plane.indices;
}


Plane::~Plane()
{
}
