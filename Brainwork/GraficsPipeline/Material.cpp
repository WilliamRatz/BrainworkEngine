#include "Material.h"


Material::Material()
{
}
Material::Material(const Material& p_material)
{
	m_color = p_material.m_color;
	m_texture = p_material.m_texture;
}
Material::~Material()
{
}

void Material::SetTexture(Texture p_texture)
{
	m_texture = p_texture;
}
void Material::SetColor(Vector3 color)
{
	m_color = color;
}

Vector3 Material::GetColor()
{
	return m_color;
}
Vector3& Material::GetColorRef()
{
	return m_color;
}

Texture Material::GetTexture()
{
	return m_texture;
}
Texture& Material::GetTextureRef()
{
	return m_texture;
}

void Material::CleanUpMaterial() 
{
	m_texture.CleanUpTexture();
}