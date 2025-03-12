#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include <gtc/matrix_transform.hpp>

#include <fstream>
#include <future>
#include <thread>

#include "GlWrap.h"
#include "Resources/WorldLoader.hpp"
#include "Resources/Shader.h"
#include "World/Renderer.h"
#include "World/GameWindow.h"

#include "World/GameWorld.h"

#include "Resources/TexturePool.cpp"
#include "Vendor/imgui_internal.h"
#include "World/Game.h"

// camera
float lastX = 400, lastY = 300;
float yaw = -90, pitch = 0;
bool firstMouse = true;

GameWindow window;

// Opgengl window resize callback
void WindowSizeCallback(GLFWwindow* glfWindow, int width, int height)
{
	window.Resize();
}

// Opgengl mouse scroll callback
void ScrollBack(GLFWwindow* glfWindow, double xoffset, double yoffset)
{
	Camera* camera = Game::Instance()->world.MainCamera();
	camera->ProcessMouseScroll(yoffset);
}

// Opengl keyboard callback
void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	auto* game = Game::Instance();
	Camera* camera = game->world.MainCamera();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, game->DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, game->DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, game->DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, game->DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		camera->ToggleMovementMode();
	}
	
}

// Opengl mouse callback
void MouseCallback(GLFWwindow* w, double xPos, double yPos)
{
	const int button = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT);
	
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}


	const float xoffset = xPos - lastX;
	const float yoffset = lastY - yPos; // reversed since y-coordinates go from bottom to top

	lastX = xPos;
	lastY = yPos;

	Camera* camera = Game::Instance()->world.MainCamera();
	camera->ProcessMouseMovement(xoffset, yoffset);
}


void LoadingMessage()
{	
	ImGui::Begin("Resource Loading");
	ImGui::SetCursorPos(ImVec2(10, 30));			
	ImGui::Text("Loading Game Contents... can take up to 1 minute. ");
	ImGui::Text("It is loading several big models, 8K, 4K, 2K textures etc... ");
	ImGui::Text("I could have used 8K textures for everything but due to loading times I am forced to reduce most to 2K.");
	ImGui::Text("Next to that, I also decreased the level of detail for my models to allow faster loading speeds.");
	ImGui::Text("If I had the time I would use asynchronous resource loading which would be impact-full.");
	ImGui::Text("For performance I created an object pool, texture pool such that resources are only loaded once at the start.");
	ImGui::Text("For the textures, assets I have used blender, photoshop and most importantly the QUIXEL BRIDGE");
	ImGui::Text("QUIXEL BRIDGE is opensourced by Epic Games. It provides a whole library of high level textures and models of all kinds.");
	ImGui::Text("In my game I make use of physical based rendering and use the metallic, albeto, AO, roughness, normal maps provided by them.");
	ImGui::Text("Game should be loaded by about now. Thanks for reading ;)");
	ImGui::End();
}

void FPSUI()
{
	ImGui::Begin("FPS");
	ImGui::SetCursorPos(ImVec2(10, 30));
	ImGui::Text("Movement: WASD");
	ImGui::Text("Look Around: Mouse");
	ImGui::Text("Toggle Walking/Drone Modes: V");
	ImGui::Separator();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

bool resourcedLoaded = false;

int main()
{
	Game* game = Game::Instance();
	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	if (!window.CreateWindow())
	{
		return -1;
	}
	
	glEnable(GL_DEPTH_TEST);
	
	window.SetCallback(KeyCallback, MouseCallback, WindowSizeCallback, ScrollBack);
	window.SetFullScreen(false);

	
	/* Loop until the user closes the window */
	while (!window.ShouldClose())
	{
		if (window.tick == 2)
		{
			// load game content 
			const WorldLoader loader;
			loader.InitializeWorld(&game->world);
			resourcedLoaded = true;
		}
		
		window.StartFrame();

		if (resourcedLoaded) {
			game->Tick();
			FPSUI();
		}
		else 
			LoadingMessage();
		
		window.Tick();
		window.EndFrame();
	}

	window.Terminate();
	
	return 0;
}
