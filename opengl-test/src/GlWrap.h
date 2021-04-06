#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define Assert(x) if (!(x)) __debugbreak();
#define GLCall(x) { GlClearError(); \
    x;\
    Assert(GLLogCall(#x, __FILE__, __LINE__)) }

void GlClearError();
bool GLLogCall(const char* function, const char* file, int line);
