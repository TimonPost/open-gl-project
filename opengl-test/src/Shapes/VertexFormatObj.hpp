#pragma once

#include "glm.hpp"

/// <summary>
/// Vertex format with position and normal.
/// </summary>
struct VertexFormatObject
{
	glm::vec3 position;
	glm::vec3 normal;

	VertexFormatObject()
	{
		position = glm::vec3();
		normal = glm::vec3();
	}

	VertexFormatObject(glm::vec3 pos, glm::vec3 normal)
	{
		this->position = pos;
		this->normal = normal;
	}

	~VertexFormatObject() = default;
};
