#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &_registerId));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &_registerId));
}

void VertexArray::AddBuffer(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<VertexBufferLayout>& layout) const
{
	Bind();
	vb->Bind();

	const auto& elements = layout->GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		GLCall(
			glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout->GetStride(), (const void *)offset));
		GLCall(glEnableVertexAttribArray(i));

		offset += element.count * sizeof(element.type);
	}

	vb->Unbind();
	Unbind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(_registerId));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
