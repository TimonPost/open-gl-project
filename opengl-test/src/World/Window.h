#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "../Constants.h"
#include "../GlWrap.h"

class Window
{
private:
	GLFWwindow* _window;
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;

public:
	int CreateWindow();
	void StartFrame() const;
	void EndFrame() const;
	void Tick() const;
	bool ShouldClose() const;
	GLFWwindow* GetWindowRef() const;
	void SetCallback(GLFWkeyfun keyCallback, GLFWcursorposfun mouseCallback, GLFWwindowsizefun resizeCallback, GLFWscrollfun scrollFun) const;
	int Width() const;
	int Height() const;
	void SetWidth(int width);
	void SetHeight(int height);
	void Terminate();
	static int CalculateAspectRatio();
};
