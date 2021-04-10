#pragma once

#include "../ObjShapeBase.h"
#include "../ShadowObjectBase.hpp"

class ColoredBox : public ObjShapeBase
{

public:
	ColoredBox() : ObjShapeBase("", cube_meshID)
	{
	}

	void ObjShapeBase::Draw(Graphics* graphics) override
	{
		SetUniforms(graphics->activeShader);

		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~ColoredBox() = default;
};

class Box : public ObjShapeBase
{

public:
	Box(std::string textureIdentifier) : ObjShapeBase(textureIdentifier, cube_meshID)
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
	CubeShadowObject(std::string textureIdentifier) : ShadowObjectBase(textureIdentifier, "C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\objs\\box.obj")
	{
	}

	void Draw(Graphics* graphics) override
	{
		graphics->activeShader->SetUniformMatrix4fv("model", _model);
		glDrawArrays(GL_TRIANGLES, 0, _size);
	}
};
