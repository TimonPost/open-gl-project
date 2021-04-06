#pragma once

#include "Resources/Shader.h"
#include "Resources/TexturePool.h"
#include "World/Renderer.h"
#include "World/Lights.hpp"

class Graphics
{
public:
	Renderer* Render;
	Shader* activeShader;
	
	std::vector<PointLight>* pointLights;
	DirectionalLight* directionalLight;
	SpotLight* spotLight;
	
	void ApplyLightsToShader(Shader* shader) const
	{	
		shader->SetUniform3fv("viewPos", Render->camera->position);
		
		for (unsigned int i = 0; i < pointLights->size(); i++)
		{
			PointLight* light = &pointLights->at(i);
			 shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].position", light->position);
			 shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].ambient", light->ambient);
			 shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].diffuse", light->diffuse);
			 shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].specular", light->specular);
			 shader->SetUniform1f("pointLights[" + std::to_string(i) + "].constant", light->constant);
			 shader->SetUniform1f("pointLights[" + std::to_string(i) + "].linear", light->linear);
			 shader->SetUniform1f("pointLights[" + std::to_string(i) + "].quadratic", light->quadratic);
		}
		
		// Set Directional Light

		shader->SetUniform3fv("dirLight.direction", directionalLight->direction);
		shader->SetUniform3fv("dirLight.ambient", directionalLight->ambient);
		shader->SetUniform3fv("dirLight.diffuse", directionalLight->diffuse);
		shader->SetUniform3fv("dirLight.specular", directionalLight->specular);

	}
};
