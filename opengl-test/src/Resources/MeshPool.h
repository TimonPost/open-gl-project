#pragma once	
#include <vector>

#include "MeshObjectShape.hpp"

/// <summary>
/// Pool with loaded meshes that can be acquired by object instances.
/// This pool improves performance since meshes are not to be loaded multiple times.
/// </summary>
class MeshPool
{
public:
	std::vector<mesh*> Meshes;
		
	static MeshPool* Instance();

	/// <summary>
	/// Adds a mesh to the pool.
	/// </summary>
	/// <param name="entry"></param>
	void AddMesh(mesh* entry);

	/// <summary>
	/// Returns all meshes with the given id.
	/// </summary>
	/// <param name="meshId"></param>
	/// <returns></returns>
	std::vector<mesh*> GetMeshesById(std::string meshId);
	
private:
	MeshPool() {}
	MeshPool(ShaderPool const&) {};
	MeshPool& operator=(MeshPool const&);
	
	static MeshPool* instance;	
};


