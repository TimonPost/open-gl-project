#pragma once

#include "World.h"

class Game
{
private:
	static Game* instance;

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	
	Game();

public:
	std::shared_ptr<Renderer> render = std::make_shared<Renderer>();
	World world = World(render);

	void Tick();
	float DeltaTime() const;
	float LastFrame() const;
	
	/* Static access method. */
	static Game* Instance();
};
