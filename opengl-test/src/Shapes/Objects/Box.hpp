#pragma once

#include "../ObjShapeBase.h"

class Box : public ObjShapeBase
{

public:
	Box(string textureIdentifier) : ObjShapeBase(textureIdentifier, cube_meshID)
	{	
	}
	
	void ObjShapeBase::Draw(Graphics* graphics) override
	{		
		SetUniforms(graphics->activeShader);

		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~Box() = default;
};


class CubeShadowObject : public ShadowObjectBase
{
public:
	CubeShadowObject(string textureIdentifier) : ShadowObjectBase(textureIdentifier, "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\box.obj")
	{
	}

	void Draw(Graphics* graphics) override
	{
		graphics->activeShader->SetUniformMatrix4fv("model", _model);
		glDrawArrays(GL_TRIANGLES, 0, _size);
	}
};
