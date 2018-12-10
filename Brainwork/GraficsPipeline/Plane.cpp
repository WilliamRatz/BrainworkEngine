#include "Plane.h"


Plane::Plane()
{
}

Plane::Plane(const Matrix<float, 4, 4>& p_defaultValue)
{
	m_model = p_defaultValue;
}

Plane::operator GameObject()
{
	return GameObject(m_model, m_vertices, m_indices);
}
