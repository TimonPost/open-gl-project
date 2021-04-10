#pragma once	
#include <vector>

#include "MeshObjectShape.hpp"

class MeshPool
{
public:
	vector<Mesh*> Meshes;

	MeshPool(ShaderPool const&);
	MeshPool& operator=(MeshPool const&);

	static MeshPool* Instance();
	
	void AddMesh(Mesh* entry);
	vector<Mesh*> GetMeshesById(std::string objectId);
	
	MeshPool() {}
private:
	static MeshPool* instance;	
};


