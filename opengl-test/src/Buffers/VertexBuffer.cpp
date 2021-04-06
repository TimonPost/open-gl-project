#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(void* data, int size)
{
	GLCall(glGenBuffers(1, &_registerId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _registerId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &_registerId));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _registerId));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
