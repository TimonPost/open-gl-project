#include "Game.h"

Game* Game::instance = 0;

Game::Game()
= default;

void Game::Tick()
{
	const float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	world.Render();
}

float Game::DeltaTime() const
{
	return deltaTime;
}

float Game::LastFrame() const
{
	return lastFrame;
}

Game* Game::Instance()
{
	if (instance == 0)
	{
		instance = new Game();
	}

	ShaderPool::Instance();
	
	return instance;
}

