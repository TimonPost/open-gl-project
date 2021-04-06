#include "IndexBuffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	if (_count != 0)
	{
		GLCall(glGenBuffers(1, &_indexBufferId));
		IndexBuffer::Bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
		IndexBuffer::Unbind();
	}

	_count = count;
}

IndexBuffer::~IndexBuffer()
{
	if (_count != 0)
	{
		GLCall(glDeleteBuffers(1, &_indexBufferId));
	}
}

void IndexBuffer::Bind() const
{
	if (_count != 0)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId));
	}
}

void IndexBuffer::Unbind() const
{
	if (_count != 0)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}
