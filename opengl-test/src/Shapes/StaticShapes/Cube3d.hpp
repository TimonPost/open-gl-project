#pragma once
#include "../ShapeBase.h"
#include "../VertexFormat.hpp"

class Cube3d : public ShapeBase
{
private:
	VertexFormat _positions[8];
	unsigned int _indices[36];
	GLint _uniform_mvp;
	glm::mat4 _mvp;
public:
	Cube3d(float width, float height, float depth) : ShapeBase("", "cube3dShader")
	{
		std::vector<VertexFormat> vertices = {
			// Front
			VertexFormat(glm::vec4(-width, -height, depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)),
			VertexFormat(glm::vec4(width, -height, depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)),
			VertexFormat(glm::vec4(width, height, depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)),
			VertexFormat(glm::vec4(-width, height, depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)),

			// Back
			VertexFormat(glm::vec4(-width, -height, -depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)),
			VertexFormat(glm::vec4(width, -height, -depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)),
			VertexFormat(glm::vec4(width, height, -depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)),
			VertexFormat(glm::vec4(-width, height, -depth, 1), glm::vec4(1.0f, 1.0f, 1.0, 1))
		};

		unsigned int indicies[]{
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};

		std::copy(std::begin(vertices), std::end(vertices), std::begin(_positions));
		std::copy(std::begin(indicies), std::end(indicies), std::begin(_indices));

		_size = (sizeof(VertexFormat) * vertices.size());

		WithBuffer(&vertices[0], _size);
		
		WithShader("res\\shaders\\Cube.shader");
		WithIndexBuffer(_indices, sizeof(_indices));

		_layout->AddFloat(4);
		_va->AddBuffer(_vb, _layout);

		_uniform_mvp = _shader->GetUniformLocation("mvp");
	}

	void ShapeBase::Draw(Graphics* graphics) override
	{
		auto* render = graphics->Render;
		
		_shader->SetUniformMatrix4fv("mvp", render->P() * render->V() * _model);
		
		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		GLCall(glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr));
	}

	virtual ~Cube3d()
	{
		delete[] _indices;
		delete[] _indices;
		delete[] _positions;
	}
};
