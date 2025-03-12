#pragma once

#include <vector>
#include <string>
#include <vec3.hpp>

#include "Material.hpp"
#include "MeshObjectShape.hpp"

#include "../Algorithm.hpp"
#include "../Math.hpp"

/// <summary>
/// Object file loader.
/// </summary>
class ObjectLoader
{
private:
	/// <summary>
	/// Generate vertices from a list of positions, tcoords, normals and a face line
	/// </summary>
	/// <param name="oVerts"></param>
	/// <param name="iPositions"></param>
	/// <param name="iTCoords"></param>
	/// <param name="iNormals"></param>
	/// <param name="icurline"></param>
	void GenVerticesFromRawOBJ(std::vector<VertexFormatObjectWithUV>& oVerts,
		const std::vector<glm::vec3>& iPositions,
		const std::vector<glm::vec2>& iTCoords,
		const std::vector<glm::vec3>& iNormals,
		std::string icurline) const;

	void VertexTriangluation(std::vector<unsigned int>& oIndices,
		const std::vector<VertexFormatObjectWithUV>& iVerts);
	
	/// <summary>
	/// Load Materials from .mtl file
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	bool LoadMaterials(std::string path);

public:
	ObjectLoader();

	~ObjectLoader();

	/// Loaded Mesh Objects
	std::vector<Mesh> LoadedMeshes;
	/// Loaded Vertex Objects
	std::vector<VertexFormatObjectWithUV> LoadedVertices;
	/// Loaded Index Positions
	std::vector<unsigned int> LoadedIndices;
	/// Loaded Material Objects
	std::vector<Material> LoadedMaterials;

	/// Load a file into the loader
	///
	/// If file is loaded return true
	///
	/// If the file is unable to be found
	/// or unable to be loaded return false
	bool LoadFile(std::string Path);
};