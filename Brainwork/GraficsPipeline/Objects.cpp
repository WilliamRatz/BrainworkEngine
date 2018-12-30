#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "Objects.h"


#pragma region Object
Object::Object()
{

}
Object::Object(const Object& p_object)
{
	m_vertices = p_object.m_vertices;
	m_indices = p_object.m_indices;
}
Object::~Object()
{

}

void Object::SetMesh(std::string directoryPath)
{

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, directoryPath.c_str())) {
		throw std::runtime_error(warn + err);
	}

	if (shapes[0].mesh.indices[0].texcoord_index == 0)
	{
		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex(
					Vector3(attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1], attrib.vertices[3 * index.vertex_index + 2]),
					Vector3(1.0f, 1.0f, 1.0f),
					Vector2(attrib.texcoords[2 * index.texcoord_index + 0], 2 * attrib.texcoords[index.texcoord_index + 1])
				);

				m_vertices.push_back(vertex);
				m_indices.push_back(m_indices.size());
			}
		}
	}
	else {
		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex(
					Vector3(attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1], attrib.vertices[3 * index.vertex_index + 2]),
					Vector3(1.0f, 1.0f, 1.0f),
					Vector2(0.0f, 0.0f)
				);

				m_vertices.push_back(vertex);
				m_indices.push_back(m_indices.size());
			}
		}
	}
}

void Object::SetVertices(std::vector<Vertex>& p_vertices)
{
	m_vertices = p_vertices;
}
void Object::SetIndices(std::vector<uint32_t>& p_indices)
{
	m_indices = p_indices;
}

std::vector<Vertex>	 Object::GetVertices()
{
	return m_vertices;
}
std::vector<uint32_t> Object::GetIndices()
{
	return m_indices;
}
std::vector<Vertex>& Object::GetVerticesRef()
{
	return m_vertices;
}
std::vector<uint32_t>& Object::GetIndicesRef()
{
	return m_indices;
}
#pragma endregion


#pragma region Cube
Cube::Cube()
{
}

Cube::~Cube()
{
}

Cube::operator Object()
{
	Object temp;
	temp.SetVertices(m_vertices);
	temp.SetIndices(m_indices);

	return temp;
}
#pragma endregion

#pragma region Plane
Plane::Plane()
{
}

Plane::operator Object()
{
	Object temp;
	temp.SetVertices(m_vertices);
	temp.SetIndices(m_indices);

	return temp;
}
#pragma endregion

#pragma region Sphere
Sphere::Sphere()
{
}

Sphere::operator Object()
{
	Object temp;
	temp.SetVertices(m_vertices);
	temp.SetIndices(m_indices);

	return temp;
}
#pragma endregion

#pragma region Capsule
Capsule::Capsule()
{
}

Capsule::operator Object()
{
	Object temp;
	temp.SetVertices(m_vertices);
	temp.SetIndices(m_indices);

	return temp;
}
#pragma endregion

