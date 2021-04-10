#pragma once

#include "mesh.hpp"
#include "MeshObjectShape.hpp"
#include "MeshPool.h"
#include "../Shapes/ShapeBase.h"

/// <summary>
///  Mesh loader capable of loading and transforming one or more a mesh(es).
/// </summary>
class MeshLoader : public ShapeBase
{
public:
	std::vector<MeshObjectShape*> meshObjects;

	MeshLoader(MeshLoader* toClone) : ShapeBase(toClone)
	{
	}

	MeshLoader(std::string textureIdentifier, const std::string& objectMeshID) :ShapeBase(
		std::move(textureIdentifier))
	{
		MeshPool* pool = MeshPool::Instance();
		
		std::vector<mesh*> meshes = pool->GetMeshesById(objectMeshID);

		for (auto& mesh : meshes)
		{
			MeshObjectShape* m = new MeshObjectShape(*mesh);
			m->TextureIdentifier = TextureIdentifier;
			meshObjects.push_back(m);
		}
	}

	virtual void Draw(Graphics* graphics)
	{
		throw std::exception("can not be drawn");
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
		throw std::exception("can not bind buffer");
	}

	void WithIndexBuffer(unsigned* indices, unsigned size) override
	{
		throw std::exception("can not bind buffer");
	}

	void Bind() const override
	{
		throw std::exception("can not bind buffer");
	}

	void Unbind() const override
	{
		throw std::exception("can not unbind buffer");
	}

	virtual ~MeshLoader()
	{
	}
};
