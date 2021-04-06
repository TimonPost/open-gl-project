#pragma once

#include "../ObjShapeBase.h"
#include "../../Graphics.h"
#include "../../Resources/TexturePool.h"

class PBRTexturedBox : public PBRTexturedObjectBase
{

public:
	PBRTexturedBox(const std::string textureId) : PBRTexturedObjectBase(
		textureId,
		"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\ojbs\\box.obj")
	{
	}

	void PBRTexturedObjectBase::Draw(Graphics* graphics) override
	{		
		graphics->activeShader->SetUniformMatrix4fv("model", _model);
		
		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~PBRTexturedBox() = default;
};

class PBRTexturedObject : public PBRTexturedObjectBase
{

public:
	PBRTexturedObject(const std::string textureId, const std::string objectPath) : PBRTexturedObjectBase(textureId, objectPath)
	{
	}

	void PBRTexturedObjectBase::Draw(Graphics* graphics) override
	{		
		graphics->activeShader->SetUniformMatrix4fv("model", _model); 

		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~PBRTexturedObject() = default;
};

