#include "GameWindow.h"

#include <iostream>

int GameWindow::ScreenWidth = 1024;
int GameWindow::ScreenHeight = 1024;

int GameWindow::CreateWindow()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	ScreenWidth = mode->width;
	ScreenHeight = mode->height;
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	_window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Game Graphics", nullptr, nullptr);
			
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
	
	_monitor = glfwGetPrimaryMonitor();
	glfwGetWindowSize(_window, &ScreenWidth, &ScreenHeight);
	glfwGetWindowPos(_window, &_wndPos[0], &_wndPos[1]);
	
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

void GameWindow::Tick()
{
	if (_updateViewport)
	{
		glfwGetFramebufferSize(_window, &_vpSize[0], &_vpSize[1]);
		glViewport(0, 0, _vpSize[0], _vpSize[1]);
		glfwGetWindowSize(_window, &ScreenWidth, &ScreenHeight);
		glfwGetWindowPos(_window, &_wndPos[0], &_wndPos[1]);
		_updateViewport = false;		
	}
	
	tick++;
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	/* Swap front and back buffers */
	GLCall(glfwSwapBuffers(_window))

	/* Poll for and process events */
	GLCall(glfwPollEvents())
}

bool GameWindow::IsFullscreen(void)
{
	return glfwGetWindowMonitor(_window) != nullptr;
}

void GameWindow::SetFullScreen(bool fullscreen)
{
	if (IsFullscreen() == fullscreen)
		return;

	if (fullscreen)
	{
		// backup window position and window size
		glfwGetWindowPos(_window, &_wndPos[0], &_wndPos[1]);
		glfwGetWindowSize(_window, &ScreenWidth, &ScreenHeight);

		// get resolution of monitor
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		// switch to full screen
		glfwSetWindowMonitor(_window, _monitor, 0, 0, mode->width, mode->height, 0);
	}
	else
	{
		// restore last window size and position
		glfwSetWindowMonitor(_window, nullptr, _wndPos[0], _wndPos[1], ScreenWidth, ScreenHeight, 0);
	}

	_updateViewport = true;
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

int GameWindow::Width() const
{
	return ScreenWidth;
}

int GameWindow::Height() const
{
	return ScreenHeight;
}

void GameWindow::Resize()
{
	_updateViewport = true;
}

void GameWindow::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
