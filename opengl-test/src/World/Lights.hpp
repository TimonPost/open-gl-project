#pragma once

#include <trigonometric.hpp>
#include <vec3.hpp>

class PointLight
{
public:
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	PointLight()
	{
		position = glm::vec3(0.05f, 0.05f, 0.05f);
		diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);
		constant = 1.0;
		linear = 0.09;
		quadratic = 0.032;
	}
};

class DirectionalLight
{
public:
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	DirectionalLight()
	{
		direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		ambient = glm::vec3(0.5f, 0.5f, 0.5f);
		diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		specular = glm::vec3(0.5f, 0.5f, 0.5f);
	}
};

class SpotLight
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	SpotLight()
	{
		direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);

		constant = 1.0;
		linear = 0.09f;
		quadratic = 0.032f;

		cutOff = glm::cos(glm::radians(12.5f));
		outerCutOff = glm::cos(glm::radians(15.0f));
	}
};