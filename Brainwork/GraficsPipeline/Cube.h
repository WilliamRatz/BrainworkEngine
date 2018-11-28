#ifndef CUBE_H
#define CUBE_H
#include "VK_Object.h"
class Cube
{
public:
	Matrix<float, 4, 4> model;
	std::vector<Vertex> vertices{
		Vertex(-0.5f, -0.5f,  0.5f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex( 0.5f, -0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex( 0.5f,  0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f,  0.5f, 1.0f,		1.0f, 1.0f, 1.0f),
							 
		Vertex(-0.5f, -0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f),
		Vertex(	0.5f, -0.5f, -0.5f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(	0.5f,  0.5f, -0.5f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(-0.5f,  0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f)
	};
	std::vector<uint16_t> indices{
		3, 0, 1, 1, 2, 3, //front
		7, 4, 0, 0, 3, 7, //left
		2, 1, 5, 5, 6, 2, //right
		6, 7, 3, 3, 2, 6, //top
		0, 4, 5, 5, 1, 0, //bottom
		5, 4, 7, 7, 6, 5  //back
	};


	Cube();
	Cube(const Matrix<float, 4, 4>& defaultValue);
	Cube(const Cube& cube);
	~Cube();
};

#endif
