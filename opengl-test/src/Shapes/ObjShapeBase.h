#pragma once

#include "ShapeBase.h"

#include "VertexFormatObj.hpp"
#include "../Resources/ObjectReader.hpp"

#include "../../objectLoader.h"

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

		// Make uniform vars
		RefreshShaderProperties();
	}

	ObjShapeBase(std::string textureIdentifier, std::string shaderIdentifier, const std::string& objPath) :ShapeBase(textureIdentifier, shaderIdentifier)
	{		
		Loader loader;
		
		std::vector<VertexFormatObjectWithUV> buffer = ObjReader::GetBufferWithUv(objPath);
		_size = (sizeof(VertexFormatObjectWithUV) * buffer.size());

		WithBuffer(&buffer[0], _size);
		WithShader(ShaderIdentifier);

		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);

		light_position = glm::vec3(4, 4, 4);
		ambient_color = glm::vec3(0.2, 0.2, 0.1);
		diffuse_color = glm::vec3(0.5, 0.5, 0.3);
		specular = glm::vec3(0.7, 0.7, 0.7);
		power = 1024;

		RefreshShaderProperties();
	}

	void RefreshShaderProperties() const
	{
		_shader->Bind();
		ApplyShaderProperties();
		_shader->Unbind();
	}

	void ApplyShaderProperties() const
	{
		_shader->SetUniform3fv("light_pos", light_position);
		_shader->SetUniform3fv("mat_ambient", ambient_color);
		_shader->SetUniform3fv("mat_specular", specular);
		_shader->SetUniform1f("mat_power", power);
	}

	virtual void Draw(Graphics* graphics)  = 0;
};

class PBRTexturedObjectBase : public ShapeBase
{
public:
	
	PBRTexturedObjectBase(PBRTexturedObjectBase* toClone) : ShapeBase(toClone)
	{
		TextureIdentifier = toClone->TextureIdentifier;
	}

	PBRTexturedObjectBase(std::string textureIdentifier, std::string shaderIdentifier, const std::string& objPath) :ShapeBase(
		std::move(textureIdentifier), std::move(shaderIdentifier))
	{	
		std::vector<VertexFormatObjectWithUV> buffer = ObjReader::LoadWithLib(objPath);
		_size = sizeof(VertexFormatObjectWithUV) * buffer.size();

		WithBuffer(&buffer[0], _size);
		WithShader(ShaderIdentifier);

		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);
	}

	virtual void Draw(Graphics* graphics) = 0;
};



class SpecularTexturedObjectBase : public ShapeBase
{
public:

	SpecularTexturedObjectBase(PBRTexturedObjectBase* toClone) : ShapeBase(toClone)
	{
	}

	SpecularTexturedObjectBase(std::string textureIdentifier, std::string shaderIdentifier, const std::string& objPath) :ShapeBase(
		std::move(textureIdentifier), std::move(shaderIdentifier))
	{
		Loader loader;

		std::vector<VertexFormatObjectWithUV> buffer = ObjReader::GetBufferWithUv(objPath);
		_size = sizeof(VertexFormatObjectWithUV) * buffer.size();

		WithBuffer(&buffer[0], _size);
		WithShader(ShaderIdentifier);

		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);
	}

	virtual void Draw(Graphics* graphics) = 0;
};
