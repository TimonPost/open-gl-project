#pragma once

#include "../GlWrap.h"

#include <string>
#include <unordered_map>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../Buffers/GLRegisterable.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

enum class ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};


class Shader : GLRegisterable
{
private:
	std::string _filePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	
public:
	std::string Label;
	
	Shader(const std::string& filePath, std::string label);
	virtual ~Shader();

	void Bind() const override;
	void Unbind() const override;

	std::string Path() const;

	// Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform3fv(const std::string& name, glm::vec3 value);
	void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);
	int GetUniformLocation(const std::string& name);
	int GetAttributeLocation(const std::string& name) const;
private:
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filePath) const;
};
