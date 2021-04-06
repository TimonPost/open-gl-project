#pragma once

#include "../ObjShapeBase.h"
#include "../../Resources/TexturePool.h"

class TeaPot : public ObjShapeBase
{
public:
	/// <summary>
	/// Create a new instance of a teapot by cloning and partially reusing the given shape.
	/// </summary>
	TeaPot(TeaPot* teaPot) : ObjShapeBase(teaPot)
	{
	}

	TeaPot() : ObjShapeBase("uvTemplateTexture", "objectShader", "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\teapot.obj")
	{
	}

	void ObjShapeBase::Draw(Graphics* graphics) override
	{
		auto* render = graphics->Render;
	
		auto* texture = TexturePool::Instance()->GetSimpleTextureById(TextureIdentifier);
		texture->Bind();

		_shader->SetUniformMatrix4fv("mv", render->V() * _model);
		_shader->SetUniformMatrix4fv("projection", render->P());

		glDrawArrays(GL_TRIANGLES, 0, _size);

		texture->Unbind();
	}

	virtual ~TeaPot() = default;
};
