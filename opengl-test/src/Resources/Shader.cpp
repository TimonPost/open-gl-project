#include "Shader.h"

#include <GL/glew.h>

#include <utility>

Shader::Shader(const std::string& filePath, std::string label)
{
	const shader_program_source source = ParseShader(filePath);
	_registerId = CreateShader(source.VertexSource, source.FragmentSource);
	_filePath = filePath;
	Label = std::move(label);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(_registerId))
}

void Shader::Bind() const
{
	GLCall(glUseProgram(_registerId))
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0))
}

std::string Shader::Path() const
{
	return _filePath;
}

// Set uniforms
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform3fv(const std::string& name, glm::vec3 value)
{
	glUniform3fv(GetUniformLocation(name), 1, value_ptr(value));
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(value));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
	{
		return uniformLocationCache[name];
	}

	int location;
	GLCall(location = glGetUniformLocation(Id(), name.c_str()));

	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "'doesnt exist!" << std::endl;
	}
	uniformLocationCache[name] = location;
	return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id;
	GLCall(id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int lenght;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
		char* message = static_cast<char*>(alloca(lenght * sizeof(char)));
		GLCall(glGetShaderInfoLog(id, lenght, &lenght, message));

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader" <<
			std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(0));

		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program;
	GLCall(program = glCreateProgram());
	const unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

shader_program_source Shader::ParseShader(const std::string& filePath) const
{
	std::ifstream stream(filePath);

	std::string line;
	std::stringstream ss[2];
	shader_type type = shader_type::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = shader_type::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = shader_type::FRAGMENT;
			}
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}

	return shader_program_source{ss[0].str(), ss[1].str()};
}

int Shader::GetAttributeLocation(const std::string& name) const
{
	return glGetAttribLocation(Id(), name.c_str());
}
