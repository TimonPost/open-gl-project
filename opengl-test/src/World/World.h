#pragma once

#include <memory>
#include <vector>

#include "Lights.hpp"
#include "Renderer.h"
#include "../Shapes/ShapeBase.h"
#include "../Shapes/ObjShapeBase.h"
#include "../Shapes/Objects/Box.hpp"
#include "../Resources/Shader.h"
#include "../Buffers/FrameBuffer.h"

class World
{
private:
	std::vector<ShapeBase*> _pbrShapes;
	std::vector<ShapeBase*> _shadowShapes;
	std::vector<ShapeBase*> _objectShapes;
	
	std::shared_ptr<Renderer> _render;
	
	DirectionalLight directionalLight;
	SpotLight spotLight;

public:
	ShadowMapFBO shadowMap;
	
	std::vector<PointLight> pointLights = std::vector<PointLight>();
	
	World(std::shared_ptr<Renderer>& render);
		
	void AddPointLight(PointLight light)
	{
		pointLights.push_back(light);
	}

	void Initialize()
	{
		const glm::vec3 lightSize = glm::vec3(0.5f, 0.5f, 0.5f);
		const glm::vec3 lightColor = glm::vec3(0.5f, 0.5f, 0.5f);
		
		// Add point lights to the scene as physical objects for debugging purposes.
		for (auto& pointLight : pointLights)
		{
			auto* lightCube = new Box(uvTemplateTexture);
			lightCube->ambient_color = lightColor;
			lightCube->Scale(lightSize);
			lightCube->Translate(pointLight.position);						
			
			_objectShapes.push_back(lightCube);
		}

		// Add directional light to the scene as physical objects for debugging purposes.
		auto* lightCube = new Box(uvTemplateTexture);
		lightCube->ambient_color = glm::vec3(0.2f, 1.0f, 0.2f);
		lightCube->Scale(lightSize);
		lightCube->Translate(_render->LightPosition());
		_objectShapes.push_back(lightCube);
		
		shadowMap.Init();
	}

	Renderer* Render()
	{
		return _render.get();
	}
	
	void SetSpotLight(SpotLight light)
	{
		spotLight = light;
	}

	void SetDirectionalLight(DirectionalLight light)
	{
		directionalLight = light;
	}
			
	void AddBPRShape(ShapeBase& shape);
	void AddShadowShape(ShapeBase& shape);
	void AddObjectShape(ShapeBase& shape);

	Camera* MainCamera() const;
	void DrawShapes();
	void DrawObjectShapes(Graphics graphics);
	void RenderShadowScene(Graphics* graphics);
	void RenderPBRShapes(Graphics* graphics);
	void RenderShadowShapes(Graphics* graphics);
};
