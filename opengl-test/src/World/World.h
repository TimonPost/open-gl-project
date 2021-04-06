#pragma once

#include <memory>
#include <vector>

#include "Lights.hpp"
#include "Renderer.h"
#include "../Shapes/ShapeBase.h"
#include "../Shapes/Objects/Box.hpp"
#include "../GlWrap.h"
#include "../Resources/Shader.h"
#include "../Buffers/FrameBuffer.h"
class World
{
private:
	std::vector<Box*> _lightCubes;

	std::vector<ShapeBase*> _pbrShapes;
	std::vector<ShapeBase*> _shadowShapes;
	
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
		for (int i = 0; i < pointLights.size(); i++)
		{
			auto* lightCube = new Box();
			lightCube->ambient_color = glm::vec3(1,1,1);		
			lightCube->RefreshShaderProperties();
			
			auto* lightData = &pointLights[i];
						
			lightCube->Scale(glm::vec3(0.5f, 0.5f, 0.5f));
			lightCube->Translate(lightData->position);		
			
			_lightCubes.push_back(lightCube);
		}

		shadowMap.Init();
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
	Camera* MainCamera() const;
	std::unique_ptr<Renderer>* Render();
	std::vector<ShapeBase*>* GetShapes();
	void DrawShapes();
	void RenderScene(Graphics* graphics);
	void RenderPBRShapes(Graphics* graphics);
	void RenderShadowShapes(Graphics* graphics);
};
