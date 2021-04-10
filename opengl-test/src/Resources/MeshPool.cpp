#include "MeshPool.h"

#include <string>

MeshPool* MeshPool::instance = nullptr;

MeshPool* MeshPool::Instance()
{
	if (instance == nullptr)
	{
		instance = new MeshPool();
	}

	return instance;
}

void MeshPool::AddMesh(Mesh* entry)
{
	Meshes.push_back(entry);
}

std::vector<Mesh*> MeshPool::GetMeshesById(std::string meshId)
{
	std::vector<Mesh*> foundMeshes = std::vector<Mesh*>();
	
	for (auto mesh: Meshes)
	{
		if (mesh->MeshName == meshId)
			foundMeshes.push_back(mesh);
	}

	return foundMeshes;
}