#pragma once

#include "../Shapes/ShapeBase.h"
#include "../Shapes/VertexFormatObj.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

/// <summary>
/// A Simple Mesh Object that holds a name, a vertex list, and an index list. 
/// </summary>
class MeshObjectShape : public ShapeBase
{
public:
	
	// Variable Set Constructor
	MeshObjectShape(Mesh mesh) : ShapeBase("")
	{
		Vertices = mesh.Vertices;
		Indices = mesh.Indices;
		MeshName = mesh.MeshName;
		MeshMaterial = mesh.MeshMaterial;
		
		_size = sizeof(VertexFormatObjectWithUV) * Vertices.size();

		WithBuffer(&Vertices[0], _size);

		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);
	}
	
	// Mesh Name
	std::string MeshName;
	// Vertex List
	std::vector<VertexFormatObjectWithUV> Vertices;
	// Index List
	std::vector<unsigned int> Indices;
	// Material
	Material MeshMaterial;

	void Draw(Graphics* graphics) override
	{
		graphics->activeShader->SetUniformMatrix4fv("model", _model);
		glDrawArrays(GL_TRIANGLES, 0, _size);
	}	
};
