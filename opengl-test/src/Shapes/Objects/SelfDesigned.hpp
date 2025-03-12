#pragma once
#include <string>
#include <GL/glew.h>
#include "../../Resources/MeshesLoader.hpp"

class SelfDesignedObject : public MeshLoader
{

public:
	SelfDesignedObject() : MeshLoader(ground_textureID, self_designed_MeshID)
	{
	}

	virtual ~SelfDesignedObject() = default;
};

