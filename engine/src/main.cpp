#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/application.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    Application app;
    app.run();
}