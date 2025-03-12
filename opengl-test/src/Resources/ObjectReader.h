#pragma once
#include <string>
#include <vector>

#include "MeshObjectShape.hpp"

/// <summary>
/// Object file reader abstraction.
/// </summary>
class ObjectReader
{
public:
	/// <summary>
	/// Returns a vector with vertex information from a single mesh.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	static std::vector<VertexFormatObjectWithUV> LoadObject(const std::string path);

	/// <summary>
	/// Returns a vector with meshes from an object file.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	static std::vector<Mesh> LoadMeshes(const std::string path);
};
