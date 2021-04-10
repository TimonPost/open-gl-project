#include "GlWrap.h"

void GlClearError()
{
	int count = 200;
	unsigned int error = glGetError();

	while (error != GL_NO_ERROR)
	{
		count--;
		if (count < 0)
		{
			std::cout << " glGetError error " << error <<
				" is in an endles loop (check if an OpenGL context exists) \n";
			Assert(false);
		}

		error = glGetError();
	}
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (const GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
};
