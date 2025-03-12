#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "../Constants.h"
#include "../GlWrap.h"
#include "../Vendor/imgui.h"
#include "../Vendor/imgui_impl_glfw.h"
#include "../Vendor/imgui_impl_opengl3.h"
#include <array>
#include <stdexcept>

/// <summary>
/// Opgengl game window.
/// </summary>
class GameWindow
{
private:
	GLFWwindow* _window;
	GLFWmonitor* _monitor = nullptr;
	
	bool _updateViewport;
	
	std::array< int, 2 > _wndPos{ 0, 0 };
	std::array< int, 2 > _vpSize{ 0, 0 };


public:
	static int ScreenWidth;
	static int ScreenHeight;
	
	static float AspectRatio() { return 1.0f * ScreenWidth / ScreenHeight; }
	
	int tick;
	
	/// <summary>
	/// Create a new window instance.
	/// </summary>
	/// <returns></returns>
	int CreateWindow();

	/// <summary>
	/// Initializes a frame.
	/// </summary>
	void StartFrame() const;

	/// <summary>
	/// Finishes a frame.
	/// </summary>
	void EndFrame() const;

	/// <summary>
	/// Ticks logic for each game tick.
	/// </summary>
	void Tick();
	bool IsFullscreen();
	void SetFullScreen(bool fullscreen);

	/// <summary>
	/// Returns whether the window is closed.
	/// </summary>
	/// <returns></returns>
	bool ShouldClose() const;

	/// <summary>
	/// Returns a opengl window instance.
	/// </summary>
	/// <returns></returns>
	GLFWwindow* GetWindowRef() const;

	/// <summary>
	/// Initializes window callback methods.
	/// </summary>
	/// <param name="keyCallback"></param>
	/// <param name="mouseCallback"></param>
	/// <param name="resizeCallback"></param>
	/// <param name="scrollFun"></param>
	void SetCallback(GLFWkeyfun keyCallback, GLFWcursorposfun mouseCallback, GLFWwindowsizefun resizeCallback, GLFWscrollfun scrollFun) const;

	int Width() const;
	int Height() const;
	void Resize();

	/// <summary>
	/// Terminates and closes the window.
	/// </summary>
	void Terminate();

	static int CalculateAspectRatio();

	~GameWindow()
	{
		delete& _window;
	}
};
