#pragma once	

#include "Shader.h"

using namespace  std;

class ShaderPool
{
public:
	std::vector<Shader*> Shaders;
	
	ShaderPool(ShaderPool const&);
	ShaderPool& operator=(ShaderPool const&);

	static ShaderPool* Instance();
	void AddShader(Shader* entry);

	Shader* GetShaderById(std::string shaderId);
	ShaderPool() {}
private:
	static ShaderPool* instance;
	
	//ShaderPool() {}
};