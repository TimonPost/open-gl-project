#pragma once

#include <geometric.hpp>
#include <vec3.hpp>

// Namespace: Math
//
// Description: The namespace that holds all of the math
//	functions need for OBJL
namespace math
{
	// glm::vec3 Magnitude Calculation
	inline float MagnitudeV3(const glm::vec3 in)
	{
		return (sqrtf(powf(in.x, 2) + powf(in.y, 2) + powf(in.z, 2)));
	}

	// Angle between 2 glm::vec3 Objects
	inline float AngleBetweenV3(const glm::vec3 a, const glm::vec3 b)
	{
		float angle = glm::dot(a, b);
		angle /= (MagnitudeV3(a) * MagnitudeV3(b));
		return angle = acosf(angle);
	}

	// Projection Calculation of a onto b
	inline glm::vec3 ProjV3(const glm::vec3 a, const glm::vec3 b)
	{
		glm::vec3 bn = b / MagnitudeV3(b);
		return bn * glm::dot(a, bn);
	}
}