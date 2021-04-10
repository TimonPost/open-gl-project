#pragma once

#include <memory>
#include <vector>

#include "Lights.hpp"
#include "Renderer.h"
#include "../Shapes/ShapeBase.h"
#include "../Shapes/ObjShapeBase.h"
#include "../Shapes/Objects/Box.hpp"
#include "../Resources/Shader.h"
#include "../Resources/TexturePool.h"
#include "../Buffers/ShadowMap.h"

/// <summary>
/// The game world in which the game state is maintained.
/// </summary>
class GameWorld
{
	std::vector<ShapeBase*> _pbrShapes;
	std::vector<ShapeBase*> _shadowShapes;
	std::vector<ShapeBase*> _objectShapes;

	std::vector<ShapeBase*> _debugLights;
	
	std::shared_ptr<Renderer> _render;
	
	DirectionalLight directionalLight;
	SpotLight spotLight;

	ShadowMap shadowMap;
	std::vector<PointLight> pointLights = std::vector<PointLight>();

	void DrawObjectShapes(Graphics* graphics);
	void RenderShadowScene(Graphics* graphics);
	void RenderPBRShapes(Graphics* graphics);
	void RenderShadowShapes(Graphics* graphics);

public:
	GameWorld(std::shared_ptr<Renderer>& render);

	/// <summary>
	/// Adds a point light to the world.
	/// </summary>
	/// <param name="light"></param>
	void AddPointLight(PointLight light)
	{
		pointLights.push_back(light);
	}

	/// <summary>
	/// Initializes some world state required for the game to be able to run.
	/// </summary>
	void Initialize();

	/// <summary>
	/// Returns the game render instance.
	/// </summary>
	/// <returns></returns>
	Renderer* Render() const
	{
		return _render.get();
	}

	/// <summary>
	/// returns the main camera of the game world.
	/// </summary>
	/// <returns></returns>
	Camera* MainCamera() const;
	
	/// <summary>
	/// Sets the directional light for the scene.
	/// </summary>
	/// <param name="light"></param>
	void SetDirectionalLight(DirectionalLight light)
	{
		directionalLight = light;
	}

	/// <summary>
	/// Adds a physical based rendered shape to the game world.
	/// </summary>
	/// <param name="shape"></param>
	void AddBPRShape(ShapeBase& shape);
	
	/// <summary>
	/// Adds a shadow shape to the game world.
	/// This shape is capable of casting shadows and render shadows on its surface.
	/// </summary>
	/// <param name="shape"></param>
	void AddShadowShape(ShapeBase& shape);
	
	/// <summary>
	/// Adds a simple object shape to the game world.
	/// </summary>
	/// <param name="shape"></param>
	void AddObjectShape(ShapeBase& shape);

	/// <summary>
	/// Render the game world to the screen.
	/// </summary>
	void Render();
	void DrawDebugLights(Graphics* graphics);
};
