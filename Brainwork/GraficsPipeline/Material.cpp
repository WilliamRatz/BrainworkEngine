#include "Material.h"


Material::Material()
{
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

Texture Material::GetTexture()
{
	return m_texture;
}
Vector3 Material::GetColor()
{
	return m_color;
}

Texture& Material::GetTextureRef()
{
	return m_texture;
}
Vector3& Material::GetColorRef()
{
	return m_color;
}