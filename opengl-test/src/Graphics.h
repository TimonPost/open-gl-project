#pragma once

#include "Resources/Shader.h"
#include "Resources/TexturePool.h"
#include "World/Renderer.h"
#include "World/Lights.hpp"

class Graphics
{
public:
	Renderer* Render;

	std::vector<PointLight>* pointLights;
	DirectionalLight* directionalLight;
	SpotLight* spotLight;
	
	void ApplyLightsToShader(Shader* shader) const
	{
		// spotLight->direction = Render->camera->Front;
		// spotLight->position = Render->camera->position;
		//
		// shader->SetUniform3fv("viewPos", Render->camera->position);
		
		for (unsigned int i = 0; i < pointLights->size(); i++)
		{
			PointLight* light = &pointLights->at(i);
			 shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].position", light->position);
			 // shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].ambient", light->ambient);
			 // shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].diffuse", light->diffuse);
			 // shader->SetUniform3fv("pointLights[" + std::to_string(i) + "].specular", light->specular);
			 // shader->SetUniform1f("pointLights[" + std::to_string(i) + "].constant", light->constant);
			 // shader->SetUniform1f("pointLights[" + std::to_string(i) + "].linear", light->linear);
			 // shader->SetUniform1f("pointLights[" + std::to_string(i) + "].quadratic", light->quadratic);
		}

		// Set Spotlight

		//shader->SetUniform3fv("spotLight.position", spotLight->position);
		//shader->SetUniform3fv("spotLight.direction", spotLight->direction);

		//shader->SetUniform3fv("spotLight.ambient", spotLight->ambient);
		//shader->SetUniform3fv("spotLight.diffuse", spotLight->diffuse);
		//shader->SetUniform3fv("spotLight.specular", spotLight->specular);

		//shader->SetUniform1f("spotLight.constant", spotLight->constant);
		//shader->SetUniform1f("spotLight.linear", spotLight->linear);
		//shader->SetUniform1f("spotLight.quadratic", spotLight->quadratic);

		//shader->SetUniform1f("spotLight.cutOff", spotLight->cutOff);
		//shader->SetUniform1f("spotLight.outerCutOff", spotLight->outerCutOff);

		// Set Directional Light

		// shader->SetUniform3fv("dirLight.direction", directionalLight->direction);
		// shader->SetUniform3fv("dirLight.ambient", directionalLight->ambient);
		// shader->SetUniform3fv("dirLight.diffuse", directionalLight->diffuse);
		// shader->SetUniform3fv("dirLight.specular", directionalLight->specular);

		// If present set map index
		shader->SetUniform1i("albedoMap", 0);
		shader->SetUniform1i("normalMap", 1);
		shader->SetUniform1i("metallicMap", 2);
		shader->SetUniform1i("roughnessMap", 3);
		shader->SetUniform1i("aoMap", 4);
		shader->SetUniform1i("shadowMap", 5);		
		
		// shader->SetUniform1i("diffuseTexture", 0);

	}
};
