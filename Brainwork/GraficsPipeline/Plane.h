#ifndef PLANE_H
#define PLANE_H
#include "VK_Object.h"

class Plane
{

public:
	Matrix<float, 4, 4> model;
	std::vector<Vertex> vertices{
		Vertex(-0.5f, -0.5f,  1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(	0.5f, -0.5f,  1.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(	0.5f,  0.5f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f,  1.0f, 1.0f,		1.0f, 1.0f, 1.0f),
	};
	std::vector<uint16_t> indices{
		0, 1, 2, 2, 3, 0
	};


	Plane();
	Plane(const Matrix<float, 4, 4>& defaultValue);
	Plane(const Plane& plane);
	~Plane();
};

#endif 

