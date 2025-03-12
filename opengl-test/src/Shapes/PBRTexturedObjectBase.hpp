#pragma once

#include <vector>

#include "ShapeBase.h"
#include "VertexformatObjectWithUV.hpp"
#include "../Resources/ObjectReader.h"

class PBRTexturedObjectBase : public ShapeBase
{
public:

	PBRTexturedObjectBase(PBRTexturedObjectBase* toClone) : ShapeBase(toClone)
	{
	}

	PBRTexturedObjectBase(std::string textureIdentifier, const std::string& objPath) :ShapeBase(
		std::move(textureIdentifier))
	{
		MeshPool* pool = MeshPool::Instance();
		std::vector<Mesh*> meshes = pool->GetMeshesById(objPath);
		Mesh* mesh = meshes[0];
		
		_size = (sizeof(VertexFormatObjectWithUV) * mesh->Vertices.size());

		WithBuffer(&mesh->Vertices[0], _size);

		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);
	}

	virtual void Draw(Graphics* graphics) = 0;
};
