#pragma once
#include "ShapeBase.h"
#include "VertexformatObjectWithUV.hpp"
#include "../Resources/ObjectReader.h"

class ShadowObjectBase : public ShapeBase
{
public:

	ShadowObjectBase(ShadowObjectBase* toClone) : ShapeBase(toClone)
	{
	}

	ShadowObjectBase(std::string textureIdentifier, const std::string& objPath) :ShapeBase(
		std::move(textureIdentifier))
	{
		std::vector<VertexFormatObjectWithUV> buffer = ObjectReader::LoadObject(objPath);
		_size = sizeof(VertexFormatObjectWithUV) * buffer.size();

		WithBuffer(&buffer[0], _size);
		_layout->AddFloat(3);
		_layout->AddFloat(3);
		_layout->AddFloat(2);

		_va->AddBuffer(_vb, _layout);
	}

	virtual void Draw(Graphics* graphics) = 0;
};
