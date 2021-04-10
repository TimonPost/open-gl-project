#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "../Constants.h"
#include "../GlWrap.h"

/// <summary>
/// Opgengl game window.
/// </summary>
class GameWindow
{
private:
	GLFWwindow* _window;
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;

public:
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
	void Tick() const;

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
	void SetWidth(int width);
	void SetHeight(int height);

	/// <summary>
	/// Terminates and closes the window.
	/// </summary>
	void Terminate();

	static int CalculateAspectRatio();
};
