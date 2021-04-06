#pragma once

#include "texture.hpp"
#include "../Buffers/GLRegisterable.h"

class SimpleTextureEntry : public GLRegisterable
{
	const std::string diffuseMapPath;
	const std::string specularMapPath;

public:
	std::string Label;

	SimpleTextureEntry(std::string label, std::string diffuseMapPath)
	{
		_registerId = loadTexture(diffuseMapPath.c_str());
		Label = label;
	}

	void Bind() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Id());
	}

	void Unbind() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

class ObjectTextureEntry : public GLRegisterable
{
	unsigned int _diffuseMapPath;
	unsigned int _specularMapPath;

public:
	std::string Label;

	ObjectTextureEntry(std::string label, std::string diffuseMapPath, std::string specularMapPath)
	{
		_diffuseMapPath = loadTexture(diffuseMapPath.c_str());
		_specularMapPath = loadTexture(specularMapPath.c_str());
		
		Label = label;
	}

	void Bind() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _diffuseMapPath);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _specularMapPath);
	}

	void Unbind() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

class PBRTextureEntry : public GLRegisterable
{
public:
	std::string Label;

	unsigned int Albedo;
	unsigned int Normal;
	unsigned int Metallic;
	unsigned int Roughness;
	unsigned int AO;

	PBRTextureEntry(std::string label, std::string albedoPath, std::string normalPath, std::string metallicPath, std::string roughnessPath, std::string aoPath)
	{
		Albedo = loadTexture(albedoPath.c_str());
		Normal = loadTexture(normalPath.c_str());
		Metallic = loadTexture(metallicPath.c_str());
		Roughness = loadTexture(roughnessPath.c_str());
		AO = loadTexture(aoPath.c_str());
		Label = label;
	}

	void Bind() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Albedo);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Normal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, Metallic);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, Roughness);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, AO);
	}

	void Unbind() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};
