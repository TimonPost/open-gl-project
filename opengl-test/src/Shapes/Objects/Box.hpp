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

