#pragma once

#include "glm.hpp"

struct VertexFormat
{
	glm::vec4 position;
	glm::vec4 color;

	VertexFormat()
	{
	}

	VertexFormat(glm::vec4 pos, glm::vec4 col)
	{
		position = pos;
		color = col;
	}

	~VertexFormat()
	{
	}
};
