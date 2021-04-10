#pragma once

#include <vec2.hpp>
#include <vec3.hpp>

#include "VertexFormatObj.hpp"

/// <summary>
/// Vertex format with UV, position and normal.
/// </summary>
struct VertexFormatObjectWithUV : public VertexFormatObject
{
	glm::vec2 uvs;

	VertexFormatObjectWithUV() = default;
	
	VertexFormatObjectWithUV(glm::vec3 _pos, const glm::vec3 _normals, glm::vec2 _uvs)
	{
		this->position = _pos;
		this->normal = _normals;
		this->uvs = _uvs;
	}

	~VertexFormatObjectWithUV() = default;
};
