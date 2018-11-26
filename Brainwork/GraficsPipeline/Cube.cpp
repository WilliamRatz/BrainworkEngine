#include "Cube.h"



Cube::Cube()
{
}
Cube::Cube(const Matrix<float, 4, 4>& defaultValue)
{

	model = defaultValue;
}
Cube::Cube(const Cube& cube)
{
	model = cube.model;
	vertices = cube.vertices;
	indices = cube.indices;
}
Cube::~Cube()
{
}
