#ifndef PLANE_H
#define PLANE_H
#include "GameObject.h"

class Plane
{
public:
	Matrix<float, 4, 4> m_model;
	std::vector<Vertex> m_vertices{
		Vertex(-0.5f, -0.5f,  1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(	0.5f, -0.5f,  1.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(	0.5f,  0.5f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f,  1.0f, 1.0f,		1.0f, 1.0f, 1.0f),
	};
	std::vector<uint16_t> m_indices{
		0, 1, 2, 2, 3, 0
	};


	Plane();
	Plane(const Matrix<float, 4, 4>& defaultValue);
	~Plane();

	operator GameObject();
};

#endif 

