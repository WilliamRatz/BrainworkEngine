#pragma once
#include "Texture.h"

class Material
{
public:
	Vector3 m_color = Vector3(1.0f, 1.0f, 1.0f);
	Texture m_texture;

public:
	Material();
	Material(const Material& material);
	~Material();

	void		SetTexture		(Texture texture);
	void		SetColor		(Vector3 color);
	
	Vector3		GetColor		();
	Vector3&	GetColorRef		();

	Texture		GetTexture		();
	Texture&	GetTextureRef	();

	void CleanUpMaterial		();
};

