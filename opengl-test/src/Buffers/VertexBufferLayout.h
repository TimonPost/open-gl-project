#pragma once

#include <vector>
#include <GL/glew.h>
#include "../GlWrap.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
		default: Assert(false);
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	unsigned int _stride;
	std::vector<VertexBufferElement> _elements;

public:
	VertexBufferLayout() :
		_stride(0)
	{
	}

	void AddFloat(unsigned int count) { Push(GL_FLOAT, count, GL_FALSE); }
	void AddUnsignedInt(unsigned int count) { Push(GL_UNSIGNED_INT, count, GL_FALSE); }
	void AddUnsignedByte(unsigned int count) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

	std::vector<VertexBufferElement> GetElements() const { return _elements; };
	unsigned int GetStride() const { return _stride; };

private:
	void Push(unsigned int type, unsigned int count, unsigned char normalized)
	{
		const struct VertexBufferElement vbe = {type, count, normalized};
		_elements.push_back(vbe);
		_stride += count * VertexBufferElement::GetSizeOfType(type);
	};
};
