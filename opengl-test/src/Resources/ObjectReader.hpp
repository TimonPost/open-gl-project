#pragma once
#include <string>
#include <vector>

#include "objloader.h"
#include "../../objectLoader.h"
#include "../Shapes/VertexFormatObj.hpp"

class ObjReader
{
public:
	static std::vector<VertexFormatObject> GetBuffer(const std::string& path)
	{
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;

		bool res = loadOBJ(path.c_str(), vertices, uvs, normals);

		std::vector<VertexFormatObject> vertexes = std::vector<VertexFormatObject>();
		for (int i = 0; i < vertices.size(); i++)
		{
			vertexes.emplace_back(vertices[i], normals[i]);
		}

		return vertexes;
	}

	static std::vector<VertexFormatObjectWithUV> GetBufferWithUv(const std::string path)
	{
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;

		bool res = loadOBJ(path.c_str(), vertices, uvs, normals);

		std::vector<VertexFormatObjectWithUV> vertexes = std::vector<VertexFormatObjectWithUV>();
		for (int i = 0; i < vertices.size(); i++)
		{
			vertexes.emplace_back(vertices[i], normals[i], uvs[i]);
		}

		return vertexes;
	}

	static std::vector<VertexFormatObjectWithUV> LoadWithLib(const std::string path)
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
