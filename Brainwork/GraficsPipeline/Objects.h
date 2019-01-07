#ifndef OBJECTS_H
#define OBJECTS_H

#include "VK_inc.h"


struct Vertex {
	Vector3 pos;
	Vector3 color;
	Vector2 texCoord;
	Vector3 normal;

	Vertex(Vector3 p_position, Vector3 p_color, Vector2 p_texCoord, Vector3 p_normal)
	{
		pos = p_position;
		color = p_color;
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

	static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		attributeDescriptions[3].binding = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[3].offset = offsetof(Vertex, normal);

		return attributeDescriptions;
	}

	void ColorChange(Vector3& p_color)
	{
		color = p_color;
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
	std::vector<uint32_t>		GetIndices();
	std::vector<Vertex>&		GetVerticesRef();
	std::vector<uint32_t>&		GetIndicesRef();
};

class Cube
{
private:
	Vector3					m_color = Vector3(1.0f, 1.0f, 1.0f);
	//std::vector<Vertex>		m_vertices{
	//	//front
	//	Vertex(Vector3(-0.5f, +0.5f, -0.5f),	m_color,	Vector2(1.0f, 0.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, -0.5f),	m_color,	Vector2(0.0f, 0.0f)),
	//	Vertex(Vector3(+0.5f, -0.5f, -0.5f),	m_color,	Vector2(0.0f, 1.0f)),
	//	Vertex(Vector3(-0.5f, -0.5f, -0.5f),	m_color,	Vector2(1.0f, 1.0f)),

	//	//left
	//	Vertex(Vector3(-0.5f, +0.5f, +0.5f),	m_color,	Vector2(2.0f, 1.0f)),
	//	Vertex(Vector3(-0.5f, +0.5f, -0.5f),	m_color,	Vector2(1.0f, 1.0f)),
	//	Vertex(Vector3(-0.5f, -0.5f, -0.5f),	m_color,	Vector2(1.0f, 2.0f)),
	//	Vertex(Vector3(-0.5f, -0.5f, +0.5f),	m_color,	Vector2(2.0f, 2.0f)),

	//	//right
	//	Vertex(Vector3(+0.5f, -0.5f, +0.5f),	m_color,	Vector2(2.0f, 3.0f)),
	//	Vertex(Vector3(+0.5f, -0.5f, -0.5f),	m_color,	Vector2(3.0f, 3.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, -0.5f),	m_color,	Vector2(3.0f, 2.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, +0.5f),	m_color,	Vector2(2.0f, 2.0f)),

	//	//top
	//	Vertex(Vector3(-0.5f, +0.5f, +0.5f),	m_color,	Vector2(4.0f, 3.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, +0.5f),	m_color,	Vector2(3.0f, 3.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, -0.5f),	m_color,	Vector2(3.0f, 4.0f)),
	//	Vertex(Vector3(-0.5f, +0.5f, -0.5f),	m_color,	Vector2(4.0f, 4.0f)),

	//	//bottom
	//	Vertex(Vector3(-0.5f, -0.5f, -0.5f),	m_color,	Vector2(5.0f, 4.0f)),
	//	Vertex(Vector3(+0.5f, -0.5f, -0.5f),	m_color,	Vector2(4.0f, 4.0f)),
	//	Vertex(Vector3(+0.5f, -0.5f, +0.5f),	m_color,	Vector2(4.0f, 5.0f)),
	//	Vertex(Vector3(-0.5f, -0.5f, +0.5f),	m_color,	Vector2(5.0f, 5.0f)),

	//	//back
	//	Vertex(Vector3(-0.5f, -0.5f, +0.5f),	m_color,	Vector2(5.0f, 6.0f)),
	//	Vertex(Vector3(+0.5f, -0.5f, +0.5f),	m_color,	Vector2(6.0f, 6.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, +0.5f),	m_color,	Vector2(6.0f, 5.0f)),
	//	Vertex(Vector3(-0.5f, +0.5f, +0.5f),	m_color,	Vector2(5.0f, 5.0f))

	//};
	//std::vector<uint32_t>	m_indices{
	//	2, 1, 0, 0, 3, 2, //front
	//	6, 5, 4, 4, 7, 6, //left
	//	10, 9,8,8,11, 10, //right
	//   14,13,12,12,15,14, //top
	//   18,17,16,16,19,18, //bottom
	//   22,21,20,20,23,22,  //back
	//};

