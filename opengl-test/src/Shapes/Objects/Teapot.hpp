#pragma once

#include "../ObjShapeBase.h"

class TeaPot : public ObjShapeBase
{
public:
	/// <summary>
	/// Create a new instance of a teapot by cloning and partially reusing the given shape.
	/// </summary>
	TeaPot(TeaPot* teaPot) : ObjShapeBase(teaPot)
	{
	}

	TeaPot() : ObjShapeBase("uvTemplateTexture", "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\teapot.obj")
	{
	}

	void ObjShapeBase::Draw(Graphics* graphics) override
	{
		SetUniforms(graphics->activeShader);
		
		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~TeaPot() = default;
};
