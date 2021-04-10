#include "ShaderPool.h"

#include <string>

ShaderPool::ShaderPool(ShaderPool const&)
{
}

ShaderPool* ShaderPool::instance = 0;

ShaderPool* ShaderPool::Instance()
{
	if (instance == 0)
	{
		instance = new ShaderPool();
	}

	return instance;
}

void ShaderPool::AddShader(Shader* entry)
{
	_shaders.push_back(entry);
}

Shader* ShaderPool::GetShaderById(const std::string shaderId)
{
	for (auto& pbr_texture : _shaders)
	{
		if (pbr_texture->Label == shaderId)
			return pbr_texture;
	}

	throw "Shader Could not be found";
}