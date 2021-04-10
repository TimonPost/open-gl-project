#include "MeshPool.h"

#include <string>

MeshPool* MeshPool::instance = 0;

MeshPool* MeshPool::Instance()
{
	if (instance == 0)
	{
		instance = new MeshPool();
	}

	return instance;
}

void MeshPool::AddMesh(Mesh* entry)
{
	Meshes.push_back(entry);
}

vector<Mesh*> MeshPool::GetMeshesById(std::string objectId)
{
	vector<Mesh*> foundMeshes = vector<Mesh*>();
	
	for (auto mesh: Meshes)
	{
		if (mesh->MeshName == objectId)
			foundMeshes.push_back(mesh);
	}

	return foundMeshes;
}