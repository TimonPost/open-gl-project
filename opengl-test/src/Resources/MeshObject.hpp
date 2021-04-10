#pragma once

#include "MeshObjectShape.hpp"
#include "MeshPool.h"
#include "ObjectReader.h"
#include "../Shapes/ShapeBase.h"

class MeshesLoader : public ShapeBase
{
public:
	std::vector<MeshObjectShape*> meshObjects;

	MeshesLoader(MeshesLoader* toClone) : ShapeBase(toClone)
	{
	}

	MeshesLoader(std::string textureIdentifier, const std::string& objectMeshID) :ShapeBase(
		std::move(textureIdentifier))
	{
		MeshPool* pool = MeshPool::Instance();
		
		std::vector<Mesh*> meshes = pool->GetMeshesById(objectMeshID);

		for (auto& mesh : meshes)
		{
			MeshObjectShape* m = new MeshObjectShape(*mesh);
			m->TextureIdentifier = TextureIdentifier;
			meshObjects.push_back(m);
		}
	}

	virtual void Draw(Graphics* graphics)
	{
		throw exception("can not be drawn");
	}

	void Scale(glm::vec3 scale) override
	{
		for (auto& mesh : meshObjects)
		{
			mesh->Scale(scale);
		}
	}

	void Rotate(glm::vec3 rotate, float angle) override
	{
		for (auto& mesh : meshObjects)
		{
			mesh->Rotate(rotate, angle);
		}
	}

	void Translate(glm::vec3 translate) override
	{
		for (auto& mesh : meshObjects)
		{
			mesh->Translate(translate);
		}
	}

	void WithBuffer(void* data, int size) override
	{
		throw exception("can not bind buffer");
	}

	void WithIndexBuffer(unsigned* indices, unsigned size) override
	{
		throw exception("can not bind buffer");
	}

	void Bind() const override
	{
		throw exception("can not bind buffer");
	}

	void Unbind() const override
	{
		throw exception("can not unbind buffer");
	}

	virtual ~MeshesLoader()
	{
	}
};
