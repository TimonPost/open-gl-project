#pragma once

#include "../ShapeBase.h"
#include "../VertexFormat.hpp"


class Triangle final : public ShapeBase
{
private:
	VertexFormat _positions[3];
	unsigned int _indices[3];

public:
	Triangle() : ShapeBase("", "baseShapeShader")
	{
		VertexFormat vertices[] = {
			VertexFormat(glm::vec4(0.0f, 0.5f, 0, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)), // 1: top center Red
			VertexFormat(glm::vec4(0.5f, -0.5f, 0, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)), // 2: right bottom Green
			VertexFormat(glm::vec4(-0.5f, -0.5f, 0, 1), glm::vec4(1.0f, 1.0f, 1.0, 1)) // 3: left bottom Blue
		};

		unsigned int indicies[]{
			0, 1, 2
		};

		std::copy(std::begin(vertices), std::end(vertices), std::begin(_positions));
		std::copy(std::begin(indicies), std::end(indicies), std::begin(_indices));

		WithBuffer(_positions, sizeof(_positions));
		WithShader(ShaderIdentifier);
		WithIndexBuffer(_indices, sizeof(_indices));

		_layout->AddFloat(4);
		_layout->AddFloat(4);
		_va->AddBuffer(_vb, _layout);
	}

	void ShapeBase::Draw(Graphics* graphics) override
	{		
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
	}

	virtual ~Triangle()
	{
		delete[] _indices;
		delete[] _positions;
	}
};
