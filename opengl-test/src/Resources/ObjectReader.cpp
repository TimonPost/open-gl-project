#include "ObjectReader.h"

#include <string>
#include <vector>

#include "MeshObjectShape.hpp"
#include "objectLoader.h"
#include "../Shapes/VertexFormatObj.hpp"


std::vector<VertexFormatObjectWithUV> ObjectReader::LoadObject(const std::string path)
{
	ObjectLoader ObjectLoader;
	bool loadout = ObjectLoader.LoadFile(path);

	return ObjectLoader.LoadedVertices;
}

std::vector<Mesh> ObjectReader::LoadMeshes(const std::string path)
{
	ObjectLoader ObjectLoader;
	bool loadout = ObjectLoader.LoadFile(path);

	return ObjectLoader.LoadedMeshes;
}

ObjectReader::~ObjectReader() = default;
