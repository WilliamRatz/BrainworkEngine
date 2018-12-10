#include "Cube.h"



Cube::Cube()
{
}
Cube::Cube(const Matrix<float, 4, 4>& p_defaultValue)
{

	m_model = p_defaultValue;
}


Cube::operator GameObject()
{
	return GameObject(m_model, m_vertices, m_indices);
}
