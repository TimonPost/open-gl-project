#pragma once

#include "GLRegisterable.h"
#include "../GlWrap.h"

class VertexBuffer : public GLRegisterable
{
public:
	VertexBuffer(void* data, int size);

	void Bind() const override;
	void Unbind() const override;

	~VertexBuffer() override;
};
