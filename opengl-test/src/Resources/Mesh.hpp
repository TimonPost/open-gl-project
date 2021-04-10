#pragma once

#include <vector>

#include "Material.hpp"
#include "../Shapes/VertexformatObjectWithUV.hpp"

/// <summary>
/// A Simple Mesh Object that holds a name, a vertex list, and an index list.
/// </summary>
struct mesh
{
	// Default Constructor
	mesh()
	{}

	// Variable Set Constructor
	mesh(std::vector<VertexFormatObjectWithUV>& vertices, std::vector<unsigned int>& indices)
	{
		Vertices = vertices;
		Indices = indices;
	}
	
	// Mesh Name
	std::string MeshName;
	// Vertex List
	std::vector<VertexFormatObjectWithUV> Vertices;
	// Index List
	std::vector<unsigned int> Indices;

	// Material
	material MeshMaterial;
};