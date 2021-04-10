#pragma once

#include "GLRegisterable.h"
#include "../GlWrap.h"

/// <summary>
/// Abstraction for the opengl vertex buffer.
/// </summary>
class VertexBuffer : public GLRegisterable
{
public:
	VertexBuffer(void* data, int size);

	void Bind() const override;
	void Unbind() const override;

	~VertexBuffer() override;
};
