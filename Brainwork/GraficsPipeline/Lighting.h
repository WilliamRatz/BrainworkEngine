#pragma once
#include "VK_inc.h"

class PointLight;

class Lighting
{
private:
	std::vector<PointLight*>	m_pPointLights;

public:
	Lighting();
	Lighting(const Lighting&);
	~Lighting();

	void AddPointLight(PointLight* pointLight);

	std::vector<PointLight*> GetPointLight();
	std::vector<PointLight*>& GetPointLightRef();

	void CleanUpLighting();
};

