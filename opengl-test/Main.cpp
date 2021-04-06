#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include "Window.h"
#include "GlWrap.h"
#include "Shader.h"

int main(void) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    Window window;

    if (!window.CreateWindow())
    {
        return -1;
    }
    
    Shader shader("res\\shaders\\Basic.shader");

    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        window.Tick();
    }

    glfwTerminate();
    return 0;
}