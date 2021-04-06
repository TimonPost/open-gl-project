#pragma once;

#include <GL/gl.h>


#include "PBRTexturedBox.hpp"
#include "Box.hpp"
#include "../../Graphics.h"

class BoxMetalic : public PBRTexturedBox
{

public:

	BoxMetalic(std::string textureId) : PBRTexturedBox(textureId, "pbrShader")
	{
	}

	virtual ~BoxMetalic() = default;
};

