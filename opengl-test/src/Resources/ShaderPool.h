#pragma once	

#include "Shader.h"

/// <summary>
/// Pool with loaded shaders that can be acquired by object instances.
/// This pool improves performance since shaders are not to be loaded multiple times.
/// </summary>
class ShaderPool
{
public:
	static ShaderPool* Instance();
	void AddShader(Shader* entry);

	/// <summary>
	/// Returns a shader with the given id.
	/// </summary>
	Shader* GetShaderById(std::string shaderId);

	~ShaderPool();
private:
	std::vector<Shader*> _shaders;
	
	static ShaderPool* instance;
	
	ShaderPool() {}
	ShaderPool(ShaderPool const&);
	ShaderPool& operator=(ShaderPool const&);
};