#pragma once
#include "Texture.h"

class Material
{
private:
	Vector3* Color;
	Vector2* texCoords;
	unsigned int texCoordCount = 8;

	Texture texture;

public:


	Material();
	~Material();
};

