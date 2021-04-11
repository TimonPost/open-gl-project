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
	auto* game = Game::Instance();
	
	Camera* camera = game->world.MainCamera();

	window.SetWidth(width);
	window.SetHeight(height);

	game->render->UpdateProjection(width, height, DEFAULT_ASPECT_RATIO, camera->NearPlane, camera->FarPlane);
	glViewport(0, 0, width, height);
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
}

// Opengl mouse callback
void MouseCallback(GLFWwindow* w, double xPos, double yPos)
{
	const int button = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT);

	if (button != GLFW_PRESS)
	{
		return;
	}
	
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

namespace ImGui {

	bool BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = size_arg;
		size.x -= style.FramePadding.x * 2;

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id))
			return false;

		// Render
		const float circleStart = size.x * 0.7f;
		const float circleEnd = size.x;
		const float circleWidth = circleEnd - circleStart;

		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);

		const float t = g.Time;
		const float r = size.y / 2;
		const float speed = 1.5f;

		const float a = speed * 0;
		const float b = speed * 0.333f;
		const float c = speed * 0.666f;

		const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
		const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
		const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;

		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
	}

	bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id))
			return false;

		// Render
		window->DrawList->PathClear();

		int num_segments = 30;
		int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

		const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
		const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for (int i = 0; i < num_segments; i++) {
			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
				centre.y + ImSin(a + g.Time * 8) * radius));
		}

		window->DrawList->PathStroke(color, false, thickness);
	}

}

void LoadingMessage()
{	
	ImGui::Begin("Resource Loading");
	ImGui::SetCursorPos(ImVec2(10, 30));			
	ImGui::Text("Loading Game Contents... can take up to 1 minute. ");
	ImGui::Text("It is loading several big models, 8K, 4K, 2K textures etc... ");
	ImGui::Text("I could have used 8K textures for everything but due to loading times I am forced to reduce most to 2K.");
	ImGui::Text("Next to that, I also decreased the level of detail for my models to allow faster loading speeds.");
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
