#pragma once

#include "../ShapeBase.h"

const unsigned int extension = 3;
const unsigned int fragments = 400 * extension;

class Circle : public ShapeBase
{
private:
	float _positions[fragments];

	std::vector<glm::vec3> CreateCircleArray(float radius, float x, float y, unsigned int fragments) const
	{
		const float PI = 3.1415926f;

		std::vector<glm::vec3> result;

		for (float a = 0; a < 360; a += 360.0 / static_cast<float>(fragments))
		{
			float angle = (PI / 180) * a;
			result.push_back(glm::vec3(radius * cos(angle) + x, radius * sin(angle) + y, 0));
		}

		return result;
	}

public:
	Circle() : ShapeBase("", "baseShapeShader")
	{
		std::vector<glm::vec3> circlePoints = CreateCircleArray(1, 0, 0, fragments / extension);

		float points[fragments];

		unsigned int index = 0;

		for (int i = 0; i < fragments; i += 3)
		{
			glm::vec3 point = circlePoints[index];

			points[i] = point.x;
			points[i + 1] = point.y;
			points[i + 2] = point.z;

			index += 1;
		}

		std::copy(std::begin(points), std::end(points), std::begin(_positions));

		WithBuffer(_positions, sizeof(_positions));
		WithShader(ShaderIdentifier);

		_layout->AddFloat(3);
		_va->AddBuffer(_vb, _layout);
	}

	void ShapeBase::Draw(Graphics* graphics) override
	{
		glDrawArrays(GL_TRIANGLE_FAN, 2, fragments);
	}

	virtual ~Circle()
	{
		delete[] _positions;
	}
};
