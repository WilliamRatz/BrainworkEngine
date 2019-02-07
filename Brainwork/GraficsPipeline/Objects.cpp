#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "Objects.h"
#include "Material.h"
#include "VK_Renderer.h"

#pragma region Object
Object::Object()
{

}
Object::Object(const Object& p_object)
{
	m_ubo = p_object.m_ubo;
	m_bufferObject = p_object.m_bufferObject;

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
					Vector2(attrib.texcoords[2 * index.texcoord_index + 0], 2 * attrib.texcoords[index.texcoord_index + 1]),
					Vector3(-attrib.normals[3 * index.normal_index + 0], -attrib.normals[3 * index.normal_index + 1], -attrib.normals[3 * index.normal_index + 2])
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
					Vector2(0.0f, 0.0f),
					Vector3(attrib.normals[3 * index.normal_index + 0], attrib.normals[3 * index.normal_index + 1], attrib.normals[3 * index.normal_index + 2])
				);

				m_vertices.push_back(vertex);
				m_indices.push_back(m_indices.size());
			}
		}
	}
}
void Object::CreateBuffer(VK_Renderer* p_renderer)
{
	m_bufferObject.SetRenderer(p_renderer);
	m_bufferObject.CreateVertexBuffer(m_vertices);
	m_bufferObject.CreateIndexBuffer(m_indices);
}

UniformBufferObject	Object::GetUniformBufferObject()
{
	return m_ubo;
}
UniformBufferObject& Object::GetUniformBufferObjectRef()
{
	return m_ubo;
}

VK_BufferObject	Object::GetVK_BufferObject()
{
	return m_bufferObject;
}
VK_BufferObject& Object::GetVK_BufferObjectRef()
{
	return m_bufferObject;
}

std::vector<Vertex>	 Object::GetVertices()
{
	return m_vertices;
}
std::vector<Vertex>& Object::GetVerticesRef()
{
	return m_vertices;
}

std::vector<uint32_t> Object::GetIndices()
{
	return m_indices;
}
std::vector<uint32_t>& Object::GetIndicesRef()
{
	return m_indices;
}

void Object::CleanUpObject()
{
	m_bufferObject.CleanUp();
}
#pragma endregion


#pragma region Cube
Cube::Cube()
{
}

Cube::operator Object()
{
	Object temp;
	temp.SetMesh(m_directoryPath);

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
	temp.SetMesh(m_directoryPath);

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
	temp.SetMesh(m_directoryPath);

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
	temp.SetMesh(m_directoryPath);

	return temp;
}
#pragma endregion

