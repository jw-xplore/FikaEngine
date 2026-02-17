#include "application.h"
#include "../platform/window.h";
#include <GLFW/glfw3.h>

void Application::run()
{
	Window window;

    if (!window.create(1280, 720, "Retro Combat Engine"))
        return;

    while (!window.shouldClose())
    {
        window.poll();

        // temporary clear color
        glClear(GL_COLOR_BUFFER_BIT);

        window.swap();
    }

    window.destroy();
}