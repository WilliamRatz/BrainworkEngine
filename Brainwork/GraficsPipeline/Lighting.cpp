#include "Lighting.h"
#include "PointLight.h"


Lighting::Lighting()
{
}

Lighting::Lighting(const Lighting& p_lighting)
{
	m_pPointLights = p_lighting.m_pPointLights;
}

Lighting::~Lighting()
{
}

void Lighting::AddPointLight(PointLight* pointLight)
{
	m_pPointLights.push_back(pointLight);
}

std::vector<PointLight*> Lighting::GetPointLight()
{
	return m_pPointLights;
}
std::vector<PointLight*>& Lighting::GetPointLightRef()
{
	return m_pPointLights;
}

void Lighting::CleanUpLighting()
{

}
