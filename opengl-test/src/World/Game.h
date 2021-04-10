#pragma once

#include "GameWorld.h"

/// <summary>
/// The main game entry.
/// </summary>
class Game
{
	static Game* instance;

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	
	Game();

public:
	std::shared_ptr<Renderer> render = std::make_shared<Renderer>();
	GameWorld world = GameWorld(render);

	void Tick();
	float DeltaTime() const;
	float LastFrame() const;
	
	/* Static access method. */
	static Game* Instance();
};
