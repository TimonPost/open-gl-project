#include "GameWindow.h"

#include <iostream>

#include "../Vendor/imgui.h"
#include "../Vendor/imgui_impl_glfw.h"
#include "../Vendor/imgui_impl_opengl3.h"


int GameWindow::CreateWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", nullptr, nullptr);

	if (!_window)
	{
		GLCall(glfwTerminate());
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(_window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}

	glfwSwapInterval(1);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();
	
	return 1;
}

void GameWindow::StartFrame() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GameWindow::EndFrame() const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameWindow::Tick() const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	/* Swap front and back buffers */
	GLCall(glfwSwapBuffers(_window))

	/* Poll for and process events */
	GLCall(glfwPollEvents())
}

bool GameWindow::ShouldClose() const
{
	return glfwWindowShouldClose(_window);
}

GLFWwindow* GameWindow::GetWindowRef() const
{
	return _window;
}

void GameWindow::SetCallback(GLFWkeyfun keyCallback, GLFWcursorposfun mouseCallback, GLFWwindowsizefun resizeCallback, GLFWscrollfun scrollFun) const
{
	GLCall(glfwSetKeyCallback(_window, keyCallback));
	GLCall(glfwSetCursorPosCallback(_window, mouseCallback));
	GLCall(glfwSetWindowSizeCallback(_window, resizeCallback));
	GLCall(glfwSetScrollCallback(_window, scrollFun));
	GLCall(glfwSetInputMode(_window, GLFW_STICKY_KEYS | GLFW_CURSOR, GLFW_CURSOR_DISABLED));
}

int GameWindow::CalculateAspectRatio()
{
	return 1.0f * SCREEN_WIDTH / SCREEN_HEIGHT;
}

int GameWindow::Width() const
{
	return screenWidth;
}

int GameWindow::Height() const
{
	return screenHeight;
}

void GameWindow::SetWidth(int width)
{
	screenHeight = width;
}

void GameWindow::SetHeight(int height)
{
	screenHeight = height;
}

void  GameWindow::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
