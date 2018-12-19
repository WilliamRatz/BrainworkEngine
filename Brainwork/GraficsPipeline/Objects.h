#ifndef OBJECTS_H
#define OBJECTS_H

#include "VK_inc.h"

class GameObject;

struct Vertex {
	Quaternion pos;
	Vector3 color;
	Vector2 texCoord;

	Vertex(Quaternion p_position, Vector3 p_color, Vector2 p_texCoord)
	{
		pos = p_position;
		color = p_color;
		texCoord = p_texCoord;
	}

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}
};

class Cube
{
private:
	std::vector<Vertex> m_vertices{
		Vertex(Quaternion(-0.5f, -0.5f,  0.5f, 1.0f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f, 0.0f)),
		Vertex(Quaternion(+0.5f, -0.5f,  0.5f, 1.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f, 0.0f)),
		Vertex(Quaternion(+0.5f,  0.5f,  0.5f, 1.0f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f, 1.0f)),
		Vertex(Quaternion(-0.5f,  0.5f,  0.5f, 1.0f),	Vector3(1.0f, 1.0f, 1.0f),	Vector2(1.0f, 1.0f)),
												   	
		Vertex(Quaternion(-0.5f, -0.5f, -0.5f, 1.0f),	Vector3(1.0f, 1.0f, 1.0f),	Vector2(1.0f, 0.0f)),
		Vertex(Quaternion(+0.5f, -0.5f, -0.5f, 1.0f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f, 0.0f)),
		Vertex(Quaternion(+0.5f,  0.5f, -0.5f, 1.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f, 1.0f)),
		Vertex(Quaternion(-0.5f,  0.5f, -0.5f, 1.0f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f, 1.0f))
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
		Vertex(Quaternion(-0.5f, -0.5f, 1.0f, 1.0f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f, 0.0f)),
		Vertex(Quaternion(+0.5f, -0.5f, 1.0f, 1.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f, 0.0f)),
		Vertex(Quaternion(+0.5f,  0.5f, 1.0f, 1.0f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f, 1.0f)),
		Vertex(Quaternion(-0.5f,  0.5f, 1.0f, 1.0f),	Vector3(1.0f, 1.0f, 1.0f),	Vector2(1.0f, 1.0f))
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
		Vertex(Quaternion(-0.5f, -0.5f,  1.0f, 1.0f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f, 0.0f)),
		Vertex(Quaternion(+0.5f, -0.5f,  1.0f, 1.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f, 0.0f)),
		Vertex(Quaternion(+0.5f,  0.5f,  1.0f, 1.0f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f, 1.0f)),
		Vertex(Quaternion(-0.5f,  0.5f,  1.0f, 1.0f),	Vector3(1.0f, 1.0f, 1.0f),	Vector2(1.0f, 1.0f))
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
		Vertex(Quaternion(-0.5f, -0.5f,  1.0f, 1.0f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f, 0.0f)),
		Vertex(Quaternion(+0.5f, -0.5f,  1.0f, 1.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f, 0.0f)),
		Vertex(Quaternion(+0.5f,  0.5f,  1.0f, 1.0f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f, 1.0f)),
		Vertex(Quaternion(-0.5f,  0.5f,  1.0f, 1.0f),	Vector3(1.0f, 1.0f, 1.0f),	Vector2(1.0f, 1.0f))
	};
	std::vector<uint16_t> m_indices{
		0, 1, 2, 2, 3, 0
	};

	Capsule();

	operator GameObject();
};
#endif // !OBJECTS_H
