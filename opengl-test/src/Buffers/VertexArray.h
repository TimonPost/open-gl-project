#pragma once

#include "../GlWrap.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

/// <summary>
/// Abstraction for the opengl vertex array.
/// </summary>
class VertexArray : public GLRegisterable
{
public:
	VertexArray();

	/// <summary>
	/// Adds a buffer and a layout to this vertex array.
	/// </summary>
	/// <param name="vb"></param>
	/// <param name="layout"></param>
	void AddBuffer(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<vertex_buffer_layout>& layout) const;

	void Bind() const override;
	void Unbind() const override;

	~VertexArray() override;
};
