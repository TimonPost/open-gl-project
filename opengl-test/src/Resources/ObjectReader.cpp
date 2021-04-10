#include "ObjectReader.h"

#include <string>
#include <vector>

#include "MeshObjectShape.hpp"
#include "objectLoader.h"
#include "../Shapes/VertexformatObjectWithUV.hpp"


std::vector<VertexFormatObjectWithUV> ObjectReader::LoadObject(const std::string path)
{
	ObjectLoader ObjectLoader;
	bool loadout = ObjectLoader.LoadFile(path);

	return ObjectLoader.LoadedVertices;
}

std::vector<mesh> ObjectReader::LoadMeshes(const std::string path)
{
	ObjectLoader ObjectLoader;
	bool loadout = ObjectLoader.LoadFile(path);

	return ObjectLoader.LoadedMeshes;
}

