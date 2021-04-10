#pragma once

#include "GLRegisterable.h"

#include "../GlWrap.h"

/// <summary>
/// Abstraction for the opengl index buffer.
/// </summary>
class IndexBuffer final : public GLRegisterable
{
private:
	unsigned int _indexBufferId{};
	unsigned int _count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);

	/// <summary>
	/// Return the number of indexes.
	/// </summary>
	/// <returns></returns>
	unsigned int GetCount() const { return _count; }
		
	void Bind() const override;
	void Unbind() const override;
	
	~IndexBuffer() override;
};
