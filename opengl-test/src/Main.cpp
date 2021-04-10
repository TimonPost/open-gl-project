#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include <gtc/matrix_transform.hpp>

#include <fstream>

#include "GlWrap.h"
#include "Resources/WorldLoader.hpp"
#include "Resources/Shader.h"
#include "World/Renderer.h"
#include "World/GameWindow.h"

#include "World/GameWorld.h"

#include "Vendor/imgui.h"
#include "Vendor/imgui_impl_glfw.h"
#include "Vendor/imgui_impl_opengl3.h"

#include "Resources/TexturePool.cpp"
#include "World/Game.h"

// camera
float lastX = 400, lastY = 300;
float yaw = -90, pitch = 0;
bool firstMouse = true;

GameWindow window;

void window_size_callback(GLFWwindow* glfWindow, int width, int height)
{
	auto* game = Game::Instance();
	
	Camera* camera = game->world.MainCamera();

	window.SetWidth(width);
	window.SetHeight(height);

	game->render->UpdateProjection(width, height, DEFAULT_ASPECT_RATIO, camera->NearPlane, camera->FarPlane);
	glViewport(0, 0, width, height);
}

void ScrollBack(GLFWwindow* glfWindow, double xoffset, double yoffset)
{
	Camera* camera = Game::Instance()->world.MainCamera();
	camera->ProcessMouseScroll(yoffset);
}

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

class ModelEditor
{
public:
	glm::mat4 scaleMat = glm::mat4(1.0f);
	glm::mat4 translateMat = glm::mat4(1.0f);
	glm::mat4 rotateMat = glm::mat4(1.0f);

	ShapeBase* _base = nullptr;

	glm::vec3 scaleVec = glm::vec3(1.0f);
	glm::vec3 translateVec = glm::vec3(1.0f);
	glm::vec3 rotateVec = glm::vec3(1.0f);
	
	bool initialized = false;
		
	void Initialize(ShapeBase* base);

	void Update() const;

	void Draw();
};

void ModelEditor::Initialize(ShapeBase* base)
{
	this->_base = base;

	this->scaleMat = this->_base->_scale;
	this->rotateMat = this->_base->_rotate;
	this->translateMat = this->_base->_translate;
	this->initialized = true;
}

void ModelEditor::Update() const
{
	if (this->initialized)
	{
		this->_base->_scale = this->scaleMat;
		this->_base->_translate = this->translateMat;

		this->_base->Scale(this->scaleVec);
		this->_base->Translate(this->translateVec);
	}
}

void ModelEditor::Draw()
{
	if (this->initialized)
	{
		ImGui::SliderFloat3("Scale", &this->scaleVec.x, -10.0, 10.0);
		ImGui::SliderFloat3("Translate", &this->translateVec.x, -30, 30.0f);
		ImGui::SliderFloat3("Rotate", &this->rotateVec.x, 0.0f, 50.0f);
		ImGui::Separator();
	}
}

ModelEditor* statueEditor = new ModelEditor();
ModelEditor* romanArchEditor = new ModelEditor();

void DrawEditors(ModelEditor* editor,ShapeBase* shapes)
{
	if (!editor->initialized) {
		editor->Initialize(shapes);
	}

	editor->Draw();
	editor->Update();
}

void SetupWindow()
{	
	// auto* game = Game::Instance();
	// std::vector<ShapeBase*>* shapes = game->world.GetShapes();
	//
	// {
	// 	ImGui::Begin("Element");
	//
	// 	DrawEditors(statueEditor, shapes->at(10));
	// 	DrawEditors(romanArchEditor, shapes->at(11));
	//
	// 	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	// 	ImGui::End();
	//
	// }
}

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
	
	window.SetCallback(KeyCallback, MouseCallback, window_size_callback, ScrollBack);

	const WorldLoader loader;
	 loader.InitializeWorld(&game->world);
	 	
	/* Loop until the user closes the window */
	while (!window.ShouldClose())
	{				
		window.StartFrame();

		SetupWindow();

		game->Tick();
		window.Tick();
		
		window.EndFrame();
	}

	window.Terminate();
	
	return 0;
}
