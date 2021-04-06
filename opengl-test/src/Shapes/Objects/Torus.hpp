#pragma once

#include "../ShapeBase.h"
#include "../VertexFormatObj.hpp"
#include "../../Resources/ObjectReader.hpp"

using namespace std;

class Torus : public ShapeBase
{
public:
	Torus() : ShapeBase("", "objectNoTextureShader")
	{
		vector<VertexFormatObject> buffer = ObjReader::GetBuffer(
			"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\torus.obj");
		_size = (sizeof(VertexFormatObject) * buffer.size());

		WithBuffer(&buffer[0], _size);
		WithShader(ShaderIdentifier);

		_layout->AddFloat(3);
		_layout->AddFloat(3);

		_va->AddBuffer(_vb, _layout);
	}

	void ShapeBase::Draw(Graphics* graphics) override
	{
		auto* render = graphics->Render;

		_shader->SetUniformMatrix4fv("mv", render->M() * _model);
		_shader->SetUniformMatrix4fv("projection", render->P());

		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~Torus() = default;
};
