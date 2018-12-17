#ifndef OBJECTS_H
#define OBJECTS_H

#include "VK_inc.h"

class GameObject;

struct Vertex {
	Quaternion pos;
	Vector3 color;

	Vertex(float a1, float a2, float a3, float a4, float b1, float b2, float b3)
	{
		pos = Quaternion(a1, a2, a3, a4);
		color = Vector3(b1, b2, b3);
	}

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

class Cube
{
private:
	std::vector<Vertex> m_vertices{
		Vertex(-0.5f, -0.5f,  0.5f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(0.5f,  0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f,  0.5f, 1.0f,		1.0f, 1.0f, 1.0f),

		Vertex(-0.5f, -0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f),
		Vertex(0.5f, -0.5f, -0.5f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(0.5f,  0.5f, -0.5f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(-0.5f,  0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f)
	};
	std::vector<uint16_t> m_indices{
		3, 0, 1, 1, 2, 3, //front
		7, 4, 0, 0, 3, 7, //left
		2, 1, 5, 5, 6, 2, //right
		6, 7, 3, 3, 2, 6, //top
		0, 4, 5, 5, 1, 0, //bottom
		5, 4, 7, 7, 6, 5  //back
	};

public:
	Cube();

	operator GameObject();
};

class Plane
{
public:
	std::vector<Vertex> m_vertices{
		Vertex(-0.5f, -0.5f,  1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f,  1.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(0.5f,  0.5f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f,  1.0f, 1.0f,		1.0f, 1.0f, 1.0f),
	};
	std::vector<uint16_t> m_indices{
		0, 1, 2, 2, 3, 0
	};

	Plane();

	operator GameObject();
};

class Sphere 
{
	std::vector<Vertex> m_vertices{
		Vertex(-0.5f, -0.5f,  1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f,  1.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(0.5f,  0.5f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f,  1.0f, 1.0f,		1.0f, 1.0f, 1.0f),
	};
	std::vector<uint16_t> m_indices{
		0, 1, 2, 2, 3, 0
	};

	Sphere();

	operator GameObject();
};

class Capsule
{
	std::vector<Vertex> m_vertices{
		Vertex(-0.5f, -0.5f,  1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f,  1.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(0.5f,  0.5f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,  0.5f,  1.0f, 1.0f,		1.0f, 1.0f, 1.0f),
	};
	std::vector<uint16_t> m_indices{
		0, 1, 2, 2, 3, 0
	};

	Capsule();

	operator GameObject();
};
#endif // !OBJECTS_H
