#pragma once

#include "../GlWrap.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>


#pragma once
class VertexArray : public GLRegisterable
{
public:
	VertexArray();

	void AddBuffer(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<VertexBufferLayout>& layout) const;

	void Bind() const override;
	void Unbind() const override;

	~VertexArray() override;
};
