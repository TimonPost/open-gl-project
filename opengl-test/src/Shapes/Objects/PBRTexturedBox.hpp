#pragma once

#include "../PBRTexturedObjectBase.hpp"
#include "../../Graphics.h"

class PBRTexturedBox : public PBRTexturedObjectBase
{

public:
	PBRTexturedBox(const std::string textureId) : PBRTexturedObjectBase(
		textureId,
		"C:\\Users\\Timon\\source\\repos\\opengl-test\\opengl-test\\res\\objs\\box.obj")
	{
	}

	void PBRTexturedObjectBase::Draw(Graphics* graphics) override
	{
		graphics->activeShader->SetUniformMatrix4fv("model", _model);

		glDrawArrays(GL_TRIANGLES, 0, _size);
	}

	virtual ~PBRTexturedBox() = default;
};

