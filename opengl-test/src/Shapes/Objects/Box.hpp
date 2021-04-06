#pragma once

#include "../ObjShapeBase.h"

class Box : public ObjShapeBase
{

public:
	Box() : ObjShapeBase("uvTemplateTexture", "objectShader", "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\box.obj")
	{
	}
	
	void ObjShapeBase::Draw(Graphics* graphics) override
	{
		auto* render = graphics->Render;

		ApplyShaderProperties();
		_shader->SetUniformMatrix4fv("mv", render->V() * _model);
		_shader->SetUniformMatrix4fv("projection", render->P());

		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~Box() = default;
};

