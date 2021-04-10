#pragma once

#include "ShapeBase.h"

#include "VertexFormatObj.hpp"
#include "../Resources/objectLoader.h"
#include "../Resources/ObjectReader.h"

class ObjShapeBase : public ShapeBase
{
public:
	glm::vec3 light_position, ambient_color, diffuse_color, specular;
	float power;
	
	unsigned int diffuseMap;
	unsigned int specularMap;

public:
	ObjShapeBase(ObjShapeBase* toClone) : ShapeBase(toClone)
	{
		diffuseMap = toClone->diffuseMap;

		light_position = toClone->light_position;
		ambient_color = toClone->ambient_color;
		diffuse_color = toClone->diffuse_color;
		specular = toClone->specular;
		power = toClone->power;
	}

	ObjShapeBase(std::string textureIdentifier, const std::string& objPath) :ShapeBase(textureIdentifier)
	{
		MeshPool* pool = MeshPool::Instance();

		vector<Mesh*> meshes = pool->GetMeshesById(objPath);
		Mesh* mesh = meshes[0];
		
		_size = (sizeof(VertexFormatObjectWithUV) * mesh->Vertices.size());

		WithBuffer(&mesh->Vertices[0], _size);

		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);

		light_position = glm::vec3(4, 4, 4);
		ambient_color = glm::vec3(0.2, 0.2, 0.1);
		diffuse_color = glm::vec3(0.5, 0.5, 0.3);
		specular = glm::vec3(0.7, 0.7, 0.7);
		power = 1024;
	}

	void SetUniforms(Shader* shader)
	{
		shader->SetUniformMatrix4fv("model", _model);
		shader->SetUniform3fv("light_pos", light_position);
		shader->SetUniform3fv("mat_ambient", ambient_color);
		shader->SetUniform3fv("mat_specular", specular);
		shader->SetUniform1f("mat_power", power);
	}
	
	virtual void Draw(Graphics* graphics)  = 0;
};

class PBRTexturedObjectBase : public ShapeBase
{
public:

	PBRTexturedObjectBase(PBRTexturedObjectBase* toClone) : ShapeBase(toClone)
	{
	}

	PBRTexturedObjectBase(std::string textureIdentifier, const std::string& objPath) :ShapeBase(
		std::move(textureIdentifier))
	{
		std::vector<VertexFormatObjectWithUV> buffer = ObjectReader::LoadObject(objPath);
		_size = sizeof(VertexFormatObjectWithUV) * buffer.size();

		WithBuffer(&buffer[0], _size);

		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);
	}

	virtual void Draw(Graphics* graphics) = 0;
};


class ShadowObjectBase : public ShapeBase
{
public:

	ShadowObjectBase(PBRTexturedObjectBase* toClone) : ShapeBase(toClone)
	{
	}

	ShadowObjectBase(std::string textureIdentifier, const std::string& objPath) :ShapeBase(
		std::move(textureIdentifier))
	{
		std::vector<VertexFormatObjectWithUV> buffer = ObjectReader::LoadObject(objPath);
		_size = sizeof(VertexFormatObjectWithUV) * buffer.size();

		WithBuffer(&buffer[0], _size);
		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);
	}
	
	virtual void Draw(Graphics* graphics) = 0;
};