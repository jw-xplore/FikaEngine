#include "renderer.h"
#include <GLFW/glfw3.h>

namespace Renderer
{
	static int width, height;

	void init(int w, int h)
	{
		width = w;
		height = h;
	}

	void clear() { glClear(GL_COLOR_BUFFER_BIT); }
}