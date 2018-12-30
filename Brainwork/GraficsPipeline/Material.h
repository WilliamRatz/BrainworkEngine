#pragma once
#include "Texture.h"

class Material
{
public:
	Vector3 m_color = Vector3(1.0f, 1.0f, 1.0f);
	Texture m_texture;


public:
	Material();
	~Material();

	void		SetTexture		(Texture texture);
	void		SetColor		(Vector3 color);
	Texture		GetTexture		();
	Vector3		GetColor		();

	Texture&	GetTextureRef	();
	Vector3&	GetColorRef		();



};

