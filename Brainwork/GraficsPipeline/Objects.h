#ifndef OBJECTS_H
#define OBJECTS_H

#include "VK_inc.h"


struct Vertex {
	Vector3 pos;
	Vector2 texCoord;
	Vector3 normal;

	Vertex(Vector3 p_position,Vector2 p_texCoord, Vector3 p_normal)
	{
		pos = p_position;
		texCoord = p_texCoord;
		normal = p_normal;
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
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, texCoord);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, normal);

		return attributeDescriptions;
	}
};

class Object 
{
private:
	std::vector<Vertex>			m_vertices;
	std::vector<uint32_t>		m_indices;

public:
	Object						();
	Object						(const Object&);
	~Object						();

	void SetMesh				(std::string directoryPath);

	void SetVertices			(std::vector<Vertex>& vertices);
	void SetIndices				(std::vector<uint32_t>& indices);

	std::vector<Vertex>			GetVertices();
	std::vector<Vertex>&		GetVerticesRef();
	std::vector<uint32_t>		GetIndices();
	std::vector<uint32_t>&		GetIndicesRef();
};

class Cube
{
	std::string m_directoryPath = "models/Cube.obj";

public:
	Cube					();

	operator				Object();
};
class Plane
{
	std::string m_directoryPath = "models/Plane.obj";

public:
	Plane					();

	operator				Object();
};
class Sphere
{
	std::string m_directoryPath = "models/Sphere.obj";

public:
	Sphere					();

	operator				Object();
};
class Capsule
{
private:
	std::string m_directoryPath = "models/Capsule.obj";

public:
	Capsule					();

	operator				Object();
};
#endif // !OBJECTS_H
