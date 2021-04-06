#pragma once

#include "glm.hpp"

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

struct VertexFormatObjectWithUV : public VertexFormatObject
{
	glm::vec2 uvs;

	VertexFormatObjectWithUV() : VertexFormatObject()
	{
		uvs = glm::vec2();
	}

	VertexFormatObjectWithUV(glm::vec3 _pos, const glm::vec3 _normals, glm::vec2 _uvs)
	{
		this->position = _pos;
		this->normal = _normals;
		this->uvs = _uvs;
	}

	~VertexFormatObjectWithUV() = default;
};
