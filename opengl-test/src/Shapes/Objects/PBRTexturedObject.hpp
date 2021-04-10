#pragma once

#include <vector>

#include "../ShapeBase.h"
#include "../PBRTexturedObjectBase.hpp"
#include "../../Resources/ObjectReader.h"

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