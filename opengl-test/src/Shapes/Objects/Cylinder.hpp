#pragma once

#include "../ShapeBase.h"
#include "../VertexFormatObj.hpp"
#include "../../Resources/ObjectReader.hpp"

using namespace std;

class Cylinder18 : public ShapeBase
{
private:
	glm::vec3 light_position, ambient_color, diffuse_color, specular;
	float power;
public:
	Cylinder18() : ShapeBase("", "objectNoTextureShader")
	{
		vector<VertexFormatObject> buffer = ObjReader::GetBuffer(
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\cylinder18.obj");
		_size = (sizeof(VertexFormatObject) * buffer.size());

		WithBuffer(&buffer[0], _size);
		WithShader(ShaderIdentifier);

		_layout->AddFloat(3);
		_layout->AddFloat(3);

		_va->AddBuffer(_vb, _layout);

		light_position = glm::vec3(4, 4, 4);
		ambient_color = glm::vec3(0.2, 0.2, 0.1);
		diffuse_color = glm::vec3(0.5, 0.5, 0.3);
		specular = glm::vec3(0.7, 0.7, 0.7);
		power = 1024;

		// Make uniform vars
		_shader->Bind();
		_shader->SetUniform3fv("light_pos", light_position);
		_shader->SetUniform3fv("mat_ambient", ambient_color);
		_shader->SetUniform3fv("mat_diffuse", diffuse_color);
		_shader->SetUniform3fv("mat_specular", specular);
		_shader->SetUniform1f("mat_power", power);
	}

	void ShapeBase::Draw(Graphics* graphics) override
	{
			auto* render = graphics->Render;
		
		_shader->SetUniformMatrix4fv("mv", render->V() * _model);
		_shader->SetUniformMatrix4fv("projection", render->P());

		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~Cylinder18() = default;
};
