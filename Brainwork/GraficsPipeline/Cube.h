#ifndef CUBE_H
#define CUBE_H
#include "VK_Object.h"
class Cube
{
public:
	Matrix<float, 4, 4> model;
	std::vector<Vertex> vertices{
		Vertex(-0.5f, -0.5f, 0.5f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex( 0.5f, -0.5f, 0.5f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex( 0.5f,  0.5f, 0.5f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f),
							 
		Vertex(-0.5f, -0.5f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(	0.5f, -0.5f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(	0.5f,  0.5f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f)
	};
	std::vector<uint16_t> indices{
		0, 1, 2, 2, 3, 0, //front
		4, 0, 3, 3, 7, 4, //left
		2, 6, 5, 5, 1, 2, //right
		3, 7, 6, 6, 2, 3, //top
		0, 1, 5, 5, 4, 0, //bottom
		4, 5, 6, 6, 7, 4  //back
	};


	Cube();
	Cube(const Matrix<float, 4, 4>& defaultValue);
	Cube(const Cube& cube);
	~Cube();
};

#endif
