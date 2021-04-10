#pragma once

#include <vector>
#include <GL/glew.h>
#include "../GlWrap.h"

/// <summary>
/// Specifies the layout in a buffer.
/// </summary>
struct VertexLayoutElement
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

/// <summary>
/// Layout manager for the opengl buffer.
/// </summary>
class vertex_buffer_layout
{
	unsigned int _stride;
	std::vector<VertexLayoutElement> _elements;

public:
	vertex_buffer_layout() :
		_stride(0)
	{
	}

	/// <summary>
	/// Adds one or more floats to the layout.
	/// </summary>
	/// <param name="count"></param>
	void AddFloat(unsigned int count) { Push(GL_FLOAT, count, GL_FALSE); }

	/// <summary>
	/// Adds one or more integers to the layout.
	/// </summary>
	/// <param name="count"></param>
	void AddUnsignedInt(unsigned int count) { Push(GL_UNSIGNED_INT, count, GL_FALSE); }

	/// <summary>
	/// Adds one or more bytes to the layout.
	/// </summary>
	/// <param name="count"></param>
	void AddUnsignedByte(unsigned int count) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

	/// <summary>
	/// Gets the layout elements making up the layout.
	/// </summary>
	/// <param name="count"></param>
	std::vector<VertexLayoutElement> GetElements() const { return _elements; }
	
	unsigned int GetStride() const { return _stride; }

private:
	void Push(unsigned int type, unsigned int count, unsigned char normalized)
	{
		const struct VertexLayoutElement vbe = {type, count, normalized};
		_elements.push_back(vbe);
		_stride += count * VertexLayoutElement::GetSizeOfType(type);
	};
};
