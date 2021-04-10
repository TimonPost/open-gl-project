#pragma once
#include <string>
#include <vector>

#include "MeshObjectShape.hpp"

struct VertexFormatObjectWithUV;

class ObjectReader
{
public:
	static std::vector<VertexFormatObjectWithUV> LoadObject(const std::string path);

	static std::vector<Mesh> LoadMeshes(const std::string path);

	~ObjectReader();
};
