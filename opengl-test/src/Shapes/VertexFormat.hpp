#pragma once

#include "glm.hpp"

/// <summary>
/// Most basic vertex buffer format.
/// </summary>
struct VertexFormat
{
	glm::vec4 position{};
	glm::vec4 color{};

	VertexFormat() = default;

	VertexFormat(glm::vec4 pos, glm::vec4 col)
	{
		position = pos;
		color = col;
	}

	~VertexFormat() = default;
};
