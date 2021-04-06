#pragma once
#include <string>
#include <vector>

#include "objloader.h"
#include "../../objectLoader.h"
#include "../Shapes/VertexFormatObj.hpp"

class ObjReader
{
public:
	static std::vector<VertexFormatObjectWithUV> LoadObject(const std::string path)
	{
		Loader Loader;
		bool loadout = Loader.LoadFile(path);

		std::vector<VertexFormatObjectWithUV> vertexes = std::vector<VertexFormatObjectWithUV>();
		for (auto& vertex : Loader.LoadedVertices)
		{
			vertexes.push_back(VertexFormatObjectWithUV(vertex.Position, vertex.Normal, vertex.TextureCoordinate));
		}
				
		return vertexes;
	}
	
	static std::vector<Mesh> LoadMeshes(const std::string path)
	{
		Loader Loader;		
		bool loadout = Loader.LoadFile(path);
		
		return Loader.LoadedMeshes;
	}
	
	
	~ObjReader() = default;
};