	//std::vector<Vertex>		m_vertices{
	//	Vertex(Vector3(-0.5f, -0.5f, +0.5f),	m_color,	Vector2(0.0f,0.0f)),
	//	Vertex(Vector3(+0.5f, -0.5f, +0.5f),	m_color,	Vector2(0.0f,1.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, +0.5f),	m_color,	Vector2(1.0f,1.0f)),
	//	Vertex(Vector3(-0.5f, +0.5f, +0.5f),	m_color,	Vector2(1.0f,0.0f)),
	//										  		 	
	//	Vertex(Vector3(-0.5f, -0.5f, -0.5f),	m_color,	Vector2(1.0f,1.0f)),
	//	Vertex(Vector3(+0.5f, -0.5f, -0.5f),	m_color,	Vector2(1.0f,2.0f)),
	//	Vertex(Vector3(+0.5f, +0.5f, -0.5f),	m_color,	Vector2(2.0f,2.0f)),
	//	Vertex(Vector3(-0.5f, +0.5f, -0.5f),	m_color,	Vector2(2.0f,1.0f))
	//};
	//std::vector<uint32_t>	m_indices{
	//	1, 0, 3, 3, 2, 1, //front
	//	0, 4, 7, 7, 3, 0, //left
	//	5, 1, 2, 2, 6, 5, //right
	//	3, 7, 6, 6, 2, 3, //top
	//	5, 4, 0, 0, 1, 5, //bottom
	//	7, 4, 5, 5, 6, 7  //back
	//};

public:
	Cube					();
	~Cube					();

	operator				Object();
};

class Plane
{
private:
	Vector3					m_color = Vector3(1.0f, 1.0f, 1.0f);
	/*std::vector<Vector2*>	m_texCoords;
	std::vector<Vertex>		m_vertices{
		Vertex(Vector3(-0.5f, -0.5f, -0.5f),	m_color,	Vector2(1.0f, 1.0f)),
		Vertex(Vector3(+0.5f, -0.5f, -0.5f),	m_color,	Vector2(0.0f, 1.0f)),
		Vertex(Vector3(+0.5f, +0.5f, -0.5f),	m_color,	Vector2(0.0f, 0.0f)),
		Vertex(Vector3(-0.5f, +0.5f, -0.5f),	m_color,	Vector2(1.0f, 0.0f)),
	};
	std::vector<uint32_t>	m_indices{
		0, 1, 2, 2, 3, 0
	};*/

public:
	Plane					();

	operator				Object();
};

class Sphere
{
private:
	Vector3					m_color = Vector3(1.0f, 1.0f, 1.0f);
	/*std::vector<Vector2*>	m_texCoords;
	std::vector<Vertex>		m_vertices{
		Vertex(Vector3(-0.5f, -0.5f, -0.5f),	m_color,	Vector2(1.0f, 1.0f)),
		Vertex(Vector3(+0.5f, -0.5f, -0.5f),	m_color,	Vector2(0.0f, 1.0f)),
		Vertex(Vector3(+0.5f, +0.5f, -0.5f),	m_color,	Vector2(0.0f, 0.0f)),
		Vertex(Vector3(-0.5f, +0.5f, -0.5f),	m_color,	Vector2(1.0f, 0.0f)),
	};
	std::vector<uint32_t>	m_indices{
		0, 1, 2, 2, 3, 0
	};
*/
public:
	Sphere					();

	operator				Object();
};

class Capsule
{
private:
	Vector3					m_color = Vector3(1.0f, 1.0f, 1.0f);
	/*std::vector<Vector2*>	m_texCoords;
	std::vector<Vertex>		m_vertices{
		Vertex(Vector3(-0.5f, -0.5f, -0.5f),	m_color,	Vector2(1.0f, 1.0f)),
		Vertex(Vector3(+0.5f, -0.5f, -0.5f),	m_color,	Vector2(0.0f, 1.0f)),
		Vertex(Vector3(+0.5f, +0.5f, -0.5f),	m_color,	Vector2(0.0f, 0.0f)),
		Vertex(Vector3(-0.5f, +0.5f, -0.5f),	m_color,	Vector2(1.0f, 0.0f)),
	};
	std::vector<uint32_t>	m_indices{
		0, 1, 2, 2, 3, 0
	};*/

public:
	Capsule					();

	operator				Object();
};
#endif // !OBJECTS_H
