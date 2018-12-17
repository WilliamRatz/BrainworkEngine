#include "GameObject.h"
#include "Objects.h"


#pragma region Cube
Cube::Cube()
{
}

Cube::operator GameObject()
{
	return GameObject(m_vertices, m_indices);
}
#pragma endregion

#pragma region Plane
Plane::Plane()
{
}

Plane::operator GameObject()
{
	return GameObject(m_vertices, m_indices);
}
#pragma endregion

#pragma region Sphere
Sphere::Sphere()
{
}

Sphere::operator GameObject()
{
	return GameObject(m_vertices, m_indices);
}
#pragma endregion

#pragma region Capsule
Capsule::Capsule()
{
}

Capsule::operator GameObject()
{
	return GameObject(m_vertices, m_indices);
}
#pragma endregion
